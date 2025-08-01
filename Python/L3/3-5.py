# 定义邻接关系
adjacency = {
    '河北': ['内蒙古', '辽宁', '山东', '河南', '山西', '陕西'],
    '山西': ['河北', '河南', '陕西', '内蒙古'],
    '内蒙古': ['黑龙江', '吉林', '辽宁', '河北', '山西', '陕西', '宁夏', '甘肃'],
    '辽宁': ['内蒙古', '河北', '吉林'],
    '吉林': ['黑龙江', '内蒙古', '辽宁'],
    '黑龙江': ['内蒙古', '吉林'],
    '山东': ['河北', '河南', '安徽', '江苏'],
    '河南': ['河北', '山东', '安徽', '湖北', '陕西', '山西'],
    '安徽': ['山东', '河南', '湖北', '江西', '江苏', '浙江'],
    '江苏': ['山东', '安徽', '浙江'],
    '浙江': ['江苏', '安徽', '江西', '福建'],
    '福建': ['浙江', '江西', '广东'],
    '广东': ['福建', '江西', '湖南', '广西'],
    '广西': ['广东', '湖南', '贵州', '云南'],
    '云南': ['广西', '贵州', '四川', '西藏'],
    '西藏': ['新疆', '青海', '四川', '云南'],
    '四川': ['陕西', '甘肃', '青海', '西藏', '云南', '贵州'],
    '贵州': ['四川', '云南', '广西', '湖南'],
    '湖南': ['湖北', '贵州', '广西', '广东', '江西'],
    '湖北': ['河南', '陕西', '湖南', '江西', '安徽'],
    '江西': ['安徽', '湖北', '湖南', '广东', '福建', '浙江'],
    '陕西': ['山西', '河南', '湖北', '四川', '甘肃', '宁夏', '内蒙古', '河北'],
    '甘肃': ['新疆', '内蒙古', '宁夏', '陕西', '四川', '青海'],
    '青海': ['新疆', '甘肃', '四川', '西藏'],
    '宁夏': ['内蒙古', '陕西', '甘肃'],
    '新疆': ['西藏', '青海', '甘肃'],
}

degrees = {province: len(neighbors) for province, neighbors in adjacency.items()}

sorted_provinces = sorted(degrees.keys(), key=lambda x: degrees[x], reverse=True)

color_map = {}
color_names = {0: '红', 1: '黄', 2: '蓝', 3: '绿'}

for province in sorted_provinces:
    used_colors = set()
    for neighbor in adjacency[province]:
        if neighbor in color_map:
            used_colors.add(color_map[neighbor])

    for color in range(4):  # 0:红, 1:黄, 2:蓝, 3:绿
        if color not in used_colors:
            color_map[province] = color
            break

print("省份着色方案：")
for province, color in color_map.items():
    print(f"{province}: {color_names[color]}")