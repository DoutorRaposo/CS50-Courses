import os

sqlq = 13

for i in range(sqlq):
    os.system(f"cat {i + 1}.sql | sqlite3 movies.db > output{i + 1}.txt")

for i in range(sqlq):
    with open(f"output{i + 1}.txt") as fp:
        x = len(fp.readlines())
        print(f'Total lines in {i + 1}:', x - 4)