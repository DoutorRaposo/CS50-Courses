import re

def main():
    print(convert(input("Hours: ")))


def convert(s):
    if m := re.match(
        r"^(\d{1,2})(?: |:([0-5][0-9]) )(\w{2}) to (\d{1,2})(?: |:([0-5][0-9]) )(\w{2})$", s
    ):
        elements = list(m.groups())
        for index, element in enumerate(elements):
            if element == None:
                elements[index] = "00"
            if element == "PM":
                if elements[index - 2] == "12":
                    elements[index - 2] = "12"
                else:
                    elements[index - 2] = str(int(elements[index - 2]) + 12)
            if element == "AM":
                if elements[index - 2] == "12":
                    elements[index - 2] = "00"
                elif elements[index - 2] != "11":
                    elements[index - 2] = "0" + elements[index - 2]
        return elements[0] + ":" + elements[1] + " to " + elements[3] + ":" + elements[4]

    else:
        raise ValueError


if __name__ == "__main__":
    main()
