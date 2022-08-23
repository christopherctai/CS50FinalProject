from cs50 import get_string

sentence = get_string("Text: ")

# Define the count for words, letters, and sentences
word_count = 1
letter_count = 0
sentence_count = 0

# Count the words, letters, and sentences
for i in range(len(sentence)):
    if sentence[i] == '.' or sentence[i] == '!' or sentence[i] == '?':
        sentence_count += 1
    if sentence[i] == ' ':
        word_count += 1
    if sentence[i].isalpha():
        letter_count += 1

# Use those counts to find the average letters for 100 words and average sentences for 100 words
L = (letter_count / word_count) * 100
S = (sentence_count / word_count) * 100

# Find index value for what grade level this is
index = round(0.0588 * L - 0.296 * S - 15.8)

# Print corresponding grade level 
if index > 15:
    print("Grade 16+")
elif index < 1:
    print("Before Grade 1")
else:
    print(f"Grade {index}")