import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import load_iris
from sklearn.decomposition import PCA

def kmeans_plus_plus_init(X, k):
    n_samples = X.shape[0]
    centers = []

    # 随机选第一个中心
    idx = np.random.randint(0, n_samples)
    centers.append(X[idx])

    # 选取剩余中心
    for _ in range(1, k):
        dist_sq = np.array([min([np.inner(x - c, x - c) for c in centers]) for x in X])
        probs = dist_sq / dist_sq.sum()
        cumulative = probs.cumsum()
        r = np.random.rand()

        for idx, p in enumerate(cumulative):
            if r < p:
                centers.append(X[idx])
                break

    return np.array(centers)

def kmeans(X, k, max_iter=100):
    centers = kmeans_plus_plus_init(X, k)
    centers_history = [centers.copy()]  # 用于可视化中心轨迹

    for _ in range(max_iter):
        # 计算距离并分类
        labels = np.argmin(np.linalg.norm(X[:, np.newaxis] - centers, axis=2), axis=1)

        # 更新中心
        new_centers = np.array([X[labels == i].mean(axis=0) if np.any(labels == i)
                                else centers[i]
                                for i in range(k)])

        # 记录轨迹
        centers_history.append(new_centers.copy())

        # 判断收敛
        if np.allclose(new_centers, centers):
            break

        centers = new_centers

    return centers, labels, centers_history

iris = load_iris()
X = iris.data
X_pca = PCA(n_components=2).fit_transform(X)  # 用 PCA 降到 2D 方便绘图

k = 3
centers, labels, centers_history = kmeans(X_pca, k)

plt.figure(figsize=(8, 6))
plt.title("K-Means++ Clustering on Iris (PCA 2D)", fontsize=14)

for i in range(k):
    plt.scatter(X_pca[labels == i, 0], X_pca[labels == i, 1], s=40, label=f"Cluster {i}")

centers_history = np.array(centers_history)
for i in range(k):
    plt.plot(centers_history[:, i, 0], centers_history[:, i, 1], "--o", label=f"Center {i} Path")

plt.xlabel("PC1")
plt.ylabel("PC2")
plt.legend()
plt.grid(True)
plt.show()
