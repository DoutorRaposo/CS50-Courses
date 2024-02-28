list = {}
while True:
    try:
        item = input().upper()
        if item not in list.keys():
            list[item] = 1
        else:
            list[item] += 1
    except EOFError:
        for items in sorted(list):
            print(list[items], items)
        exit()