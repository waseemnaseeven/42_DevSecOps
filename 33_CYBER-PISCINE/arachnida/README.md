# Arachnida

Web scraping and image metadata analysis tools.

## Programs

### `spider` — recursive image downloader

```
./spider [-r] [-l N] [-p PATH] URL
```

| Option | Description | Default |
|---|---|---|
| `-r` | Enable recursive crawling | off |
| `-l N` | Max recursion depth (requires `-r`) | `5` |
| `-p PATH` | Download directory | `./data/` |

```bash
./spider https://books.toscrape.com/                  # single page
./spider -r https://books.toscrape.com/               # recursive, depth 5
./spider -r -l 2 https://books.toscrape.com/          # recursive, depth 2
./spider -r -l 3 -p /tmp/imgs https://books.toscrape.com/
```

Downloads `.jpg` `.jpeg` `.png` `.gif` `.bmp` files only. Stays on the same domain. Skips already downloaded files.

---

### `scorpion` — image metadata reader

```
./scorpion FILE1 [FILE2 ...]
```

```bash
./scorpion data/photo.jpg
./scorpion data/*.jpg
./scorpion img1.png img2.bmp img3.gif
```

Displays basic attributes (filename, format, dimensions, file size, creation date) and EXIF data (camera make/model, GPS coordinates, exposure settings, etc.) for each file.

Supports `.jpg` `.jpeg` `.png` `.gif` `.bmp`.

---

## Installation

```bash
pip install -r requirements.txt
```

## Structure

```
arachnida/
├── spider       # image crawler
├── scorpion     # metadata reader
└── utils.py     # shared constants
```