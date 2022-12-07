import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("'Incorrect Usage")
        sys.exit(1)
    # TODO: Read database file into a variable
    with open(sys.argv[1]) as file1:
        vcsv = list(csv.DictReader(file1))
        vcsv_head = dict(vcsv[0])
        strlist = list(vcsv_head.keys())[1:]
        #print(vcsv)
        #print(strlist)
    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2]) as file2:
        vtxt = file2.read()
        #print(vtxt)
    # TODO: Find longest match of each STR in DNA sequence
    longest = {}
    for x in strlist:
        longest[x] = longest_match(vtxt, x)
    #print(longest)
    # TODO: Check database for matching profiles
    with open(sys.argv[1]) as file2:
        vcsv2 = csv.DictReader(file2)
        str_count = len(longest)
        for row in vcsv2:
            match_count = 0
            for line in longest:
                #print(f"longestline: {longest[line]}")
                #print(f"rowline: {row[line]}")
                if int(longest[line]) != int(row[line]):
                    break
                else:
                    match_count += 1
                    #print(match_count)
                    #print(str_count)
                if match_count == str_count:
                    print(row['name'])
                    sys.exit(0)
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
