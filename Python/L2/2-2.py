while True:
    m, n = eval(input("请输入头数和脚数m,n："))
    if n % 2 != 0:
        print("脚的数目不能是奇数!")
    elif m < 0:
        print("头的数目不能是负数")
    elif n < 0:
        print("脚的数目不能是负数")
    else:
        break

y = n // 2 - m
x = m - y
print(f"笼子中有", x, "只鸡,", y, "只兔", end = "\n")