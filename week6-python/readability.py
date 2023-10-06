# TODO
# Prompt user for text
text = input("Text: ")

# Count letters, words and sentences
wordlist = text.split()
letterlist = []
sentencelist = []
endlist = [".", "?", "!"]

for text in wordlist:
    for c in text:
        if c.isalpha():
            letterlist.append(c)
        elif c in endlist:
            sentencelist.append(c)

words = len(wordlist)
letters = len(letterlist)
sentences = len(sentencelist)

# Coleman-Liau index
l = letters / (words / 100)
s = sentences / (words / 100)
cli = round(0.0588 * l - 0.296 * s - 15.8)

# Print "Grade X"
if cli < 1:
    print("Before Grade 1")
elif cli >= 16:
    print("Grade 16+")
else:
    print(f"Grade {cli}")
