#ifndef _EXE_RUNNING_H_
#define _EXE_RUNNING_H_

#include <string>
#include <vector>
#include <ctime>

#ifdef _WIN32
#include <Windows.h>
#include <TlHelp32.h>
#else
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#endif

struct exe_run_result
{
    bool     run_ok;
    bool     timeout;
    bool     output_exceeded;
    int      exit_code;
    time_t   begin_time;
    time_t   end_time;
    std::string output;
};

// 运行错误代码枚举
enum RUN_ERR_CODE
{
    RUN_OK = 0,                // 正确运行
    RUN_NO_EXE = 1,            // exe 不存在
    RUN_PIPE_OPEN_FAIL = 2,    // 管道方式打开失败
    RUN_TIMER_CREATE_FAIL = 3, // 定时器创建失败
    RUN_TIMER_START_FAIL = 4,  // 启动定时器失败
    RUN_TIMEOUT = 5,           // 运行超时
    RUN_OUTPUT_OVERFLOW = 6,   // 超过输出上限
    RUN_RUNTIME_ERROR = 7      // 运行失败（exit_code != 0）
};

class exe_running
{
public:
    exe_running();
    ~exe_running();

    
    bool run_with_timeout(const std::string& cmd, exe_run_result& result, int timeout_sec, int max_output_len);

    int run_normal(const std::string& exe_path, exe_run_result& result, int timeout_sec, int max_output_len);
    int run_pipe(const std::string& exe_path, const std::string& get_input_exe, const std::string& data_file, const std::string& group_name, exe_run_result& result, int timeout_sec, int max_output_len);
    int run_redirection(const std::string& exe_path, const std::string& data_file, exe_run_result& result, int timeout_sec, int max_output_len);
    int run_args(const std::string& exe_path, const std::string& data_args, exe_run_result& result, int timeout_sec, int max_output_len);

private:
    int run_with_popen(const std::string& cmd, exe_run_result& result, int timeout_sec, int max_output_len);

#ifdef _WIN32
    bool kill_process_tree(DWORD processId);
    DWORD child_pid_;
#else
    bool kill_process_tree(pid_t processId);
    pid_t child_pid_;
#endif
    bool kill_process_tree_impl();
};

#endif