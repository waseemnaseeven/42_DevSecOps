#!/usr/bin/env python3

import os
import sys
from datetime import datetime
from PIL import Image
from PIL.ExifTags import TAGS, GPSTAGS

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from utils import VALID_EXTENSIONS, EXIF_DATE_TAGS, INTERNAL_TAGS, DECODERS



def get_creation_date(img: Image.Image, filepath: str) -> str:
    raw = img.getexif()
    if raw:
        for tag_id in EXIF_DATE_TAGS:
            val = raw.get(tag_id)
            if val:
                return str(val)
    stat = os.stat(filepath)
    ts = getattr(stat, 'st_birthtime', stat.st_mtime)
    return datetime.fromtimestamp(ts).strftime("%Y:%m:%d %H:%M:%S")


def get_basic_metadata(img: Image.Image, filepath: str) -> dict:
    stat = os.stat(filepath)
    return {
        "Filename"      : os.path.basename(filepath),
        "Format"        : img.format or "Unknown",
        "Mode"          : img.mode,
        "Size"          : f"{img.width}x{img.height} px",
        "File Size"     : f"{stat.st_size} bytes",
        "Creation Date" : get_creation_date(img, filepath),
        "Animated"      : getattr(img, "is_animated", False),
        "Frames"        : getattr(img, "n_frames", 1),
    }


def decode_gps(gps_raw: dict) -> dict:
    result = {}

    for k, v in gps_raw.items():
        tag_name = GPSTAGS.get(k, f"Unknown({k})")
        if isinstance(v, bytes):
            v = '.'.join(str(b) for b in v)
        result[tag_name] = v

    try:
        def dms_to_decimal(dms, ref) -> float:
            d, m, s = (float(x) for x in dms)
            dec = d + m / 60 + s / 3600
            return round(-dec if ref in ('S', 'W') else dec, 6)

        lat = gps_raw.get(2)
        lon = gps_raw.get(4)
        if lat and lon:
            result["DecimalLatitude"]  = dms_to_decimal(lat, gps_raw.get(1, 'N'))
            result["DecimalLongitude"] = dms_to_decimal(lon, gps_raw.get(3, 'E'))
    except Exception:
        pass

    return result

def _decode_tag(tag_name: str, value) -> object:
    """Apply human-readable decoding to a raw EXIF value."""
    if isinstance(value, bytes):
        value = value.decode('utf-8', errors='replace')
    if tag_name in DECODERS:
        value = DECODERS[tag_name].get(value, str(value))
    return value


def get_exif_metadata(img: Image.Image) -> dict:
    raw = img.getexif()
    if not raw:
        return {}

    exif = {}

    for tag_id, value in raw.items():
        tag_name = TAGS.get(tag_id, f"Unknown({hex(tag_id)})")

        if tag_name in INTERNAL_TAGS:
            continue

        if tag_name == "GPSInfo":
            if isinstance(value, dict):
                exif["GPS"] = decode_gps(value)
            else:
                try:
                    gps_ifd = raw.get_ifd(tag_id)
                    if gps_ifd:
                        exif["GPS"] = decode_gps(gps_ifd)
                except Exception:
                    exif["GPS"] = "[unreadable]"
        elif tag_name == "MakerNote":
            exif[tag_name] = "[binary data]"
        else:
            exif[tag_name] = _decode_tag(tag_name, value)

    exif_ifd = raw.get_ifd(0x8769)
    if exif_ifd:
        for tag_id, value in exif_ifd.items():
            tag_name = TAGS.get(tag_id, f"Unknown({hex(tag_id)})")
            if tag_name in INTERNAL_TAGS:
                continue
            exif[tag_name] = _decode_tag(tag_name, value)

    return exif

def get_png_metadata(img: Image.Image) -> dict:
    if img.format != 'PNG':
        return {}
    return {k: str(v) for k, v in img.info.items()
            if isinstance(v, (str, int, float))}


def print_section(title: str, data: dict) -> None:
    if not data:
        return
    print(f"\n── {title} {'─' * (50 - len(title))}")
    for key, val in data.items():
        if isinstance(val, dict):
            print(f"  {key}:")
            for k, v in val.items():
                print(f"    {k:<22} : {v}")
        else:
            print(f"  {key:<24} : {val}")


def process_file(filepath: str) -> None:
    ext = os.path.splitext(filepath)[1].lower()

    if ext not in VALID_EXTENSIONS:
        print(f"[ERROR] Unsupported format: {filepath}", file=sys.stderr)
        return
    if not os.path.isfile(filepath):
        print(f"[ERROR] File not found: {filepath}", file=sys.stderr)
        return

    try:
        with Image.open(filepath) as img:
            basic = get_basic_metadata(img, filepath)
            exif  = get_exif_metadata(img)
            png   = get_png_metadata(img)
    except Exception as e:
        print(f"[ERROR] Cannot open {filepath}: {e}", file=sys.stderr)
        return

    print("\n" + "=" * 60)
    print(f"  FILE: {filepath}")
    print("=" * 60)

    print_section("Basic Attributes", basic)
    print_section("EXIF Metadata",    exif)
    print_section("PNG Metadata",     png)

    if not exif and not png:
        print("\n  [No EXIF metadata found]")

def main() -> None:
    if len(sys.argv) < 2:
        print("Usage: python3 scorpion.py FILE1 [FILE2 ...]", file=sys.stderr)
        sys.exit(1)

    for filepath in sys.argv[1:]:
        process_file(filepath)


if __name__ == "__main__":
    main()