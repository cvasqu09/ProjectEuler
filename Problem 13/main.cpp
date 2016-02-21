#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <list>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>

//Problem 13: Work out the first ten digits of the sum of the following
//one-hundred 50-digit numbers

//Note that this requires that the c++11 standard compiler be used in order
//for the <string>.back() method to be used

using namespace std;


string convertToStr(int x)
{
    stringstream ss;
    string ret = "";
    ss << x;
    ss >> ret;
    return ret;
}

int convertToInt(string str)
{
    stringstream ss;
    int ret = 0;
    ss << str;
    ss >> ret;
    return ret;
}


//Calculates the sum of the digits in a given vector, stores the least
//significant element and returns the carry
int carryCalculate (vector<vector<int> >& vecN, int elem, int carry, list<char>& store)
{
    // Calculate sum of the digits in elem column
    int sum = carry;
    for(vector<vector<int> >::iterator it = vecN.begin(); it != vecN.end(); ++it){
        sum += (*it)[elem];
    }

    // Convert sum to string
    string answerStr;
    answerStr = convertToStr(sum);

    // Push only the last element (least significant digit
    store.push_front(answerStr.back());

    // Create a string that represents the carry
    string carryStr;
    carryStr = answerStr.substr(0, answerStr.size() - 1);

    // Convert carryStr to int
    int carryRet = 0;
    carryRet = convertToInt(carryStr);
    return carryRet;

}


int main()
{
    ifstream numbers;
    numbers.open("numbers.txt");

    // Push back each line split into 50 individual integers.
    vector<vector<int> > vecNum;
    string line;
    while(getline(numbers, line)){
        vector<int> splitNum;

        for(string::iterator it = line.begin(); it != line.end(); ++it){
            int x;

            // Converting each character string into integer
            stringstream ss;
            ss << *it;
            ss >> x;
            splitNum.push_back(x);
        }

        //Push back onto vector of split numbers
        vecNum.push_back(splitNum);
    }


    // Check for file import. Notice that it couts each individual integer.
    for(vector<vector<int> >::iterator it = vecNum.begin(); it != vecNum.end(); ++it){
        for(vector<int>::iterator iter = (*it).begin(); iter != (*it).end(); ++iter)
            cout << *iter;
        cout <<endl;
    }

    // Create list of characters that represent the addition of all 50 digit long numbers
    list<char> answerVec;
    int carry = 0;
    for(int i = 49; i >= 0; --i){
        carry = carryCalculate(vecNum, i, carry, answerVec);
    }

    // You have to append and push the carry to the answer vector as well since it is not done
    // after the previous loop is done. Start from the least significant bit and push to the front
    // of the vector so that it maintains the proper order.
    string carryString = convertToStr(carry);
    for(string::reverse_iterator it = carryString.rbegin(); it != carryString.rend(); ++it)
        answerVec.push_front(*it);


    // Convert the list of characters into a string and output that string. Having the string allows that
    // the answer may be copied and pasted.
    string first10;
    list<char>::iterator iter = answerVec.begin();
    for(int i = 0; i < 10; ++i){
        first10.push_back(*iter);
        advance(iter, 1);
    }

    cout << "Answer is: " << first10 << endl;

    numbers.close();

    return 0;
}
