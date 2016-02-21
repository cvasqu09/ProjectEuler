#include <iostream>
#include <math.h>
#include <algorithm>
#include <map>
#include <vector>
#include <numeric>

using namespace std;

/* Problem 21: Find the sum of all the amicable numbers under 10000
   Amicable pairs are those whose proper divisors equal each other such
   that both numbers are not equivalent*/

//Returns true if a number is even
bool
isEven(int x){
    return x % 2 == 0;
}

//isPrime: returns whether or not x is prime.
bool
isPrime(int x)
{
    //Only need to check up until the sqrt of x
    int check = floor(sqrt(x));
    if(x % 2 == 0 && x != 2){
        return false;
    } else {
        int i = 3;
        while(i <= check && x != 2){
            if(x % i == 0)
                return false;
            i += 2;
        }
    }
    return true;
}

//Returns the sum of the proper divisors of x
int
pDivisorsSum(int x)
{

    //Debug: cout << "pdiv" << endl;

    int sum = 0;
    int check = floor(sqrt(x));

    int i = 1;
    while(i <= check){
        if(!isEven(x) && isEven(i)){ //If x is odd and divisor is even, skip
            ++i;
        } else if(x % i == 0) {
            if(i * i == x){          //Square is a special case
                sum += i;
                ++i;
            } else if(i == 1){       //One itself is also a special case
                sum += i;            //because we do not add the number itself
                ++i;
            } else {                //Add both the number in the lower sqrt and higher sqrt
                sum += i;
                sum += x/i;
                ++i;
            }
        } else {
            ++i;
        }
    }
    //Debug: cout << x << "\t" << sum << endl;
    return sum;
}


int main()
{
    vector<int> amicables;

    //Can start with 4 since 2 and 3 are prime
    for(int i = 4; i != 10000; ++i){
        //Don't check prime numbers; avoid having proper divisors equal each other
        if(!isPrime(i)){
            int pDivSum = pDivisorsSum(i);
            //If amicable and is not perfect
            if(i == pDivisorsSum(pDivSum) && i != pDivSum)
                amicables.push_back(i);
        }
    }

    /* Debugging
    cout << "amicable: " << endl;
    for(vector<int>::iterator it = amicables.begin(); it != amicables.end(); ++it){
        cout << *it << endl;
    } */

    cout << "Sum of amicable numbers: " << accumulate(amicables.begin(), amicables.end(), 0);

    return 0;
}
