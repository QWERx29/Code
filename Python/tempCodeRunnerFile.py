if diff == 0 or (diff_str in seen and diff != 6174):
            steps.append("检测到死循环！")
            break