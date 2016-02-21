#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <numeric>
#define LIMIT 28124

using namespace std;

/* Problem 23: Find the sum of all the positive integers which cannot be written as the
   sum of two abundant numbers. Abundant numbers are those whose proper divisors add up
   to a value greater than the number itself.*/

// sumDivisors: returns the sum of the proper divisors of x.
long
sumDivisors(long x)
{

    long ret = 0;

    if(x == 1){
        return 0;
    }

    vector<long> divs;
    divs.push_back(1);      //One divides into everything

    for(int i = 2; i <= floor(sqrt(x)); ++i){  //Only need to check up until sqrt
        if(x % i == 0){     //Add both divisor and quotient to get both divisors
            divs.push_back(i);
            divs.push_back(x / i);
        }
    }

    sort(divs.begin(), divs.end());

    //Start at the beginning of the sorted vector and stop once we reach duplicate elements (unique function)
    for(vector<long>::iterator it = divs.begin(); it != unique(divs.begin(), divs.end()); ++it){
        ret += *it;
    }

    return ret;
}

// isAbundant: returns whether or not x is an abundant number; an abundant number is a number
// in which the sum of all its proper divisors is greater than x itself.
bool
isAbundant(long x)
{
    if(sumDivisors(x) > x){
        return true;
    }
    return false;
}


// abundantSum: a vector of numbers which are sums of two abundant numbers
vector<long>
abundantSum(vector<long> &abuns, long lim)
{

    vector<long> ret;
    long sum = 0;
    for(int i = 0; i < abuns.size(); ++i){
        //Debugging:
        //cout << i << endl;
        for(int j = 0; j < abuns.size(); ++j){
            sum = abuns[i] + abuns[j];
            if(sum < LIMIT)
                ret.push_back(sum);
            else
                break;
        }
    }
    return ret;
}

int main()
{
    vector<long> abundants;

    //LIMIT given by problem
    for(long i = 1; i < LIMIT; ++i){
        if(isAbundant(i))
            abundants.push_back(i);
    }

    //Contains all numbers which can be written as the sum of two abundant numbers
    vector<long> sumofAbun;
    sumofAbun = abundantSum(abundants, LIMIT);

    sort(sumofAbun.begin(), sumofAbun.end());
    vector<long>::iterator itBeg = sumofAbun.begin();
    vector<long>::iterator itEnd = unique(sumofAbun.begin(), sumofAbun.end());

    long nonAbun = 0;
    int i = 1;
    //Add all the nonAbundant numbers
    while(itBeg != itEnd){
        if(i == *itBeg){
            advance(itBeg, 1);
            ++i;
        } else {
            nonAbun += i;
            ++i;
        }
    }


    cout << nonAbun << endl;
    return 0;
}
