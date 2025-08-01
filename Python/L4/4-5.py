import jieba
def word_count():
    from collections import Counter

    with open("tj.txt", 'r', encoding='utf-8') as file:
        text = file.read()
    words = jieba.lcut(text)

    filtered_words = [word for word in words if len(word) > 1 and not word.isspace()]

    word_counts = Counter(filtered_words)
    top_3 = word_counts.most_common(3)

    for word, count in top_3:
        print(f"{word},{count}")

if __name__ == '__main__':
    word_count()