import sys
import csv


def main():
    if len(sys.argv) < 3:
        sys.exit("Too few command-line arguments")

    if len(sys.argv) > 3:
        sys.exit("Too many command-line arguments")

    input = sys.argv[1]
    output = sys.argv[2]

    if not input.lower().endswith(".csv"):
        sys.exit("Not a CSV file")

    try:
        with open(input) as file:
            reader = csv.DictReader(file)
            list = []
            for line in reader:
                last, first = line["name"].split(", ")
                temp_dict = {
                    "first": first,
                    "last": last,
                    "house": line["house"]
                }
                list.append(temp_dict)
    except FileNotFoundError:
        sys.exit(f"Could not read {input}")

    with open(output, "w") as file:
        fieldnames = ["first", "last", "house"]
        writer = csv.DictWriter(file, fieldnames=fieldnames)
        writer.writeheader()
        for line in list:
            writer.writerow(line)

if __name__ == "__main__":
    main()
