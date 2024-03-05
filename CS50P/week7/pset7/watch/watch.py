import re


def main():
    print(parse(input("HTML: ")))


def parse(s):
    if m := re.match(
        r"^.*src=[\"](?:http(?:s)?://(?:www\.)?)?youtube.com/embed/(.*?)[\"].*$", s
    ):
        return "https://youtu.be/" + m.group(1)
    else:
        return None


if __name__ == "__main__":
    main()
