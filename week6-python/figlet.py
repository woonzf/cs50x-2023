from sys import argv, exit
from pyfiglet import Figlet
from random import choice

if len(argv) not in [1, 3] or argv[1] not in ["-f", "--font"]:
    print("Invalid usage")
    exit(1)

figlet = Figlet()
fontlist = figlet.getFonts()

if len(argv) == 3:
    if argv[2] in fontlist:
        f = argv[2]
    else:
        print("Invalid usage")
        exit(1)

if len(argv) == 1:
    f = choice(fontlist)

text = input("Text: ")
figlet.setFont(font=f)
print(figlet.renderText(text))
exit(0)