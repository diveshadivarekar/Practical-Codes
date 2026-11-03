# 7. Web crawler: pull product names, prices and links from an e-commerce site
# Practice site made for scraping: https://books.toscrape.com
import sys, requests, pandas as pd
from bs4 import BeautifulSoup
from urllib.parse import urljoin

url = sys.argv[1] if len(sys.argv) > 1 else "https://books.toscrape.com/catalogue/page-1.html"
products, pages = [], 3                                   # crawl first 3 pages

for _ in range(pages):
    soup = BeautifulSoup(requests.get(url, timeout=10).text, "html.parser")
    for item in soup.select("article.product_pod"):       # one product card
        a = item.h3.a
        products.append({"title": a["title"],
                         "price": item.select_one(".price_color").text,
                         "link": urljoin(url, a["href"])})
    nxt = soup.select_one("li.next a")                    # follow the "next" button
    if not nxt: break
    url = urljoin(url, nxt["href"])

df = pd.DataFrame(products)
df.to_csv("products.csv", index=False)
print(df.head(), f"\nTotal products: {len(df)}  (saved to products.csv)")
