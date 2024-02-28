months = [
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December",
]
while True:
    try:
        user_date = input("Date: ")
        if len(user_date.split("/")) == 3:
            elements = user_date.split("/")
            if int(elements[0]) > 12 or int(elements[1]) > 31:
                continue
            print(f"{int(elements[2])}-{int(elements[0]):02}-{int(elements[1]):02}")
            break
        elif (
            len(user_date.split()) == 3
            and user_date.split()[0].isalpha()
            and "," in user_date.split()[1]
            and user_date.split()[1].rstrip(",").isnumeric()
            and user_date.split()[2].isnumeric
            and user_date.split()[0] in months
        ):
            year = int(user_date.split()[2])
            month = int(months.index(user_date.split()[0])) + 1
            day = int(user_date.split()[1].rstrip(","))
            if day > 31:
                continue
            print(f"{year}-{month:02}-{day:02}")
            break
    except ValueError:
        continue
    except EOFError:
        print()
        exit()
