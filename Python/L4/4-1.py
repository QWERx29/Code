def count_names():
    with open("红楼梦.txt", 'r', encoding='utf-8') as file:
        text = file.read()

    cnt1 = text.count("林黛玉")
    cnt2 = text.count("贾宝玉")

    print(f"统计结果：")
    print(f"林黛玉的出现次数为: {cnt1}")
    print(f"贾宝玉的出现次数为: {cnt2}")

if __name__ == "__main__":
    count_names()