#define _CRT_SECURE_NO_WARNINGS

#include "../include/exe_running.h"
#include <cstdio>
#include <sstream>
#include <cstdlib>
#include <thread>
#include <atomic>
#include <chrono>
#include <iostream>

#ifdef _WIN32
#include <Windows.h>
#include <TlHelp32.h>
#else
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#endif


using namespace std;

exe_running::exe_running() {}
exe_running::~exe_running() {}

// 递归终止进程树
#ifdef _WIN32
bool exe_running::kill_process_tree(DWORD processId) 
{
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE)
        return false;
    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);
    if (Process32First(hSnapshot, &pe)) 
    {
        do 
        {
            if (pe.th32ParentProcessID == processId) 
                kill_process_tree(pe.th32ProcessID);
        } while (Process32Next(hSnapshot, &pe));
    }
    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, processId);
    if (hProcess != NULL) 
    {
        TerminateProcess(hProcess, 1);
        CloseHandle(hProcess);
    }
    CloseHandle(hSnapshot);
    return true;
}
#else
bool exe_running::kill_process_tree(pid_t processId)
{
    return kill(-processId, SIGKILL) == 0;
}
#endif

// 根据平台调用相应的终止进程树函数
#ifdef _WIN32
bool exe_running::kill_process_tree_impl()
{
    return kill_process_tree(child_pid_);
}
#else
bool exe_running::kill_process_tree_impl()
{
    return kill_process_tree(child_pid_);
}
#endif

// 带超时的运行
bool exe_running::run_with_timeout(const std::string& cmd, exe_run_result& result, int timeout_sec, int max_output_len)
{
#ifdef _WIN32
    SECURITY_ATTRIBUTES sa = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };
    HANDLE hRead = NULL, hWrite = NULL;
    CreatePipe(&hRead, &hWrite, &sa, 0);
    SetHandleInformation(hRead, HANDLE_FLAG_INHERIT, 0);

    STARTUPINFOA si = { sizeof(STARTUPINFOA) };
    PROCESS_INFORMATION pi = { 0 };

    si.dwFlags = STARTF_USESTDHANDLES;
    si.hStdOutput = hWrite;
    si.hStdError = hWrite;

    char cmdline[4096];
    strcpy(cmdline, cmd.c_str());

    if (!CreateProcessA(NULL, cmdline, NULL, NULL, TRUE, CREATE_NEW_PROCESS_GROUP, NULL, NULL, &si, &pi))
    {
        CloseHandle(hRead);
        CloseHandle(hWrite);
        return false;
    }

    CloseHandle(hWrite);
    child_pid_ = pi.dwProcessId;

    result.begin_time = time(NULL);

    std::atomic<bool> timeout(false);

    std::thread timer([&]() {
        if (WaitForSingleObject(pi.hProcess, timeout_sec * 1000) == WAIT_TIMEOUT)
        {
            timeout = true;
            kill_process_tree(child_pid_);
        }
        });

    char buf[512];
    DWORD read;
    while (ReadFile(hRead, buf, sizeof(buf) - 1, &read, NULL) && read > 0)
    {
        buf[read] = 0;
        if ((int)result.output.size() < max_output_len)
            result.output += buf;
    }

    timer.join();

    CloseHandle(hRead);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    result.end_time = time(NULL);
    result.timeout = timeout;
    result.run_ok = !timeout;

    return result.run_ok;
#endif
}

