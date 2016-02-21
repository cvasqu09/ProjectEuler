## Chris Vasquez
## R11079698
## Lab Section 502
## Final Project

from math import *

## Be patient when running the program. Not all of the functions are run optimally however all of them are solved!
## Please email me if you have any concerns or need clarification regarding any of the functions implemented.

## 1. Sum of the multiples of 3 and 5 less than 1000.
## sum_multiples3_and_5(): Takes no arguments -> Integer
## The function sum_multiples_3_and_5 takes no arguments and simply returns and integer which represents the sum
## of the multiples of 3 and 5 which are less than 1000. A for loop is used since the exact number of times that the
## is going to be run is know. For every value in the range [1,1000) if the value is a multiple of 3 or 5 then the
## sum, s, becomes the previous sum plus this value.
def sum_multiples_3_and_5():
    s = 0
    for i in range(1, 1000):
        if i % 3 == 0 or i % 5 == 0:
            s = s + i
    return s

## Here is just the same function expressed using a list comprehension
# sum_multiples_3_and_5_listcomp(): Takes no arguments -> Integer
# def sum_multiples_3_and_5_listcomp():
#     return sum(x for x in range(1,1000) if x % 3 == 0 or x % 5 == 0)

print("1. The sum of the multiples of 3 and 5 less than 1000 is {}.".format(sum_multiples_3_and_5()))




## 2. Sum of the Even Fibonacci Numbers Less than 4 Million.
## This function calculates the sum of the even fibonacci numbers less than 4 million.

## fibonacci_generator(): Takes no arguments -> Integer
## This generates subsequent fibonacci numbers in the sum_of_even_fibs() function when x is called. The fibonacci bound
## is to produce all x less than 4 million. The loop will stop generating numbers once x reaches a value greater than
## or equal to 4 million.
def fibonacci_generator():
    fibonacci_bound = 4000000
    x,y = 1,2
    while x < fibonacci_bound:
        yield x
        x,y = y,y+x

## sum_of_even_fibs(): Takes no arguments -> An integer
## Note that this function uses the fibonacci generator function in order to sum up the even terms and is
## probably not a good idea to solve recursively given the amount of elements in a list if the fibonacci numbers
## were stored into a list.
def sum_of_even_fibs():
    return sum([x for x in fibonacci_generator() if x % 2 == 0])

print("2. The sum of the even fibonacci terms when starting with 1 and 2 less than 4 million is {}." \
        .format(sum_of_even_fibs()))




## 3. Largest Prime Factor of 600851475143
## This function is to calculate the largest prime factor of 600851475143. It takes no arguments since the number
## that is going to be calculated will always be the same.

## Helper function for the prime factor of 600851475143.
## is_prime(Z): Integer -> Boolean
## If Z is an integer then is_prime(Z) is True if and only if Z is a prime number. The function takes the square root
## of the input number and with the floor function rounds it either down or sets it equal to the square root if Z has
## an exact value for the square root, adds one, and and sets this as its bound. The purpose for this is to optimize
## the check and not have the function loop over values greater than the square root since an
## integer will have no factors greater than its square root. The loop then checks if Z is divisible by any of the
## integers in the range(3,bound,2). This starts with three and increments by two since every positive even integer
## except for two is a composite number.
def is_prime(Z):
    if Z < 2:
        return False
    elif Z == 2:
        return True
    elif Z % 2 == 0:
        return False
    else:
        bound = floor(sqrt(Z)) + 1
        for i in range(3,bound,2):
            if Z % i == 0:
                return False
        return True


## prime_factor_of_600851475143(): Takes no arguments -> Integer
## Initially, i = 2 and n = 600851475143. While n does not equal 1 the loop will continue. If n is divisible by i
## with no remainders then n will be assigned the value of n divided by i. In addition, a list of divisors will
## add the value of i if n is divisible by i with no remainders. Otherwise, the value of n will stay the same
## and the value of i will increment by 1. This loop will always terminate since n will eventually be one because i
## will eventually become n if n is prime. After this, the function creates another list from the divisors list
## which only keeps the prime divisors. The greatest prime divisor will be the last element of the prime_divisors
## list so the end of the function will return this numerical value.

def prime_factor_600851475143():
    i = 2
    n = 600851475143
    divisors = []
    while n != 1:
        if n % i == 0:
            divisors.append(i)
            n = n//i
        else:
            i += 1
    prime_divisors = [x for x in divisors if is_prime(x)]
    largest_prime = prime_divisors[-1]
    return largest_prime

print("3. The largest prime factor of 600851475143 is {}.".format(prime_factor_600851475143()))


## 4. Largest 3-digit Palindromic Number.
## This function determines the largest value of a palindromic number created from the product of two 3 digit numbers.

