import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py databases/<insert>.csv sequences/<insert>.txt")

    # TODO: Read database file into a variable
    database = []

    with open(sys.argv[1], "r") as databasefile:
        reader = csv.DictReader(databasefile)
        for row in reader:
            database.append(row)

    test_database = []
    with open(sys.argv[1], "r") as databasefile:
        reader = csv.reader(databasefile)
        for row in reader:
            test_database.append(row)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as sequencefile:
        textsequence = sequencefile.read()

    # TODO: Find longest match of each STR in DNA sequence
    longest_matches = []

    for i in database[0]:
        if i == 'name':
            continue
        x = longest_match(textsequence, i)
        longest_matches.append(x)

    # TODO: Check database for matching profiles
    y = 0
    for i in database:
        values = list(i.values())
        del values[0]
        int_values = [int(x) for x in values]
        if int_values == longest_matches:
            values = list(i.values())
            y = 1
            print(values[0])

    if y == 0:
        print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