// 使用 popen 运行命令并捕获输出
int exe_running::run_with_popen(const string& cmd, exe_run_result& result, int timeout_sec, int max_output_len)
{
    result.begin_time = time(NULL);
    result.end_time = 0;
    result.output.clear();
    result.timeout = false;
    result.run_ok = false;
    result.exit_code = -1;
    result.output_exceeded = false;

#ifdef _WIN32

    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = NULL;

    HANDLE hRead = NULL, hWrite = NULL;
    if (!CreatePipe(&hRead, &hWrite, &sa, 0))
        return false;

    SetHandleInformation(hRead, HANDLE_FLAG_INHERIT, 0);

    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));

    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    si.hStdOutput = hWrite;
    si.hStdError = hWrite;
    si.wShowWindow = SW_HIDE;

    string cmdline = cmd;

    if (!CreateProcessA(NULL, (LPSTR)cmdline.c_str(), NULL, NULL, TRUE, CREATE_NEW_PROCESS_GROUP, NULL, NULL, &si, &pi))
    {
        CloseHandle(hRead);
        CloseHandle(hWrite);
        return false;
    }

    CloseHandle(hWrite);   // 父进程只读
    atomic<bool> finished(false);
	// 启动定时器线程
    thread timer([&]() {
        for (int i = 0; i < timeout_sec * 10; ++i)
        {
            if (finished)
                return;
            this_thread::sleep_for(chrono::milliseconds(100));
        }
        result.timeout = true;
        kill_process_tree(pi.dwProcessId);
        });
    char buf[512];
    DWORD readBytes;
	// 读取输出
    while (!result.timeout)
    {
        if (!ReadFile(hRead, buf, sizeof(buf) - 1, &readBytes, NULL) || readBytes == 0)
            break;
        buf[readBytes] = 0;
        //if ((int)result.output.size() < max_output_len)
        //{
            result.output += buf;
       // }
        //else
        //{
			//result.output_exceeded = true;
            //break;
       // }
    }

    if ((int)result.output.size() >= max_output_len)
        result.output_exceeded = true;
    WaitForSingleObject(pi.hProcess, INFINITE);
    DWORD exitCode = 0;
    GetExitCodeProcess(pi.hProcess, &exitCode);

    finished = true;
    timer.join();

    CloseHandle(hRead);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

    result.exit_code = (int)exitCode;
    result.end_time = time(NULL);
    //result.run_ok = (!result.timeout && exitCode == 0);
    result.run_ok = (!result.timeout && !result.output_exceeded && exitCode == 0);
    
    if (result.timeout)
        return RUN_TIMEOUT;
    if (result.output_exceeded)
        return RUN_OUTPUT_OVERFLOW;
    if (result.exit_code != 0)
		return RUN_RUNTIME_ERROR;
    if(result.run_ok)
	    return RUN_OK;
	return RUN_RUNTIME_ERROR;

#else   // Linux

    int pipefd[2];
    if (pipe(pipefd) < 0)
        return false;

    pid_t pid = fork();
    if (pid == 0)
    {
        setpgid(0, 0);
        dup2(pipefd[1], STDOUT_FILENO);
        dup2(pipefd[1], STDERR_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        execl("/bin/sh", "sh", "-c", cmd.c_str(), (char*)0);
        _exit(127);
    }

    close(pipefd[1]);

    atomic<bool> finished(false);
    thread timer([&]() {
        sleep(timeout_sec);
        if (!finished)
        {
            result.timeout = true;
            kill_process_tree(pid);
        }
        });

    char buf[512];
    ssize_t n;
    while (!result.timeout && (n = read(pipefd[0], buf, sizeof(buf))) > 0)
    {
        if ((int)result.output.size() < max_output_len)
            result.output.append(buf, n);
        else
        {
			result.output_exceeded = true;
            break;
        }
    }

    int status = 0;
    waitpid(pid, &status, 0);

    finished = true;
    timer.join();

    result.exit_code = WEXITSTATUS(status);
    result.end_time = time(NULL);
    result.run_ok = (!result.timeout && result.exit_code == 0);
    
    if (result.timeout)
        return RUN_TIMEOUT;
    if (result.output_exceed)
        return RUN_OUTPUT_OVERFLOW;
    if (result.exit_code != 0)
        return RUN_RUNTIME_ERROR;
    if (result.run_ok)
        return RUN_OK;
    return RUN_RUNTIME_ERROR;

    //return result.run_ok;
#endif
}

int exe_running::run_normal(const string& exe_path, exe_run_result& result, int timeout_sec, int max_output_len)
{
    return run_with_popen(exe_path, result, timeout_sec, max_output_len);
}

int exe_running::run_pipe(const string& exe_path, const string& get_input_exe, const string& data_file, const string& group_name, exe_run_result& result, int timeout_sec, int max_output_len)
{
    ostringstream cmd;
#ifdef _WIN32
    cmd << "cmd.exe /c ";
    cmd << get_input_exe << " " << data_file << " " << group_name << " | " << exe_path;
#else
    cmd << "/bin/sh -c ";
    cmd << get_input_exe << " " << data_file << " " << group_name << " | " << exe_path;
#endif
    return run_with_popen(cmd.str(), result, timeout_sec, max_output_len);
}

int exe_running::run_redirection(const string& exe_path, const string& data_file, exe_run_result& result, int timeout_sec, int max_output_len)
{
    ostringstream cmd;
#ifdef _WIN32
    cmd << "cmd /c \"" << "\"" << exe_path << "\"" << " < " << "\"" << data_file << "\"" << "\"";
#else
    cmd << exe_path << " < " << data_file;
#endif
    return run_with_popen(cmd.str(), result, timeout_sec, max_output_len);
}

int exe_running::run_args(const string& exe_path, const string& data_args, exe_run_result& result, int timeout_sec, int max_output_len)
{
    ostringstream cmd;
    cmd << exe_path << " " << data_args;
    return run_with_popen(cmd.str(), result, timeout_sec, max_output_len);
}