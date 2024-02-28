import sys
from pyfiglet import Figlet
import random

figlet = Figlet()

fonts_list = figlet.getFonts()

if len(sys.argv) == 1:
    figlet.setFont(font=random.choice(fonts_list))
elif len(sys.argv) == 3 and (sys.argv[1] == "-f" or sys.argv[1] == "--font"):
    figlet.setFont(font=sys.argv[2])
else:
    sys.exit("Invalid usage")

text = input("Input: ")

print(figlet.renderText(text))
