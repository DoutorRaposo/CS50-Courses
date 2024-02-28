def main():
    answer = input("Greeting: ")
    price = value(answer)
    print(f"${price}")


def value(greeting):
    words_list = greeting.lower().split()
    if words_list[0] != "hello" and words_list[0] != "hello,":
        if words_list[0][0] == 'h':
            return 20
        else:
            return 100
    else:
        return 0


if __name__ == "__main__":
    main()