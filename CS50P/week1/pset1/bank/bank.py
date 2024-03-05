answer = input("Greeting: ")

words_list = answer.lower().split()

if words_list[0] != "hello" and words_list[0] != "hello,":
    if words_list[0][0] == 'h':
        print("$20")
    else:
        print("$100")
else:
    print("$0")