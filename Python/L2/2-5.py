d = {
    "0": "zero",
    "1": "one",
    "2": "two",
    "3": "three",
    "4": "four",
    "5": "five",
    "6": "six",
    "7": "seven",
    "8": "eight",
    "9": "nine"
}

num = input("请输入电话号码: ")

ans = '-'.join(d[char] for char in num)

print("转换后的英文形式:", ans)