#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <sstream>

// Problem 16: What is the sum of the digits of the number 2 to the power of 1000

// Note that this program only works with 2 as the base
// Calculates the sum of the digits of 2 to the power a of an positive integer
using namespace std;

// Converts int to string
string
convert_Str(int x){
    string ret;
    stringstream xss;
    xss << x;
    xss >> ret;
    return ret;
}


// Converts string to int
int
convert_Int(string str)
{
    int ret;
    stringstream strss;
    strss << str;
    strss >> ret;
    return ret;
}


// Calculates the carry
int
calculateCarry(int fullNum)
{

    string fullNumStr;
    fullNumStr = convert_Str(fullNum);          //Convert full integer to string
    string carry;
    carry = fullNumStr.substr(0, fullNumStr.size() - 1); // Carry will be everything except last character
    return convert_Int(carry);                  //Return the carry converted to integer
}


/* Doubles the digits of every integer in the list accounting for carries if necessary
   Note that the list represents an actual number. This is to avoid overflow errors
   using primitive types such as long and int when calculating the large power. */
void
doubledigits(list<int>& dFN)
{
    // Initial carry value
    int carry = 0;

    // Starting from the back of the list
    for(list<int>::reverse_iterator it = dFN.rbegin(); it != dFN.rend(); ++it){
        // Double the integer and add the carry
        int doubled = (*it) * 2 + carry;

        // If you need to calculate the carry else carry is zero
        if(doubled >= 10){
            carry = calculateCarry(doubled);
            string doubledStr = convert_Str(doubled);
            string digit = doubledStr.substr(doubledStr.size() - 1, 1);
            *it = convert_Int(digit);
        } else {
            carry = 0;
            *it = doubled;
        }
    }

    // Push the final carry if one is necessary
    if(carry != 0)
        dFN.push_front(carry);
}


// Will calculate the sum of the digits of 2 to the power of the given power
int
calculateSum(int power)
{
    list<int> digitsFN = {1};
    for(int i = 0; i != power; ++i){        //Double the digits while the power has not been reached
        doubledigits(digitsFN);
    }

    int ret = 0;
    //Calculate the sum of all the digits in the list.
    for(list<int>::iterator it = digitsFN.begin(); it != digitsFN.end(); ++it){
        ret += *it;
    }

    return ret;
}

int main()
{
    int answer;
    answer = calculateSum(1000);
    cout << "Answer: " << answer << endl;
    return 0;
}
