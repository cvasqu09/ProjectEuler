#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <numeric>
#include <math.h>
#include <list>

using namespace std;

// Problem 20: Find the sum of the digits in the number 100!

//Conversions
string
convertToStr(int value)
{
    stringstream ss;
    string ret;
     ss << value;
     ss >> ret;
     return ret;
}

int
convertToInt(string str)
{
    stringstream ss;
    int ret;
    ss << str;
    ss >> ret;
    return ret;
}

/* Converts a list of strings to a list of integers since digitizeStr
   is used to create a list of the string representation of each digit. */
list<int>
convertlist(list<string> listStrings)
{
    list<int> ret;
    for(list<string>::iterator it = listStrings.begin(); it != listStrings.end(); ++it){
        stringstream ss;
        int digit;
        ss << *it;
        ss >> digit;
        ret.push_back(digit);
    }

    return ret;
}

//Returns a list of strings which represent each digit in the given string
list<string>
digitizeStr(string str)
{
    list<string> ret;
    for(string::size_type i = 0; i != str.size(); ++i){
        ret.push_back(str.substr(i, 1));
    }
    return ret;
}

/* Returns the carry from truncating the least significant bit from a string
   representation of a number. */
int
truncate(string val, string &lastDig)
{
    //Single digit
    if(val.size() == 1){
        lastDig = val;
        return 0;
    }

    //Stores the least significant bit of the string val in lastDig
    lastDig = val.substr(val.size() - 1, 1);

    //Returning carry
    string ret;
    ret = val.substr(0, val.size() - 1);
    return convertToInt(ret);
}

/* Returns the list of integers that result from multiplying the currentlist parameter
   by the given parameter 'num'. This is used in the factorial findFact function */
list<int>
multiplylist(list<int> &currentlist, int num)
{
    list<string> retStr;
    int carry = 0;

    //Starting with the least significant bit in the list
    for(list<int>::reverse_iterator it = currentlist.rbegin(); it != currentlist.rend(); ++it){
        //Calculate the value from multiplying
        int value = *it * num + carry;

        string pushValue;
        string valueStr = convertToStr(value);

        //Carry is everything in valueStr except the least significant bit
        carry = truncate(valueStr, pushValue);
        //push the least significant bit
        retStr.push_front(pushValue);
    }

    //Push the carry if not zero
    if(carry != 0){
        string carryStr = convertToStr(carry);
        list<string> digitizeCarry;
        digitizeCarry = digitizeStr(carryStr);
        //Push the last digit first
        for(list<string>::reverse_iterator it = digitizeCarry.rbegin(); it != digitizeCarry.rend(); ++it){
            retStr.push_front(*it);
        }
    }

    return convertlist(retStr);
}

list<int>
findFact(int fact)
{
    list<int> ret;
    ret.push_back(1);

    //Invariant: after every iteration ret will be the digitized value of the current product.
    for(int i = fact; i != 1; --i){
        //Calculate factorial
        ret = multiplylist(ret, i);
    }

    return ret;
}

int main()
{
    int factorial = 100;
    long long sumOfFactorial = 0;
    list<int> digitsOfFactorial;
    digitsOfFactorial = findFact(factorial);

    //Add all the digits in our list
    sumOfFactorial = accumulate(digitsOfFactorial.begin(), digitsOfFactorial.end(), 0);
    cout << "The sum of the digits is: " << sumOfFactorial << endl;

    return 0;
}
