sentence = input("请输入一个英文句子: ")

letter_count = {}
for char in sentence:
    if char.isalpha():
        upper_char = char.upper()
        letter_count[upper_char] = letter_count.get(upper_char, 0) + 1

sorted_letters = sorted(letter_count.items())

print("每个字母的出现次数:")
for letter, count in sorted_letters:
    print(f"{letter}: {count}")