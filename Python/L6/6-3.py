import matplotlib.pyplot as plt
import re
from collections import defaultdict

plt.rcParams['font.sans-serif'] = ['SimHei']
plt.rcParams['axes.unicode_minus'] = False

def load_character_names(file_path):
    names = []
    with open(file_path, 'r', encoding='utf-8') as f:
        content = f.read()
        names = content.split()
    names = list(set([name.strip() for name in names if name.strip()]))
    names.sort(key=len, reverse=True)
    return names

def count_character_occurrences(text, names):
    character_counts = defaultdict(int)
    pattern = re.compile('|'.join(sorted(names, key=len, reverse=True)))
    matches = pattern.findall(text)
    for name in matches:
        character_counts[name] += 1
    return character_counts

def main():
    character_names = load_character_names('三国人名汇总.txt')
    with open('三国演义.txt', 'r', encoding='utf-8') as f:
        novel_text = f.read()
    character_counts = count_character_occurrences(novel_text, character_names)
    top_characters = {name: count for name, count in character_counts.items() if count > 100}

    sorted_characters = sorted(top_characters.items(), key=lambda x: x[1], reverse=True)
    plt.figure(figsize=(15, 8))

    names = [item[0] for item in sorted_characters]
    counts = [item[1] for item in sorted_characters]

    bars = plt.bar(names, counts, color='b')
    plt.title('《三国演义》出现超过100次人物统计', fontsize=16)
    plt.xlabel('人物姓名', fontsize=14)
    plt.ylabel('出现次数', fontsize=14)

    for bar in bars:
        height = bar.get_height()
        plt.text(bar.get_x() + bar.get_width() / 2., height,
                 f'{height}',
                 ha='center', va='bottom', fontsize=9)
    plt.xticks(rotation=45, ha='right', fontsize=10)
    plt.tight_layout()
    plt.savefig('sg.jpg', dpi=300)

if __name__ == "__main__":
    main()