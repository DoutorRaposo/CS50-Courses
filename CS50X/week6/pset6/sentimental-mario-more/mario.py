while True:
    try:
        height = int(input("Height: "))
        if (height > 0 and height < 9):
            break
    except ValueError:
        print("Not an integer")

for lines in range(height):
    print(' ' * (height - int(lines) - 1) + '#' * (int(lines) + 1) + 2 * ' ' + '#' * (int(lines) + 1))