#!/usr/bin/env python3

import argparse
import sys
from collections import deque
import requests
import os
from bs4 import BeautifulSoup
from urllib.parse import urlparse, urljoin, urlunparse
from concurrent.futures import ThreadPoolExecutor, as_completed

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from utils import VALID_EXTENSIONS

def parse_args():
    parser = argparse.ArgumentParser(
        prog="Spider",
        description="recursive image downloader"
    )
    parser.add_argument("url", help="Target URL")
    parser.add_argument(
        "-r", "--recursive",
        action="store_true",
        help="recursive Download"
    )
    parser.add_argument(
        "-l", "--level",
        type=int,
        default=5,
        metavar="N",
        help="maximum depth level (default: 5)"
    )
    parser.add_argument(
        "-p", "--path",
        default="./data/",
        metavar="PATH",
        help="download directory (default: ./data/)"
    )
    
    return parser.parse_args()

def extract_images(html: str, base_url: str) -> set[str]:
    """
        Extract all valid URL images from the html.
    """
    soup = BeautifulSoup(html, 'html.parser')
    images = set()
    
    for img_tag in soup.find_all('img'):
        src = img_tag.get('src')
        if not src:
            continue
            
        absolute_url = urljoin(base_url, src)
        
        path    = urlparse(absolute_url).path
        ext     = os.path.splitext(path)[1].lower()
        
        if ext in VALID_EXTENSIONS:
            images.add(absolute_url)            
    
    return images

def extract_links(html: str, base_url: str) -> set[str]:
    """Extrack every links"""
    soup = BeautifulSoup(html, 'html.parser')
    links = set()
    base_domain = urlparse(base_url).netloc
    print(base_domain)
    
    for a_tag in soup.find_all('a', href=True):
        href = a_tag['href']
        absolute_url = urljoin(base_url, href)

        # We stay on the same domain
        parsed = urlparse(absolute_url)
        if parsed.netloc == base_domain and parsed.scheme in ('http', 'https'):
            # Ignores ancres and isolated query strings
            links.add(urlunparse(parsed._replace(fragment='')))
    
    return links

def download_image(url: str, dest_dir: str) -> bool:
    """
    Download the image in dest_dir
    Send True if success, False if so.
    """
    os.makedirs(dest_dir, exist_ok=True)
    
    filename = os.path.basename(urlparse(url).path)
    if not filename:
        return False
    
    filepath = os.path.join(dest_dir, filename)
    
    # Dont download again the same images
    if os.path.exists(filepath):
        print(f"[SKIP] {filename} already exists")
        return True
    
    try:
        response = requests.get(
            url,
            headers={"User-Agent": "Mozilla/5.0"},
            timeout=10,
            stream=True  # Important for big files
        )
        response.raise_for_status() # raise http errors
        
        with open(filepath, 'wb') as f:
            for chunk in response.iter_content(chunk_size=8192):
                f.write(chunk)
        
        print(f"[OK] Downloaded: {filename}")
        return True

    except requests.RequestException as e:
        print(f"[ERROR] Failed to download {url}: {e}")
        return False
        
def spider(start_url: str, recursive: bool, max_depth: int, dest_path: str):
    visited_urls = set()
    downloaded_images = set()
    queue = deque([(start_url, 0)])
    effective_depth = max_depth if recursive else 0

    with ThreadPoolExecutor(max_workers=20) as executor:
        while queue:
            url, depth = queue.popleft()

            if url in visited_urls:
                continue
            if depth > effective_depth:
                continue

            visited_urls.add(url)
            print(f"[CRAWL] Depth {depth}: {url}")

            try:
                response = requests.get(
                    url,
                    headers={"User-Agent": "Mozilla/5.0"},
                    timeout=10
                )
                response.raise_for_status()
            except requests.RequestException as e:
                print(f"[ERROR] Cannot fetch {url}: {e}")
                continue

            html = response.text

            images_to_dl = [img for img in extract_images(html, url)
                            if img not in downloaded_images]

            futures = {executor.submit(download_image, img, dest_path): img
                       for img in images_to_dl}
            for future in as_completed(futures):
                img = futures[future]
                if future.result():
                    downloaded_images.add(img)

            if recursive and depth < effective_depth:
                for link in extract_links(html, url):
                    if link not in visited_urls:
                        queue.append((link, depth + 1))

    print(f"\n[DONE] {len(downloaded_images)} images downloaded.")

def main():
    args = parse_args()
    
    parsed = urlparse(args.url)
    if not parsed.scheme or not parsed.netloc:
        print(f"Error: '{args.url}' is not a valid URL", file=sys.stderr)
        sys.exit(1)

    spider(
        start_url=args.url,
        recursive=args.recursive,
        max_depth=args.level,
        dest_path=args.path
    )

if __name__ == "__main__":
    main()