# Import permutations
from itertools import permutations

#Problem 24: What is the millionth lexicographic permutation of the
#digits 0, 1, 2, 3, 4, 5, 6, 7, 8, and 9.

numbers = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]

def main():
	# Initial Count
	count = 1

	# Permutations returns a generator object so in order to print out
	# the value you have to iterator through it.
	for x in permutations(numbers):
	    # If it is the millionth element print it
	    if count == 1000000:
	        print(x)
	        break
	    else:
	        count += 1

main()