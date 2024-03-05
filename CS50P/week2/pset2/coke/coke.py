def main():
    coke = 50
    while True:
        if coke > 0:
            print("Amount Due:", coke)
            cents = get_cents()
            coke -= int(cents)

        if coke < 0:
            print("Change Owed:", abs(coke))
            break

        elif coke == 0:
            print("Change Owed:", coke)
            break


def get_cents():
    while True:
        user_input = int(input("Insert Coin: "))
        if user_input == 25 or user_input == 10 or user_input == 5:
            return user_input
        else:
            return 0


main()
