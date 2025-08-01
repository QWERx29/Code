import json
import matplotlib.pyplot as plt
import numpy as np

def draw():
    plt.rcParams['font.sans-serif'] = ['SimHei', 'Microsoft YaHei', 'WenQuanYi Micro Hei']
    plt.rcParams['axes.unicode_minus'] = False

    with open('json_sh_wether.txt', 'r', encoding='utf-8') as f:
        data = json.load(f)

    wether_data = data['wether data']
    min_temp = [item[0] for item in wether_data]
    max_temp = [item[1] for item in wether_data]
    days = np.arange(1, len(min_temp) + 1)
    months = ['1月', '2月', '3月', '4月', '5月', '6月',
              '7月', '8月', '9月', '10月', '11月', '12月']
    month_days = [0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365]
    month_positions = [(month_days[i] + month_days[i + 1]) // 2 for i in range(12)]

    plt.figure(figsize=(12, 6))
    plt.plot(days, min_temp, label='最低温度', color='blue')
    plt.plot(days, max_temp, label='最高温度', color='red')
    plt.xlabel('月份')
    plt.ylabel('温度 (°C)')
    plt.title('上海2023年每日最高/最低温度走势')
    plt.xticks(month_positions, months)
    plt.savefig('wether.jpg', dpi=300, bbox_inches='tight')
    plt.close()

if __name__ == '__main__':
    draw()
