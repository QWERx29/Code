import random

def find_max_rectangle(matrix):
    if not matrix or not matrix[0]:
        return 0, 0, 0, 0, 0
    
    rows = len(matrix)
    cols = len(matrix[0])
    max_area = 0
    rect_info = (0, 0, 0, 0, 0)  # (area, top, left, height, width)
    
    left_ones = [[0] * cols for _ in range(rows)]
    
    for i in range(rows):
        for j in range(cols):
            if matrix[i][j] == 1:
                left_ones[i][j] = 1 if j == 0 else left_ones[i][j-1] + 1

    for i in range(rows):
        for j in range(cols):
            if matrix[i][j] == 0:
                continue
                
            width = left_ones[i][j]
            min_width = width
            height = 1
            
            k = i
            while k >= 0 and matrix[k][j] == 1:
                min_width = min(min_width, left_ones[k][j])
                area = min_width * height
                
                if area > max_area:
                    max_area = area
                    top = k
                    left = j - min_width + 1
                    rect_info = (max_area, top, left, height, min_width)
                
                height += 1
                k -= 1
    return rect_info

matrix = [[random.randint(0, 1) for _ in range(10)] for _ in range(10)]

print("原始10x10矩阵:")
for row in matrix:
    print(" ".join(map(str, row)))

area, top, left, height, width = find_max_rectangle(matrix)

marked_matrix = [row[:] for row in matrix]

for i in range(top, top + height):
    for j in range(left, left + width):
        if marked_matrix[i][j] == 1:
            marked_matrix[i][j] = '*'

print(f"\n找到最大全1矩形：面积={area}，位置：顶行={top}，左列={left}，高度={height}，宽度={width}")
print("替换后的矩阵:")
for row in marked_matrix:
    print(" ".join(map(str, row)))