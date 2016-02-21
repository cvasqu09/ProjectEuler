#Problem 25: What is the index of the first term in the Fibonacci
#sequence to contain 1000 digits

#fibGen: takes an integer for the index of the fibonacci sequence,
#the previous number in the fibonacci sequence(n) and the next 
#number in the fibonacci sequence(m).
def fibGen(index = 1, n = 1, m = 1):
    while True:
        temp1 = n
        if index == 1 or index == 2:
            index += 1
            yield 1

        else:
            index += 1
            yield n + m
            # These two statements advance to the next two fib
            # Add the difference between n and m so that n is m
            n += m - n
            # m = m + n, generates next fibonacci number
            m += temp1


count = 1
for x in fibGen(count, 1, 1):
    if len(str(x)) == 1000: #Stop when the number is 1000 digits
        print("count", count)
        break
    else:
        count += 1 #increment count to next index
    

