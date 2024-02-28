greeting = input("Greeting: ")

words = greeting.lower().split()  # splits creates only a copy

if words[0] != "hello" and words[0] != "hello,":
    if words[0][0] == 'h':
        print("$20")
    else:
        print("$100")
else:
    print("$0")