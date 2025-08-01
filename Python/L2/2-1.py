n = 64
def ch():
    global n
    n += 1
    if n == 91:
        n = 65
    return (chr(n))

row = int(input("请输入三角形的行数（1-26）："))

for i in range(row + 1):
    print(' ' * (20 - i), end = '')
    for j in range(2 * i  - 1):
        print(ch(), end  = '')
    print()
