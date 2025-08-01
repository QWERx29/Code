def func(num):
    steps = []
    while True:
        num_str = str(num).zfill(4)
        if len(set(num_str)) == 1:
            steps.append(f"{num_str} - {num_str} = 0000")
            break
        digits = sorted(num_str)
        min_num = int(''.join(digits))
        max_num = int(''.join(digits[::-1]))
        diff = max_num - min_num
        diff_str = str(diff).zfill(4)
        step = f"{str(max_num).zfill(4)} - {str(min_num).zfill(4)} = {diff_str}"
        print(step)
        if diff == 6174:
            break
        num = diff

a = input("请输入4位数字：")
num = int(a)
steps = func(num)
