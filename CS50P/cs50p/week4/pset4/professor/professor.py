import random


def main():
    level = get_level()
    questions = 0
    score = 0
    while questions < 10:
        a = generate_integer(level)
        b = generate_integer(level)
        error_count = 0
        while error_count < 3:
            try:
                c = int(input(f"{a} + {b} = "))
                if int(c) == (a + b):
                    questions += 1
                    score += 1
                    break
                else:
                    error_count += 1
                    print("EEE")
            except ValueError:
                error_count += 1
                print("EEE")
        if error_count == 3:
            questions += 1
            print(f"{a} + {b} = {a + b}")

    print(f"Score: {score}")


def get_level():
    while True:
        user_input = input("Level: ")
        if user_input.isnumeric() and int(user_input) > 0 and int(user_input) < 4:
            return int(user_input)


def generate_integer(level):
    if level not in list(range(1, 4)):
        raise ValueError
    elif level == 1:
        return random.randrange(0, 10 ** (level))
    else:
        return random.randrange(10 ** (level - 1), 10 ** (level))


if __name__ == "__main__":
    main()
