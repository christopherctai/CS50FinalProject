from cs50 import get_string

sentence = get_string("Text: ")

word_count = 1
letter_count = 0
sentence_count = 0

for i in range(len(sentence)):
    if sentence[i] == '.' or sentence[i] == '!' or sentence[i] == '?':
        sentence_count += 1
    if sentence[i] == ' ':
        word_count += 1
    if sentence[i].isalpha():
        letter_count += 1

L = (letter_count / word_count) * 100
S = (sentence_count / word_count) * 100

index = round(0.0588 * L - 0.296 * S - 15.8)

if index > 15:
    print("Grade 16+")
elif index < 1:
    print("Before Grade 1")
else:
    print(f"Grade {index}")