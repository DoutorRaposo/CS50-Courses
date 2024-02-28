vowels = ["a", "e", "i", "o", "u"]
user_input = input("Input: ")
print("Output: ", end="")
for c in user_input:
    if c.lower() not in vowels:
        print(c, end="")
print()