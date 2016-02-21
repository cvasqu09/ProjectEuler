#include <iostream>

using namespace std;

//Find the starting number that under a million produces the longest chain
//following the iterative sequence defined for the set of positive integers:
// n -> n/2 if n is even
// n -> 3n + 1 if n is odd


long long
collatz(long long x)
{
    //Chain starts at one
    long long length = 1;

    while(x != 1){
        if(x % 2 == 0){ // n -> n/2 if even
            x = x/2;
            length += 1;
        } else  {   // n-> 3n+1 if odd
            x = 3 * x + 1;
            length += 1;
        }
    }
    return length;
}


int main()
{
    long long longest = 0;
    long long number = 0;
    for(int i = 1; i < 1000000; ++i){
        if(collatz(i) > longest){
            longest = collatz(i);
            number = i;
        }
    }
    cout << "Longest chain: " << longest << endl;
    cout << "Number: " << number;

}
