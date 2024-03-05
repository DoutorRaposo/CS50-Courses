import validators

def main():
    print(validate(input("What's your email address? ")))

def validate(s):
    return "Valid" if validators.email(s) else "Invalid"

if __name__ == "__main__":
    main()