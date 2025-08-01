import numpy as np
import matplotlib.pyplot as plt

def draw():
    plt.rcParams['font.sans-serif'] = ['SimHei', 'Microsoft YaHei', 'WenQuanYi Micro Hei']
    plt.rcParams['axes.unicode_minus'] = False

    H0 = 200
    W0 = 200
    t = np.arange(0, 2 * np.pi, 0.01)

    x = (2 / 3) * W0 * (np.cos(t)**3 + np.sin(t))
    y = (2 / 3) * H0 * (np.sin(t)**3 + np.cos(t))

    plt.figure(figsize=(6, 6))
    plt.plot(x, y, color='purple', linewidth=2)
    plt.title('参数方程曲线')
    plt.axis('equal')  # 保持x和y轴比例
    plt.grid(True)

    plt.savefig('curve.jpg', dpi=300)
    plt.close()

if __name__ == '__main__':
    draw()