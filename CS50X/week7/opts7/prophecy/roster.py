import csv
from cs50 import SQL
import os
import sys
import tabulate


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python roster.py database_name.db")
    # Create file. If it already exists, proceed.
    try:
        f = open(sys.argv[1], "x")
        f.close()
        os.system(f"cat schema.sql | sqlite3 {sys.argv[1]}")
    except FileExistsError as error:
        print("Database already exists. Proceeding.")

    # Create object.
    db = SQL(f"sqlite:///{sys.argv[1]}")

    # Check if the schema is applied.
    try:
        db.execute("SELECT * FROM students")
        print("Schema present in file. Proceeding.")
    except RuntimeError as error:
        os.system(f"cat schema.sql | sqlite3 {sys.argv[1]}")
        print("Schema not applied before. Applied and proceeding.")

    with open("students.csv", "r") as file:
        reader = csv.DictReader(file)
        for line in reader:
            # Checks if the value is already there. First, student_name in students table.
            checking_student = db.execute("SELECT * FROM students WHERE student_name = ?", line["student_name"])
            if len(checking_student) == 0:
                db.execute("INSERT INTO students (student_name) VALUES(?)", line["student_name"])
            # Second, houses and heads in house table.
            checking_house = db.execute("SELECT * FROM houses WHERE house = ?", line["house"])
            if len(checking_house) == 0:
                db.execute("INSERT INTO houses (house, head) VALUES(?, ?)", line["house"], line["head"])
    # Now that the two tables are populated, we will correlate the two in another table
    with open("students.csv", "r") as file:
        reader = csv.DictReader(file)
        for line in reader:
            checking_assignment = db.execute("SELECT * FROM assignments WHERE student_id = ?", line["id"])
            if len(checking_assignment) == 0:
                house_id = db.execute("SELECT id FROM houses WHERE house = ?", line["house"])
                db.execute("INSERT INTO assignments (student_id, house_id) VALUES (?, ?)", line["id"], house_id[0]["id"])

    print("Process Complete!")
    print()
    print()
    dataset = db.execute(
        "SELECT student_name, house, head FROM (SELECT * FROM assignments JOIN houses ON houses.id = assignments.house_id JOIN students ON students.id = assignments.student_id)")
    header = dataset[0].keys()
    rows = [x.values() for x in dataset]
    print(tabulate.tabulate(rows, header, tablefmt='grid'))


main()
