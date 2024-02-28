from cs50 import get_string


def main():
    text = get_string("Text: ")
    number_of_letters = count_letter(text)
    number_of_words = count_words(text)
    number_of_sentences = count_sentences(text)
    grade = index(number_of_letters, number_of_words, number_of_sentences)
    if grade < 0:
        print("Before Grade 1")
    elif grade > 0 and grade < 17:
        print(f"Grade {grade}")
    elif grade > 16:
        print("Grade 16+")


def count_letter(text):
    letters = 0
    for letter in text:
        if letter.isalpha():
            letters += 1
    return letters


def count_words(text):
    list_words = text.split()
    return len(list_words)


def count_sentences(text):
    closers = 0
    for letter in text:
        if letter == '?' or letter == '.' or letter == '!':
            closers += 1
    return closers


def index(letters, words, sentences):
    L = (letters / words) * 100
    S = (sentences / words) * 100
    index = (0.0588 * L) - (0.296 * S) - 15.8
    return round(index)


main()