## is_palindrome(Z): Integer -> Boolean
## If Z is an integer then is_palindrome(Z) is True if and only if the integer Z reads the same forwards and backwards.
## Note that this is a helper function for the palindromic_number() function and it for the num_backward portion of it
## it uses an extended slice to read and return the string of the integer Z backwards. If the integer is read the same
## forward as backward then it is a palindrome.
def is_palindrome(Z):
    num_forward = str(Z)
    num_backward = str(Z)[::-1]
    if num_forward == num_backward:
        return True
    else:
        return False
# palindromic_number(): Takes no arguments -> Integer
# The function palindromic_number() takes no arguments and returns the largest palindromic number created by the
# product of two 3 digit numbers. Note that the range should be [100,1000) and x and y are evaluated in this range.
# If the product of the x and y is a palindrome and the product is greater than the current value stored as
# palindrome, then palindrome takes on the value of the product of x and y. This keeps the max value palindrome
# and returns this value at the end of the function.
def palindromic_number():
    palindrome = 0
    x = 100
    y = 100
    for x in range(100,1000):
        for y in range(100,1000):
            if is_palindrome(x*y) and x*y > palindrome:
                palindrome = x * y
    return palindrome
print("4. The largest palindromic number made from the product of two 3 digit numbers is {}."
        .format(palindromic_number()))


## 5. First Integer Divisible by 1 to 20.
## The purpose of this function is to determine the value of the first number which is divisible by all the numbers form
## 1 to 20.

## The purpose for i equalling 2520 is because this was the given number that was divisible by the numbers 1 to 10 so
## the number that is divisible by the numbers 1 to 20 must be greater than that. In addition the increments of 20
## are because the last to digits of the the number must be 0-0, 2-0, 4-0, 6-0, or 8-0 for the number to be divisible
## by 20. Therefore the number cannot end with anything but a zero. If the number is divisible by 20 then there is no
## need to check if it is divisible by 2,4,5, and 10 since they are divisors of 20. If the number is divisible by
## 18 then there is no need to check if the number is divisible by 3,6, and 9 since they are also divisors of 18. If
## the number is divisible by 16 then there is no need to check for divisibility by 8. If divisibility by 14 is possible
## then divisibility by 7 is possible as well. So the only numbers that the number needs to be checked for divisibility
## by is 11,12,13,14,15,16,17,18,19 and 20 and i can also be incremented by increments of 20.

## number_divisible_by_1_to_20(): Takes no arguments -> Integer
def number_divisible_by_1_to_20():
    answer = 0
    i = 2520
    while answer == 0:
        if i % 11 == 0 and i % 12 == 0 and i % 13 == 0 and i % 14 == 0 and i % 15 == 0 and i % 16 == 0 and i % 17 == 0 \
                and i % 18 == 0 and i % 19 == 0 and i % 20 == 0:
            answer = i
        else:
            i += 20
    return answer
print("5. The smallest number divisible by the numbers 1 to 20 is {}.".format(number_divisible_by_1_to_20()))




## 6. Difference of Square of the Sum and the Sum of the Squares
## The purpose of this function is to calculate the sum of the squares and the square of the sums of the first 100
## natural numbers and output the difference between the two.

## square_of_sum(): Takes no arguments -> Natural Number
## The function is broken into three parts the first of which takes no arguments and outputs the square of the sum of
## the first 100 natural numbers beginning with 1.
def square_of_sum():
    s = 0
    for x in range(1,101):
        s = s + x
    return s ** 2

## sum_of_squares(): Takes no arguments -> Natural Number
## This is the second part that calculates the sum of the squares of the first 100 numbers beginning with 1.
def sum_of_squares():
    squares = []
    for x in range(1,101):
        square = x ** 2
        squares.append(square)
    return sum(squares)

## difference_of_square_of_sum_and_sum_of_squares(): Takes no arguments -> Integer
## Here is the final part which actually calculates the difference between the two previously calculated values.
def difference_of_square_of_sum_and_sum_of_squares():
    return (square_of_sum() - sum_of_squares())

print("6. The difference of the square of the sum and the sum of the squares of the the natural numbers from 1 to"
            " 100 is {}.".format(difference_of_square_of_sum_and_sum_of_squares()))




## 7. 10001st Prime Number
## This function determines the 10001st prime number.

## prime_number_10001(): Takes no arguments -> Integer
## The following loop goes on until count reaches 10001. Initially the count is set equal to one since 2 is part
## of the list of primes and i is started at 3 so that the loop can skip over the evens after two so the loop will
## count how many primes have been calculated so far, i is set to 3 so that the loop can increment by two and skip over
## the even values since all evens after two will be composite, and a list of primes is constructed with two
## already in it. As a result as the loop goes on it will append i whenever it is prime.
## If the number is prime then the count will increase, a list of primes will add the value of i, and i will
## increment by 2. Otherwise, the i will increment by two. The last element of the list will be returned and should
## be the 10001st prime number.
def prime_number_10001():
    count = 1
    i = 3
    primes = [2]
    while count != 10001:
        if is_prime(i):
            count += 1
            primes.append(i)
            i += 2
        else:
            i += 2
    return primes[-1]

print("7. The 10001st prime number is {}.".format(prime_number_10001()))




