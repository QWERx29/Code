def decimal_to_base_vertical(decimal, base):
    if decimal == 0:
        return ["0"], ["任何进制结果均为 0"]  # 处理特殊情况
    
    digits = []
    steps = []
    original = decimal
    
    while decimal > 0:
        remainder = decimal % base
        quotient = decimal // base
        # 记录步骤 (base, quotient, remainder)
        steps.append((base, quotient, remainder))
        digits.append(remainder)
        decimal = quotient

    # 生成结果字符串
    hex_map = {10:'A', 11:'B', 12:'C', 13:'D', 14:'E', 15:'F'}
    result = []
    for d in reversed(digits):
        if base == 16 and d >= 10:
            result.append(hex_map[d])
        else:
            result.append(str(d))
    
    return steps, [''.join(result)]

def print_vertical_conversion(number):
    bases = [2, 8, 16]
    for base in bases:
        steps, results = decimal_to_base_vertical(number, base)
        print(f"\n十进制 {number} 转 {base} 进制过程：")
        
        # 打印计算步骤
        max_width = len(str(number)) + 2
        for b, q, r in steps:
            print(f"{b:2} | {q:>{max_width}} | {r:2}")
        print(f" 0 | {steps[-1][1]:>{max_width}}")  # 最后一行
        
        # 打印转换结果
        print(f"\n转换结果：{results[0]}")

# 输入验证和主程序
try:
    num = int(input("请输入十进制整数："))
    print_vertical_conversion(num)
except ValueError:
    print("输入必须是整数！")