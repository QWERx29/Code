import pandas as pd
import matplotlib.pyplot as plt

def draw():
    plt.rcParams['font.sans-serif'] = ['SimHei', 'Microsoft YaHei', 'WenQuanYi Micro Hei']
    plt.rcParams['axes.unicode_minus'] = False

    df = pd.read_excel('st_data.xlsx', sheet_name='score')
    def categorize_grade(grade):
        if grade < 60:
            return '不及格'
        elif 60 <= grade < 70:
            return '及格'
        elif 70 <= grade < 80:
            return '中'
        elif 80 <= grade < 90:
            return '良'
        else:
            return '优'

    c_grades = df['C语言'].apply(categorize_grade)
    c_counts = c_grades.value_counts().reindex(['不及格', '及格', '中', '良', '优'], fill_value=0)

    py_grades = df['Python'].apply(categorize_grade)
    py_counts = py_grades.value_counts().reindex(['不及格', '及格', '中', '良', '优'], fill_value=0)

    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(14, 7))

    colors = ['#ff6b6b', '#4ecdc4', '#ffe66d', '#6a5acd', '#20b2aa']
    explode = (0.10, 0, 0, 0, 0)

    ax1.pie(c_counts, labels=c_counts.index, autopct='%1.1f%%',
            startangle=90, colors=colors, explode=explode, shadow=False)
    ax1.set_title('C语言成绩分布', fontsize=16)

    ax2.pie(py_counts, labels=py_counts.index, autopct='%1.1f%%',
            startangle=90, colors=colors, explode=explode, shadow=False)
    ax2.set_title('Python成绩分布', fontsize=16)

    plt.suptitle('C语言与Python成绩分布对比', fontsize=20, y=0.98)

    # plt.tight_layout(rect=[0, 0, 1, 0.95])

    plt.savefig('pie_2451317.jpg', dpi=300, bbox_inches='tight')
    plt.close()

if __name__ == '__main__':
    draw()