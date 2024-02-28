def main():
    user_input = input("Input: ")
    output = shorten(user_input)
    print(output)


def shorten(word):
    vowels = ["a", "e", "i", "o", "u", "A", "E", "I", "O", "U"]
    return word.translate( { ord(i): None for i in vowels} )

if __name__ == "__main__":
    main()