import pandas as pd
import matplotlib.pyplot as plt

def draw():
    plt.rcParams['font.sans-serif'] = ['SimHei', 'Microsoft YaHei', 'WenQuanYi Micro Hei']  # 设置中文字体
    plt.rcParams['axes.unicode_minus'] = False

    score_df = pd.read_excel('st_data.xlsx', sheet_name='score')
    info_df = pd.read_excel('st_data.xlsx', sheet_name='info')

    merged_df = pd.merge(score_df[['学号', '高数']], info_df[['学号', '性别']], on='学号')

    gender_avg = merged_df.groupby('性别')['高数'].mean()

    male_avg = gender_avg.loc['男']
    female_avg = gender_avg.loc['女']

    print(f"男生高数平均分: {male_avg:.2f}")
    print(f"女生高数平均分: {female_avg:.2f}")

    plt.figure(figsize=(8, 6))
    colors = ['#1f77b4', '#ff7f0e']
    gender_avg.plot(kind='bar', color=colors)

    plt.title('高数男女生平均分对比', fontsize=15)
    plt.xlabel('性别', fontsize=12)
    plt.ylabel('平均分', fontsize=12)
    plt.xticks(rotation=0)
    plt.ylim(0, 100)

    for i, v in enumerate(gender_avg):
        plt.text(i, v + 1, f'{v:.2f}', ha='center', fontsize=10)

    plt.savefig('2451317.jpg', dpi=300, bbox_inches='tight')
    plt.close()

if __name__ == '__main__':
    draw()