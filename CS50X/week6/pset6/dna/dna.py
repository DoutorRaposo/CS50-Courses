import csv
import sys


def main():

    # Check if it's the correct number of arguments.
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py str_counts.csv sequence.txt")

    # Create a list of dicts
    database = []
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        for row in reader:
            database.append(row)

    # Reads to a string a file
    sequence = ""
    with open(sys.argv[2], 'r') as file:
        sequence = file.read()

    # Create a list of STRs
    subsequence = list(database[0].keys())
    # I used the database for getting the keys, so I popped out the 'name' variable
    subsequence.pop(0)
    # This is just so the code is neat, so we know the number of keys/subsequences
    keys_n = len(subsequence)
    # A list of longest matches
    longest_matches = []
    for keys in range(keys_n):
        longest_matches.append(longest_match(sequence, subsequence[keys]))
    # The profile of the person in the sequences folder is translated to a dict to have a subsequence as a key and the longest matches as values for each keys.
    profile = dict()

    for times in range(keys_n):
        profile[subsequence[times]] = longest_matches[times]
    # We will check each of the dicts if the key matches to the key matched in the profile for the same key. If all keys matches, print the name and return.
    for row in range(len(database)):
        match = 0
        for keys in range(keys_n):
            if int(database[row].get(subsequence[keys])) == profile.get(subsequence[keys]):
                match += 1
            if match == keys_n:
                print(database[row].get('name'))
                return

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
