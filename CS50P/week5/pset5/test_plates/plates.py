def main():
    plate = input("Plate: ")
    if is_valid(plate):
        print("Valid")
    else:
        print("Invalid")


def is_valid(s):
    invalid_chars = ["!", "?", ".", ",", ":", ";"]
    ## "… vanity plates may contain a maximum of 6 characters (letters or numbers) and a minimum of 2 characters.”
    if len(s) < 2 or len(s) > 6:
        return False
    ## “No periods, spaces, or punctuation marks are allowed.”
    for c in s:
        if c in invalid_chars:
            return False
    ## “All vanity plates must start with at least two letters.”
    for c in s[0:2]:
        if c.isnumeric():
            return False
    ## “Numbers cannot be used in the middle of a plate; they must come at the end. The first number used cannot be a ‘0’.”
    for index in range(len(s)):
        ## After letters stop, they must all be number and the first not "0".
        if s[index].isnumeric():
            if s[index:][0] == "0":
                return False
            for c in s[index:]:
                if c.isalpha():
                    return False
            break

    return True


if __name__ == "__main__":
    main()
