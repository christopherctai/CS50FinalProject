# TODO

from cs50 import get_int

# Get input in a do-while loop except it's Python

while True:
    height = int(get_int("Height: "))
    if height < 9 and height > 0:
        break

for i in (range(1, height + 1)):
    print(" " * (height - i), end="")
    print("#" * i, end="")
    print("  ", end="")
    print("#" * i, end="")
    print()

