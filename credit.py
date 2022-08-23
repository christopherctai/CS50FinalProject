from cs50 import get_string
import re
import sys

# Get user input and verify that it could be a legit number using regular expressions
while True:
    card_number = get_string("Number: ")
    regexp = re.compile(r'(5[1-5]|3[47]|4)\d{12,15}')
    if not regexp.search(card_number):
        print("INVALID")
        sys.exit(0)
    if regexp.search(card_number):
        break

# Create two lists starting with the second_to_last_digit and starting with the last_digit
last_digit_list = []
second_to_last_digit_list = []

# Append the correct items to the second_to_last_digit_list
for i in range(2, len(card_number), 2):
    second_to_last_digit_list.append(card_number[len(card_number) - i])
if len(card_number) % 2 == 0:
    second_to_last_digit_list.append(card_number[0])

# Append the correct items to the last_digit_list
for j in range(1, len(card_number), 2):
    last_digit_list.append(card_number[len(card_number) - j])
if not len(card_number) % 2 == 0:
    last_digit_list.append(card_number[0])

# Find the checksum value to see if it ends in 0

# Initiate the sums that will be added to make the checksum
sum1 = 0
sum2 = 0

# Calculate the sums
for x in range(len(last_digit_list)):
    last_digit = int(last_digit_list[x])
    sum1 += last_digit

for y in range(len(second_to_last_digit_list)):
    second_to_last_digit = int(second_to_last_digit_list[y]) * 2
    second_to_last_digit = ((second_to_last_digit - second_to_last_digit % 10) / 10) + second_to_last_digit % 10
    sum2 += second_to_last_digit

# Calculate the checksum
checksum = (sum1 + sum2) % 10

# Print the corresponding correct card or Invalid if the checksum != 0
if checksum == 0:
    if int(card_number[0]) == 3:
        print("AMEX")
    elif int(card_number[0]) == 4:
        print("VISA")
    elif int(card_number[0]) == 5:
        print("MASTERCARD")
    else:
        print("INVALID")
else:
    print("INVALID")

"""
for index, digit in enumerate(last_digit_list):
    last_digit = digit
    last_index = index
"""

"""int_card_number = int(card_number)
last_digit = int_card_number % 10
second_to_last_digit = (int_card_number - last_digit) % 10

print(last_digit)
print(second_to_last_digit)"""

# Find Checksum, convert the user input into an int
int_card_number = int(card_number)

real_numbers = '''
378282246310005,
371449635398431,
5555555555554444,
5105105105105100,
4111111111111111,
4012888888881881,
1234567890
'''