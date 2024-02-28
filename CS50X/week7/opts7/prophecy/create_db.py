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
    db.execute("SELECT * FROM students")
    print("Schema applied.")
    #except RuntimeError as error:
        #os.system(f"cat schema.sql | sqlite3 {sys.argv[1]}")
        #print("Schema not applied before. Applied and proceeding.")
main()