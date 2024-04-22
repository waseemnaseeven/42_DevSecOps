import sys

def reverse_string(input):
    ret = ''
    for i in range(len(input)):
        reversed_char = chr(ord(input[i]) - i)
        ret += reversed_char
    return ret

def main():
    if len(sys.argv) != 2:
        print("Usage: python3 reverse.py <string to reverse>")
        sys.exit(1)
    
    input_str = sys.argv[1]
    reversed_string = reverse_string(input_str)
    print("Reversed string:", reversed_string)

if __name__ == "__main__":
    main()
