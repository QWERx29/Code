# spb_post_outlets_crawler_nossl.py
# -*- coding: utf-8 -*-
import re
import time
import csv
import sys
import random
import logging
from typing import Dict, Optional

import requests
import pandas as pd
from bs4 import BeautifulSoup
from tqdm import tqdm
import urllib3

# ------------------- 全局 SSL 验证关闭 -------------------
urllib3.disable_warnings(urllib3.exceptions.InsecureRequestWarning)

START_ID = 56500
END_ID = 56590 # 包含 MAX = 56503
BASE = "https://zwfw.spb.gov.cn/gjj/pfyycsml/pfyycsmlDetail?uuid={id}"

HEADERS = {
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) "
                  "AppleWebKit/537.36 (KHTML, like Gecko) "
                  "Chrome/123.0.0.0 Safari/537.36",
    "Accept-Language": "zh-CN,zh;q=0.9,en;q=0.8",
    "Accept": "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8",
    "Connection": "keep-alive",
}
CHECKPOINT_CSV = "spb_post_outlets_checkpoint.csv"
FINAL_XLSX = "spb_post_outlets.xlsx"
LOG_FILE = "spb_post_outlets.log"

REQ_TIMEOUT = 15
MAX_RETRY = 5
SLEEP_MIN = 0.1
SLEEP_MAX = 0.6
BATCH_SAVE = 200

FIELD_ALIASES = {
    "所属省": "省", "省": "省",
    "所属市": "市", "市": "市",
    "所属区(县)": "区县", "所属区县": "区县", "区县": "区县",
    "营业场所": "网点名称", "网点名称": "网点名称",
    "地址": "地址",
    "开办业务": "开办业务", "业务": "开办业务",
    "邮政编码": "邮编", "邮编": "邮编",
}

TARGET_COLUMNS = ["uuid", "省", "市", "区县", "网点名称", "地址", "开办业务", "邮编", "页面URL", "抓取状态"]


def normalize_key(k: str) -> str:
    k = k.strip().replace("：", ":").replace("\u3000", " ").replace("\xa0", " ")
    return re.sub(r"\s+", "", k)


def clean_value(v: str) -> str:
    return re.sub(r"[ \t]+", " ", v.strip().replace("\xa0", " ").replace("\u3000", " "))


def extract_by_pairs_from_text(text: str) -> Dict[str, str]:
    mapping = {}
    for line in text.splitlines():
        line = line.strip()
        if not line or (":" not in line and "：" not in line):
            continue
        parts = line.split("：", 1) if "：" in line else line.split(":", 1)
        if len(parts) != 2:
            continue
        k, v = normalize_key(parts[0]), clean_value(parts[1])
        for alias, unified in FIELD_ALIASES.items():
            if normalize_key(alias) == k:
                mapping[unified] = v
                break
    return mapping


def extract_fields(html: str) -> Dict[str, str]:
    soup = BeautifulSoup(html, "lxml")
    kv = {}
    for lab in soup.find_all(text=True):
        text_lab = str(lab).strip()
        key = normalize_key(text_lab).rstrip(":")
        if not any(normalize_key(a).rstrip(":") == key for a in FIELD_ALIASES.keys()):
            continue
        val = None
        el = getattr(lab, "parent", None)
        if el:
            sib = el.find_next_sibling()
            if sib:
                val_text = sib.get_text(" ", strip=True)
                if val_text:
                    val = clean_value(val_text)
        if val:
            for alias, unified in FIELD_ALIASES.items():
                if normalize_key(alias).rstrip(":") == key:
                    kv[unified] = val
                    break
    text_kv = extract_by_pairs_from_text(soup.get_text("\n", strip=True))
    merged = {}
    for unified in set(FIELD_ALIASES.values()):
        merged[unified] = kv.get(unified) or text_kv.get(unified)
    return merged


def fetch_one(session: requests.Session, uid: int) -> Dict[str, Optional[str]]:
    url = BASE.format(id=uid)
    status = "OK"
    html = None
    for attempt in range(1, MAX_RETRY + 1):
        try:
            resp = session.get(url, headers=HEADERS, timeout=REQ_TIMEOUT, verify=False)  # <- 核心修改
            if resp.status_code == 404:
                status = "404"
                break
            resp.raise_for_status()
            html = resp.text
            break
        except requests.RequestException as e:
            status = f"ERR{attempt}:{e.__class__.__name__}"
            time.sleep(min(3.0, 0.5 * attempt) + random.uniform(0, 0.5))
    row = {
        "uuid": uid, "省": None, "市": None, "区县": None,
        "网点名称": None, "地址": None, "开办业务": None, "邮编": None,
        "页面URL": url, "抓取状态": status,
    }
    if html and status == "OK":
        fields = extract_fields(html)
        for k in ["省", "市", "区县", "网点名称", "地址", "开办业务", "邮编"]:
            row[k] = fields.get(k)
        if not any(row[k] for k in ["省", "市", "区县", "网点名称", "地址", "开办业务", "邮编"]):
            row["抓取状态"] = "EMPTY_OR_LAYOUT_CHANGE"
    return row


def load_checkpoint() -> int:
    try:
        df = pd.read_csv(CHECKPOINT_CSV, encoding="utf-8")
        if len(df) == 0:
            return START_ID
        return min(int(df["uuid"].max()) + 1, END_ID)
    except Exception:
        return START_ID


def append_checkpoint(rows):
    file_exists = False
    try:
        open(CHECKPOINT_CSV, "r", encoding="utf-8").close()
        file_exists = True
    except FileNotFoundError:
        pass
    with open(CHECKPOINT_CSV, "a", newline="", encoding="utf-8") as f:
        writer = csv.DictWriter(f, fieldnames=TARGET_COLUMNS)
        if not file_exists:
            writer.writeheader()
        for r in rows:
            writer.writerow({c: r.get(c) for c in TARGET_COLUMNS})


def finalize_to_excel():
    df = pd.read_csv(CHECKPOINT_CSV, encoding="utf-8")
    df = df.sort_values("uuid").drop_duplicates(subset=["uuid"], keep="last")
    df = df[TARGET_COLUMNS]
    df.to_excel(FINAL_XLSX, index=False)
    print(f"导出完成：{FINAL_XLSX}（共 {len(df)} 条）")


def main():
    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        handlers=[logging.FileHandler(LOG_FILE, encoding="utf-8"), logging.StreamHandler(sys.stdout)]
    )
    session = requests.Session()
    start_uid = load_checkpoint()
    all_rows_batch = []
    logging.info(f"开始抓取：uuid {start_uid} -> {END_ID}")
    for uid in tqdm(range(start_uid, END_ID + 1), ncols=90):
        row = fetch_one(session, uid)
        all_rows_batch.append(row)
        time.sleep(random.uniform(SLEEP_MIN, SLEEP_MAX))
        if len(all_rows_batch) >= BATCH_SAVE:
            append_checkpoint(all_rows_batch)
            logging.info(f"写入检查点 {len(all_rows_batch)} 条，最新 uuid={uid}")
            all_rows_batch = []
    if all_rows_batch:
        append_checkpoint(all_rows_batch)
    finalize_to_excel()
    logging.info("任务完成。")


if __name__ == "__main__":
    main()
