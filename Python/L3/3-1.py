num = 1
def prime_gen(limit):
    global num
    pr = []
    for num in range(2, limit + 1):
        is_prime = True
        for i in range(2, int(num ** 0.5) + 1):
            if num % i == 0:
                is_prime = False
                break
        if is_prime:
            pr.append(num)
    return pr


primes = prime_gen(1000)
primes_set = set(primes)
x = input("请输入一个1000以内的偶数: ")
try:
    num = int(x)
    if num <= 0 or num > 1000:
        print("无效输入")
    if num % 2 != 0:
        print("无效输入")
    found = False
    for p in primes:
        if p > num // 2:
                break
        q = num - p
        if q in primes_set:
            print(f"{num} = {p} + {q}")
            found = True
            break
except ValueError:
    print("无效输入")