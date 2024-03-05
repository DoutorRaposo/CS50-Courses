from datetime import date
import inflect
import re
import sys


def main():
    birthday = convert_input(input("Date of Birth: ").strip())
    print(get_delta(birthday))


def convert_input(user_input):
    m = re.match(r"^(\d{4})-(\d{2})-(\d{2})$", user_input)
    if not m:
        sys.exit("Invalid date")
    year, month, day = [int(n) for n in m.group(1, 2, 3)]
    return date(year, month, day)


def get_delta(birthday):
    today = date.today()
    p = inflect.engine()
    minutes = p.number_to_words(
        int((today - birthday).total_seconds() / 60), andword=""
    )
    return f"{minutes.capitalize()} minutes"


if __name__ == "__main__":
    main()
