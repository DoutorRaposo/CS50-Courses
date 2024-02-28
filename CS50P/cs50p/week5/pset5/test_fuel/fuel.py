def main():
    user_input = input("Fraction: ")
    fraction = convert(user_input)
    flag = gauge(fraction)
    print(flag)

def convert(input):
    split = input.split("/")
    num, den = [int(x) for x in split]
    if den == 0:
        raise ZeroDivisionError
    if num > den:
        raise ValueError
    result = round((num / den) * 100)
    return result

def gauge(percentage):
    if percentage >= 99:
        return "F"
    elif percentage <= 1:
        return "E"
    else:
        return f"{percentage}%"

if __name__ == "__main__":
    main()
