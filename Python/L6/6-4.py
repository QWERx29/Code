import pandas as pd
import matplotlib.pyplot as plt
def draw():
    product_df = pd.read_excel('销售数据.xlsx', sheet_name='产品信息')
    customer_df = pd.read_excel('销售数据.xlsx', sheet_name='客户信息')
    sales_df = pd.read_excel('销售数据.xlsx', sheet_name='销售记录')

    _df = pd.merge(sales_df, product_df[['产品ID', '售价']], on='产品ID', how='left')

    _df['销售额'] = _df['数量'] * _df['售价']
    df = pd.merge(_df, customer_df[['客户ID', '城市']], on='客户ID', how='left')
    target_cities = ['上海', '北京', '广州']
    city_sales = df[df['城市'].isin(target_cities)]
    city_totals = city_sales.groupby('城市')['销售额'].sum().reset_index()

    plt.rcParams['font.sans-serif'] = ['SimHei']  # 用来正常显示中文标签
    plt.rcParams['axes.unicode_minus'] = False    # 用来正常显示负号

    plt.figure(figsize=(10, 8))
    plt.pie(city_totals['销售额'], labels=city_totals['城市'], autopct='%1.1f%%', startangle=90, colors=['#ff9999', '#66b3ff', '#99ff99'])

    plt.title('2025-07-30 三地消费总额对比', fontsize=15)
    plt.axis('equal')
    plt.legend(city_totals['城市'], loc='best')
    plt.savefig('sales.jpg', dpi=300, bbox_inches='tight')

if __name__ == '__main__':
    draw()