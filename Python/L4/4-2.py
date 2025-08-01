def calc_gdp():
    gdp_data = {}
    with open('GDP.txt', 'r', encoding='utf-8') as file:
        for line in file:
            parts = line.strip().split('\t')
            if len(parts) < 2:
                continue
            year_str = parts[0].replace('年', '')
            try:
                year = int(year_str)
                gdp = int(parts[1])
                gdp_data[year] = gdp
            except ValueError:
                continue
    years = sorted(gdp_data.keys())
    gr = {}
    for i in range(1, len(years)):
        cy = years[i]
        py = years[i - 1]
        if cy - py == 1:
            pg = gdp_data[py]
            cg = gdp_data[cy]
            growth_rate = (cg - pg) / pg * 100
            gr[cy] = growth_rate
    for year in range(1980, 2019):
        if year in gr:
            print(f"{year}年: {gr[year]:.2f}%")
if __name__ == "__main__":
    calc_gdp()