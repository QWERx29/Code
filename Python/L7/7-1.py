from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import time
import pandas as pd

options = Options()
# options.add_argument('--headless')  # 无头浏览器
driver = webdriver.Chrome(options=options)

base_url = "https://see.tongji.edu.cn/info/1143/"
start_page = "14085.htm"
visited_urls = set()
data = []

while start_page and start_page not in visited_urls:
    visited_urls.add(start_page)
    url = base_url + start_page
    driver.get(url)

    try:
        WebDriverWait(driver, 10).until(EC.presence_of_element_located((By.CSS_SELECTOR, "div.title h3")))
        title = driver.find_element(By.CSS_SELECTOR, "div.title h3").text.strip()

        info_em = driver.find_elements(By.CSS_SELECTOR, "div.title em")
        editor = info_em[0].text.replace("编辑：", "").strip() if len(info_em) > 0 else ""
        publish_time = info_em[1].text.replace("发表时间：", "").strip() if len(info_em) > 1 else ""
        views = info_em[2].text.replace("浏览次数：", "").strip() if len(info_em) > 2 else ""

        content_div = driver.find_element(By.CLASS_NAME, "v_news_content")
        content = content_div.text.strip()

        data.append({
            "标题": title,
            "编辑": editor,
            "发表时间": publish_time,
            "浏览次数": views,
            "正文": content
        })
        # print(f"已抓取：{title}")
        try:
            nav_paragraph = driver.find_element(By.XPATH, "//p[@align='right']")
            paragraph_text = nav_paragraph.get_attribute("innerText")
            links = nav_paragraph.find_elements(By.TAG_NAME, "a")

            next_href = None
            if "下一条" in paragraph_text and len(links) >= 2:
                next_href = links[1].get_attribute("href")
            elif "下一条" in paragraph_text and len(links) == 1:
                # 有些新闻页面可能只有“下一条”，没有“上一条”
                next_href = links[0].get_attribute("href")
            if next_href:
                if next_href.startswith("https"):
                    start_page = next_href.replace(base_url, "")
                else:
                    start_page = next_href
            else:
                start_page = None
        except:
            start_page = None

        time.sleep(1.5)

    except Exception as e:
        print("抓取失败：", url)
        print(e)
        break

df = pd.DataFrame(data)
df.to_excel("tjnews.xlsx", index=False)
# print("所有新闻已保存到 tjnews.xlsx")

driver.quit()
