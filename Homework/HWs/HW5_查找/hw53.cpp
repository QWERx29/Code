
#include <iostream>
#include <vector>
#include <string>
#include <map>

class Solution
{
public:
    int solve(std::vector<std::vector<std::string>> &old_chart, std::vector<std::vector<std::string>> &new_chart)
    {
        int n = old_chart.size();
        int m = old_chart[0].size();
        int total_seats = n * m;
        std::map<std::string, int> name_to_correct_pos;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                int pos = i * m + j;
                name_to_correct_pos[new_chart[i][j]] = pos;
            }
        }
        std::vector<int> target(total_seats);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                int current_pos = i * m + j;
                std::string student_name = old_chart[i][j];
                int correct_pos = name_to_correct_pos[student_name];
                target[current_pos] = correct_pos;
            }
        }
        // 计算最少交换次数
        int swap_count = 0;
        std::vector<bool> visited(total_seats, false);
        for (int i = 0; i < total_seats; i++)
        {
            // 如果当前位置已经是正确的，或者已经访问过，跳过
            if (visited[i] || target[i] == i)
                continue;
            // 找到一个环
            int cycle_size = 0;
            int current = i;
            while (!visited[current])
            {
                visited[current] = true;
                current = target[current];
                cycle_size++;
            }
            // 每个大小为k的环需要k-1次交换
            if (cycle_size > 1)
                swap_count += (cycle_size - 1);
        }
        return swap_count;
    }
};