# TODO

from cs50 import get_int

# Get input in a do-while loop except it's Python
while True:
    height = int(get_int("Height: "))
    if height < 9 and height > 0:
        break

# Do something height number of times.
# First, print out the most amount of spaces
# Then, print out the number of hashes for the first pyramid
# Then, print out "  " to create the gap in between the pyramids
# Then, print out the number of hashes for the second pyramid
# Then, print an extra line (\n) at the end for the next row
for i in (range(1, height + 1)):
    print(" " * (height - i), end="")
    print("#" * i, end="")
    print("  ", end="")
    print("#" * i, end="")
    print()

