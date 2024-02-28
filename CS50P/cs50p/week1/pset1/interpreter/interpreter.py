expression = input("Expression: ")
x, y, z = expression.split()

match y:
    case "+":
        print("{:.1f}".format(int(x) + int(z)))
    case "-":
        print("{:.1f}".format(int(x) - int(z)))
    case "/":
        print("{:.1f}".format(int(x) / int(z)))
    case "*":
        print("{:.1f}".format(int(x) * int(z)))