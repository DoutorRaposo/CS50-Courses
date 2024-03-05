import random


def main():
    level = get_valid_number("Level: ")
    answer = random.randint(1, level)
    while True:
        guess = get_valid_number("Guess: ")
        if guess < answer:
            print("Too small!")
        elif guess > answer:
            print("Too large!")
        else:
            print("Just right!")
            exit()


def get_valid_number(question):
    while True:
        user_input = input(question)
        if user_input.isnumeric() and int(user_input) > 0:
            return int(user_input)

if __name__ == "__main__":
    main()
