import pandas as pd
import os

def get_display_width(s):
    width = 0
    for char in s:
        if '\u4e00' <= char <= '\u9fff' or char in '，。；！？【】（）“”’‘':  # 中文字符和中文标点
            width += 2
        else:
            width += 1
    return width

def pad_string(s, total_width, align='left', fill_char=' '):
    current_width = get_display_width(str(s))
    if current_width >= total_width:
        return s
    
    padding = total_width - current_width
    if align == 'left':
        return s + fill_char * padding
    elif align == 'right':
        return fill_char * padding + s
    else:  # center
        left_pad = padding // 2
        right_pad = padding - left_pad
        return fill_char * left_pad + s + fill_char * right_pad


schedule_df = pd.read_excel('st2025.xlsx', sheet_name='shedule', header=0, index_col=0)
info_df = pd.read_excel('st2025.xlsx', sheet_name='info')
xueke_df = pd.read_excel('st2025.xlsx', sheet_name='xueke', index_col=0)

xueke_df.columns = xueke_df.columns.str.strip()

student_id = input("请输入要查询的学号：")

# 验证学号是否存在
if student_id not in map(str, info_df['学号'].values):
    print("学号不存在！")
    exit()

student_name = info_df[info_df['学号'] == int(student_id)]['姓名'].values[0]

selected_courses = xueke_df.columns[xueke_df.loc[int(student_id)] == '√'].tolist()

student_schedule = schedule_df.copy()

def filter_courses(cell):
    if pd.isna(cell):
        return ""
    courses = [course.strip() for course in str(cell).split(',')]
    return ",".join([course for course in courses if course in selected_courses])

student_schedule = student_schedule.map(filter_courses)

col_widths = {
    '时间': 12,
    '周一': 30,
    '周二': 30,
    '周三': 30,
    '周四': 30,
    '周五': 30
}

total_width = sum(col_widths.values())

title = f"{student_name}的课表"
centered_title = pad_string(title, total_width, align='center', fill_char='*')
print("\n" + centered_title)
print("*" * total_width)

header = "".join([
    pad_string(col, col_widths[col], align='center') 
    for col in ['时间', '周一', '周二', '周三', '周四', '周五']
])
print(header)

print("-" * total_width)

for time_slot in student_schedule.index:
    row = [pad_string(time_slot, col_widths['时间'], align='left')]
    for day in ['周一', '周二', '周三', '周四', '周五']:
        cell_value = student_schedule.loc[time_slot, day]
        row.append(pad_string(cell_value, col_widths[day], align='middle'))
    print("".join(row))

print()