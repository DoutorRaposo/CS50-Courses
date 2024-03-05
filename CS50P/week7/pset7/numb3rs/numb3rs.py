import re
import sys


def main():
    print(validate(input("IPv4 Address: ")))


def validate(ip):
    m = re.match(r"^([\d]{0,3})\.([\d]{0,3})\.([\d]{0,3})\.([\d]{0,3})$", ip)
    if m == None:
        return False
    if len(m.groups()) != 4:
        return False
    for group in m.groups():
        if int(group) > 255:
            return False
    return True

if __name__ == "__main__":
    main()