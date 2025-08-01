import pandas as pd
import os

schedule_df = pd.read_excel('st2025.xlsx', sheet_name='shedule', header=0, index_col=0)
info_df = pd.read_excel('st2025.xlsx', sheet_name='info')
xueke_df = pd.read_excel('st2025.xlsx', sheet_name='xueke', index_col=0)

xueke_df.columns = xueke_df.columns.str.strip()

student_id = input("请输入要查询的学号：")

if student_id not in map(str, info_df['学号'].values):
    print("学号不存在！")
    exit()

student_id_int = int(student_id)

student_info = info_df[info_df['学号'] == student_id_int].iloc[0]
student_name = student_info['姓名']
english_name = student_info['英文姓名']
gender = student_info['性别']

if student_id_int not in xueke_df.index:
    print("该学生没有选课信息！")
    exit()

selected_courses = xueke_df.columns[xueke_df.loc[student_id_int] == '√'].tolist()

result_dict = {
    '学号': student_id_int,
    '姓名': student_name,
    '英文姓名': english_name,
    '性别': gender,
    '选课冲突': []
}

for time_slot in schedule_df.index:
    for day in schedule_df.columns:
        courses = schedule_df.loc[time_slot, day]

        if pd.isna(courses):
            continue

        course_list = [course.strip() for course in str(courses).split(',')]

        selected_in_cell = [course for course in course_list if course in selected_courses]

        if len(selected_in_cell) >= 2:
            conflict_info = {
                '上课时间': time_slot,
                '日期': day,
                '冲突课程': ','.join(selected_in_cell)
            }
            result_dict['选课冲突'].append(conflict_info)

print(result_dict)