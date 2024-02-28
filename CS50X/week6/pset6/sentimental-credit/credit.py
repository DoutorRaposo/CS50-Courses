from cs50 import get_string
import math


def main():
    while True:
        creditcard = get_string("Insert your credit card number: ")
        if len(creditcard) > 12 and len(creditcard) < 17:
            break
        else:
            exit("INVALID")

    digit_list = list(creditcard)
    digit_list.reverse()
    sum = 0

    for index in range(len(digit_list)):
        if index % 2 == 0:
            sum += int(digit_list[index])
        if index % 2 != 0:
            digit = int(digit_list[index]) * 2
            if len(str(digit)) > 1:
                temp = list(str(digit))
                digit = int(temp[0]) + int(temp[1])
            sum += digit

    sum_list = list(str(sum))
    if int(sum_list[len(sum_list) - 1]) != 0:
        exit("INVALID")
    digit_list.reverse()

    if len(digit_list) == 16:
        fdcheck = 10 * int(digit_list[0]) + int(digit_list[1])
        if fdcheck > 50 and fdcheck < 56:
            print("MASTERCARD")
        elif fdcheck > 39 and fdcheck < 50:
            print("VISA")
        else:
            exit("INVALID")
    if len(digit_list) == 15:
        fdcheck = 10 * int(digit_list[0]) + int(digit_list[1])
        if fdcheck == 34 or fdcheck == 37:
            print("AMEX")
        else:
            exit("INVALID")
    if len(digit_list) == 13:
        if int(digit_list[0]) == 4:
            print("VISA")
        else:
            exit("INVALID")
    if len(digit_list) == 14 or len(digit_list) < 13:
        exit("INVALID")


main()