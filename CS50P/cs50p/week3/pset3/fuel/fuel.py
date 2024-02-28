def main():
    fraction = get_fraction("Fraction: ")
    if fraction >= 99:
        print("F")
    elif fraction <= 1:
        print("E")
    else:
        print(fraction, "%", sep="")


def get_fraction(prompt):
    while True:
        try:
            str = input(prompt)
            split = str.split("/")
            num, den = [int(x) for x in split]
            result = round((num/den) * 100)
            if result > 100:
                continue
            return result
        except (ValueError, ZeroDivisionError):
            pass

if __name__ == "__main__":
    main()