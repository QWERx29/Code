def output(n):
    i = 1
    while i <= n:
        j = 1
        while j <= i:
            print(f"{j}x{i}={j*i}", end=' ')
            j = j + 1
        print()
        i = i + 1


while True:
        try:
            a = input()
            n = int(a)

            if n < 1:
                continue
            elif n >= 9:
                continue
            else:
                output(n)
                break
            
        except ValueError:
            continue
