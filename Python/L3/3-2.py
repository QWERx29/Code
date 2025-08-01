def f(x):
    return 2 * (x ** 3) - 4 * (x ** 2) + 3 * x - 6
def solve(a, b):
    if f(a) == 0:
        return a
    if f(b) == 0:
        return b

    t = 0
    while t < 100:
        t += 1
        z = (a + b) / 2
        if abs(f(z)) < 1e-6:
            return z

        if f(z) * f(a) < 0:
            b = z
        else:
            a = z
    return (a + b) / 2

ans = solve (-10, 10)
print(f"方程在[-10,10]区间的根为：{ans}", end = "\n")