# 8. Largest Product of Thirteen Adjacent Numbers:
## This is just the 1000 digits provided.
string_of_digits = "73167176531330624919225119674426574742355349194934"\
    "96983520312774506326239578318016984801869478851843"\
    "85861560789112949495459501737958331952853208805511"\
    "12540698747158523863050715693290963295227443043557"\
    "66896648950445244523161731856403098711121722383113"\
    "62229893423380308135336276614282806444486645238749"\
    "30358907296290491560440772390713810515859307960866"\
    "70172427121883998797908792274921901699720888093776"\
    "65727333001053367881220235421809751254540594752243"\
    "52584907711670556013604839586446706324415722155397"\
    "53697817977846174064955149290862569321978468622482"\
    "83972241375657056057490261407972968652414535100474"\
    "82166370484403199890008895243450658541227588666881"\
    "16427171479924442928230863465674813919123162824586"\
    "17866458359124566529476545682848912883142607690042"\
    "24219022671055626321111109370544217506941658960408"\
    "07198403850962455444362981230987879927244284909188"\
    "84580156166097919133875499200524063689912560717606"\
    "05886116467109405077541002256983155200055935729725"\
    "71636269561882670428252483600823257530420752963450"

## Note that the string of digits was converted into a list consisting of 1000 integers.
digits = [int(x) for x in string_of_digits]

## This is a helper function for the largest_product which simply computes the product of a given list of integers
## using a for loop which returns the value of the product once it has been computed.
## product(List): List of integers -> Integer
def product(list):
    p = 1
    for x in list:
        p = p * x
    return p

## largest_product(string): String -> Integer
## The largest_product function takes in a string and returns an integer. Initially i (initial) and f (final) are set
## to 0 and 13 respectively. This is to essentially create the chunk of 13 adjacent digits that is implemented during
## the for loop. A variable of the largest_value is to store the numerical value of the largest product throughout
## the loop. The for loop is implemented in the range[0,1000-13) because at 1000-13 the last set of 13 adjacent digits
## will be evaluated. The if/else statement in the for loop checks if the product of the 13 adjacent digits is greater
## than the value stored in the largest_value. If it is then the largest_value becomes the product which was greater
## than the previous largest_value variable and both i and f are incremented by 1 to go onto the next 13 adjacent
## digits. Otherwise, the value of i and f are just incremented by one to go onto the next 13 adjacent digits.
## At the end of the loop the largest_value will be returned and should be the largest product of 13 adjacent digits.
def largest_product(string):
    i,f = 0,13
    largest_value = 0
    for i in range(0,1000-13):
        if product(digits[i:f]) > largest_value:
            largest_value = product(digits[i:f])
            i,f = i+1,f+1
        else:
            i,f = i+1,f+1
    return largest_value
print("8. The largest product of 13 adjacent digits in the 1000 digit number is {}."
        .format(largest_product(digits)))




## 9. Pythagorean Triplet Equal to 1000

## pythagorean_triplet(): Takes no arguments -> Three Tuple of Integers
## Initially, the values of a,b, and c are set equal to 1. There is a nest of for loops in which a in
## range[1,500) and b in range[1,500). If a and b are 500 a triangle cannot be constructed since c would have to be
## equal to zero in order for a + b + c to equal 1000 so that this range should be sufficient to determine the
## triplet. The value of c is set to the difference of 1000 and the sum of a and b. The loop then checks to see if
## the sum of the squares of a and b are equal to the square of c. If it is not then b is incremented by 1 otherwise if
## it is then a tuple of three integers is returned in which a,b, and c are returned.
def pythagorean_triplet():
    a = 1
    b = 1
    c = 1
    for a in range(1,500):
        for b in range(1,500):
            c = 1000-(a+b)
            if a**2+b**2 != c**2:
                b += 1
            else:
                return a,b,c
print("9. The pythagorean triplet in which a+b+c=1000 is {}.".format((pythagorean_triplet())))

## 10. Sum of Prime Numbers Below 2 Million.
## This function calculates the sum of all the primes below two million.

## primes_generator(): Takes no arguments -> Integer
## This is a helper function for the primes_below_two_million which generates the primes
## below two million. Initially i is set to 3 since every even number after two is composite and if i is prime then
## the generator yields i. Otherwise i is incremented by 2 (the next odd number).
def primes_generator():
    i = 3
    while i < 2000000:
        if is_prime(i):
            yield i
            i += 2
        else:
            i += 2

## primes_below_two_million(): Takes no arguments -> Integer
## The primes_below_two_million() is a function that works in collaboration with the primes_generator(). For every
## prime number which is yielded in the primes_generator() the sum is calculated. The initial value of 2 must be added
## as well since the primes_generator() initially starts with three so that all the odd numbers can be checked since
## every even number after 2 is a composite number.
def primes_below_two_million():
    return 2 + sum([x for x in primes_generator()])

print("10. The sum of the primes less than 2 million is {}.".format(primes_below_two_million()))