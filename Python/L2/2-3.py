from math import sqrt
a, b, c = eval(input("请输入一元二次方程的系数a,b,c："))
delta = b ** 2 - 4 * a * c

if delta < 0:
    print("无实根")

elif delta == 0:
    x = - b / (2 * a)
    print(f"x1 = x2 =", x, end = "\n")

else:
    x1 = - (b + sqrt(delta)) / (2 * a)
    x2 = - (b - sqrt(delta)) / (2 * a)
    print(f"x1 =", x1, ", x2 =", x2, end = "\n")