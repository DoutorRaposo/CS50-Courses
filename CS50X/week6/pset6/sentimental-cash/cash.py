from cs50 import get_float
import math


def main():
    cents = get_cents()
    quarters = calculate_quarters(cents)
    cents -= quarters * 25
    dimes = calculate_dimes(cents)
    cents -= dimes * 10
    nickels = calculate_nickels(cents)
    cents -= nickels * 5
    pennies = calculate_pennies(cents)
    cents -= pennies * 1
    coins = quarters + dimes + nickels + pennies
    print(coins)


def get_cents():
    while True:
        change = get_float("Change owed: ")
        if change > 0:
            return int(100 * change)


def calculate_quarters(int):
    quarters = int / 25
    return math.floor(quarters)


def calculate_dimes(int):
    dimes = int / 10
    return math.floor(dimes)


def calculate_nickels(int):
    nickels = int / 5
    return math.floor(nickels)


def calculate_pennies(int):
    pennies = int / 1
    return math.floor(pennies)


main()