from cs50 import get_string

# TODO
#Get text
text = get_string("Text: ")
#Count letters
letters = len([l for l in text if l.isalpha()])
#print(f"letters: {letters}")
#Count words
words = len(text.split())
#print(f"words: {words}")
#Count sentences
sentences = sum([text.count('.'), text.count('!'), text.count('?')])
#print(f"sentences: {sentences}")
#Coleman-Liau index
cli = (0.0588 * (letters / (words/100))) - 0.296 * (sentences / (words/100)) - 15.8
grade = round(cli)
if grade >= 1 and grade <= 16:
    print(f"Grade {grade}")
elif grade <1:
    print("Before Grade 1")
else:
    print("Grade 16+")
