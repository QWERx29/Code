import math

# ---- 计算信息熵 ----
def entropy(data):
    label_count = {}
    for row in data:
        label = row[-1]
        label_count[label] = label_count.get(label, 0) + 1

    ent = 0.0
    total = len(data)
    for count in label_count.values():
        p = count / total
        ent -= p * math.log2(p)
    return ent


# ---- 按属性划分数据集 ----
def split_data(data, attr_index, value):
    subset = []
    for row in data:
        if row[attr_index] == value:
            subset.append(row)
    return subset


# ---- 选择最优属性（信息增益最大） ----
def choose_best_feature(data):
    base_entropy = entropy(data)
    best_gain = -1
    best_attr = -1
    feature_count = len(data[0]) - 1

    for i in range(feature_count):
        values = set(row[i] for row in data)
        new_entropy = 0.0

        for v in values:
            subset = split_data(data, i, v)
            p = len(subset) / len(data)
            new_entropy += p * entropy(subset)

        gain = base_entropy - new_entropy
        if gain > best_gain:
            best_gain = gain
            best_attr = i

    return best_attr


# ---- 多数表决 ----
def majority_label(data):
    count = {}
    for row in data:
        label = row[-1]
        count[label] = count.get(label, 0) + 1
    return max(count, key=count.get)


# ---- 构建决策树（递归） ----
def build_tree(data, features):
    labels = [row[-1] for row in data]

    # 情况1：所有样本类别相同
    if labels.count(labels[0]) == len(labels):
        return labels[0]

    # 情况2：无特征可分，投票决定
    if len(features) == 0:
        return majority_label(data)

    best_feat = choose_best_feature(data)
    best_feat_name = features[best_feat]

    tree = {best_feat_name: {}}
    feat_values = set(row[best_feat] for row in data)

    for value in feat_values:
        sub_features = features[:best_feat] + features[best_feat+1:]
        subset = split_data(data, best_feat, value)

        # 递归构建
        subtree = build_tree(
            [row[:best_feat] + row[best_feat+1:] for row in subset],
            sub_features
        )
        tree[best_feat_name][value] = subtree

    return tree


# ---- 测试函数 ----
if __name__ == "__main__":
    # 数据集
    data = [
        ["Sunny", "Hot", "High", "Weak", "No"],
        ["Sunny", "Hot", "High", "Strong", "No"],
        ["Overcast", "Hot", "High", "Weak", "Yes"],
        ["Rain", "Mild", "High", "Weak", "Yes"],
        ["Rain", "Cool", "Normal", "Weak", "Yes"],
        ["Rain", "Cool", "Normal", "Strong", "No"],
        ["Overcast", "Cool", "Normal", "Strong", "Yes"],
        ["Sunny", "Mild", "High", "Weak", "No"],
        ["Sunny", "Cool", "Normal", "Weak", "Yes"],
        ["Rain", "Mild", "Normal", "Weak", "Yes"],
        ["Sunny", "Mild", "Normal", "Strong", "Yes"],
        ["Overcast", "Mild", "High", "Strong", "Yes"],
        ["Overcast", "Hot", "Normal", "Weak", "Yes"],
        ["Rain", "Mild", "High", "Strong", "No"]
    ]

    features = ["Outlook", "Temperature", "Humidity", "Wind"]

    tree = build_tree(data, features)
    print("生成的 ID3 决策树：")
    print(tree)
