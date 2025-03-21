def number_converter():
    # 获取用户输入
    number_str = input("请输入数值：").strip().upper()
    base = int(input("请输入该数值的进制（2、8、10、16）："))
    precision = int(input("请输入小数部分保留位数（默认6）：") or 6)

    # 校验进制合法性
    if base not in [2, 8, 10, 16]:
        print("错误：进制必须是2、8、10、16中的一个！")
        return

    # 预处理输入（处理负号和小数点）
    is_negative = number_str.startswith('-')
    number_str = number_str.replace('-', '')
    
    if '.' in number_str:
        integer_part, fractional_part = number_str.split('.')
    else:
        integer_part, fractional_part = number_str, ''

    # 校验数字有效性
    valid_chars = {
        2: {'0', '1'},
        8: set('01234567'),
        10: set('0123456789'),
        16: set('0123456789ABCDEF')
    }[base]

    if not (set(integer_part) <= valid_chars and set(fractional_part) <= valid_chars):
        print("错误：输入的数值与指定进制不匹配！")
        return

    # 转换整数部分
    try:
        decimal_int = int(integer_part, base) if integer_part else 0
    except:
        print("错误：整数部分转换失败！")
        return

    # 转换小数部分
    decimal_frac = 0.0
    if fractional_part:
        try:
            for i, char in enumerate(fractional_part, 1):
                decimal_frac += int(char, base) * (base ** -i)
        except:
            print("错误：小数部分转换失败！")
            return

    # 合并十进制结果
    decimal = (-1 if is_negative else 1) * (decimal_int + decimal_frac)

    # 通用转换函数
    def convert_fraction(target_base, num, precision):
        fractional = abs(num - int(num))
        result = []
        for _ in range(precision):
            fractional *= target_base
            digit = int(fractional)
            result.append(format(digit, 'X') if target_base == 16 else str(digit))
            fractional -= digit
            if fractional == 0:
                break
        return ''.join(result)

    # 转换为其他进制
    def convert_base(target_base, num):
        # 处理符号
        sign = '-' if num < 0 else ''
        num = abs(num)
        
        # 处理整数部分
        int_part = int(num)
        integer = (bin(int_part)[2:] if target_base == 2 else
                  oct(int_part)[2:] if target_base == 8 else
                  hex(int_part)[2:].upper() if target_base == 16 else
                  str(int_part))
        
        # 处理小数部分
        fractional = convert_fraction(target_base, num, precision)
        return sign + (f"{integer}.{fractional}" if fractional else integer)

    # 生成所有进制转换结果
    results = {
        2: convert_base(2, decimal),
        8: convert_base(8, decimal),
        10: convert_base(10, decimal),
        16: convert_base(16, decimal)
    }

    # 输出结果
    print("\n转换结果：")
    print(f"二进制：{results[2]}")
    print(f"八进制：{results[8]}")
    print(f"十进制：{results[10]}")
    print(f"十六进制：{results[16]}")

# 运行转换器
if __name__ == "__main__":
    number_converter()