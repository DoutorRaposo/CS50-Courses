import sys
from pyfiglet import Figlet

figlet = Figlet()

fonts_list = figlet.getFonts()

if len(sys.argv) == 2 or len(sys.argv) > 3 or (sys.argv[1] != '-f' and sys.argv[1] != '-font') or sys.argv[2] not in fonts_list:
    sys.exit("Invalid usage")

figlet.setFont(font=sys.argv[2])

text = input("Input: ")

print(figlet.renderText(text))