import sys

arg = sys.argv[1].encode(errors="surrogateescape")

print(''.join([chr(b - i) if 0 <= (b - i) <= 0x10FFFF else '?' for i, b in enumerate(arg)]))