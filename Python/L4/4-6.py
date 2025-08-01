class sfz:
    def __init__(self, id_number):
        self.id = id_number
    def getyear(self):
        # 检查身份证长度是否为18位
        if len(self.id) != 18:
            return "无效的身份证号码长度（应为18位）"
        year_str = self.id[6:10]
        try:
            year = int(year_str)
            if 1900 <= year <= 2100:
                return year
            return "无效的出生年份"
        except ValueError:
            return "年份格式错误"

    def Disp(self):
        print(f"身份证号码: {self.id}")
if __name__ == "__main__":
    id1 = sfz("310103198810065273")
    print("身份证信息:")
    id1.Disp()
    print(f"出生年份: {id1.getyear()}")
