txt = input("请输入一个字符串：")
l = len(txt)
x = 25 - int(l / 2)
if x <= 1:
    x = 1
for i in range (1,51):
    print(f'*', end = "")
print()
for i in range (2,7):
    if i % 2 == 0:
        print(f'*', end = "")
    else:
        print(f' ', end = "")
    if i == 4:
        for j in range (2, x):
            print(f" ", end = "")
        print(txt, end="")
        for j in range (2, x):
            print(f" ", end = "")
    else:
        for j in range (2,50):
            print(" ", end = "")
    if i % 2 == 0:
        print(f'*', end = "")
    else:
        print(f' ', end = "")
    print()

for i in range (1,51):
    print(f'*', end = "")