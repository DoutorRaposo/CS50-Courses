import re

def main():
    print(count(input("Text: ")))


def count(s):
    compiled = re.compile(r"\bum\b", re.IGNORECASE)
    return len(re.findall(compiled, s))


if __name__ == "__main__":
    main()