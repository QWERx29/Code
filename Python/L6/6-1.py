def main():
    id = "2451317"
    l = len(id)

    input_str = input("请输入一个1至100范围内的数字：")
    input_str = input_str.strip()

    try:
        num = int(input_str)
        if num < 1 or num > 100:
            print("非法输入")
            return
    except ValueError:
        print("非法输入")
        return

    n = num
    total_rows = 2 * n - 1
    t = 0
    print()  
    for row in range(1, total_rows + 1):
        if row <= n:
            num_digits = 2 * row - 1
        else:
            num_digits = 2 * (2 * n - row) - 1
        if row <= n:
            leading_spaces = ' ' * (n - row)
        else:
            leading_spaces = ' ' * (row - n)

        digit_str = ''
        for i in range(num_digits):
            current_index = (t + i) % l
            digit_str += id[current_index]
        t = (t + num_digits) % l
        line = leading_spaces + digit_str
        print(line)

if __name__ == "__main__":
    main()