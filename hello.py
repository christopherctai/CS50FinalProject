# TODO

# Import the correct function from cs50. We want to get the user's input for their name
from cs50 import get_string

# Get the user's name, then print a string where it's Hello and then their name 
name = get_string("What's your name? ")
print(f"Hello, {name}")