#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

/* Problem 17: If all the numbers from 1 to 1000 inclusive were written out in words,
   how many letters would be used? */


//Map of the number 1000, the word 'and', and 100 to the number of letters they contain
map<int, int> places = {
    {1000, 8},
    {-1, 3},
    {100, 7}
};

//Map of the digits 11-19 to the letters in their spellings
map<int, int> tens =
{
    {11, 6}, {12, 6},
    {13, 8}, {14, 8}, {18, 8}, {19, 8},
    {15, 7}, {16, 7},
    {17, 9}
};

//Map of 20-90 to their letters
map<int, int> aboveEqual20 =
{
    // twenty thirty eighty ninety
    {2, 6}, {3, 6}, {8,6}, {9, 6},

    // forty fifty sixty
    {4, 5}, {5, 5}, {6, 5},

    // seventy
    {7, 7}
};

//Map of the ones places to the number of letters
map<int, int> num =
{
    {1, 3}, {2, 3}, {6, 3}, {10, 3},
    {4, 4}, {5, 4}, {9, 4},
    {3, 5}, {7, 5}, {8, 5}
};

//Conversions
string
convert2Str(int x){
    stringstream ss;
    string ret;
    ss << x;
    ss >> ret;
    return ret;
}

int
convert2Int(string s){
    stringstream ss;
    int ret;
    ss << s;
    ss >> ret;
    return ret;
}

//Returns the most significant digit of a given integer
int
MSD(int x){
    string Strx = convert2Str(x);
    string retStr;
    retStr = Strx.substr(0, 1);
    return convert2Int(retStr);
}

//Returns everything after the most significant digit of a given integer
int
intTrunc(int x){
    string Strx = convert2Str(x);
    string retStr;
    retStr = Strx.substr(1);
    return convert2Int(retStr);
}

//Analyzes the numbers of letters of a given integer and returns the letters in its spelling
long long
analyzeNum(int x){
    long long ret = 0;
    int mostSig = 0;
    int truncatedNum = 0;
    if(x == 1000){
        //Add word 'one' and 'thousand' this is a special case
        ret += num[1];
        ret += places[1000];
    } else if(x >= 100 && x < 1000) {
        // Analyze most significant digit, add word, truncate MSD
        mostSig = MSD(x);
        ret += num[mostSig];
        truncatedNum = intTrunc(x);

        // Add word 'hundred'
        ret += places[100];

        //Special case -00
        if(truncatedNum == 0){
            ret += 0;
        }else if(num.find(truncatedNum) != num.end()){
            ret += places[-1];      //add 'and'
            ret += num[truncatedNum];
        } else if(tens.find(truncatedNum) != tens.end()){
            ret += places[-1];      //add 'and'
            //The key is found in the tens place; add it
            ret += tens[truncatedNum];
        } else {
            ret += places[-1];
            //The key is not found in tens; MSD it, add MSD, truncate, add truncation
            mostSig = MSD(truncatedNum);
            ret += aboveEqual20[mostSig];
            truncatedNum = intTrunc(truncatedNum);
            ret += num[truncatedNum];
        }
    } else if(x > 10 && x < 100){
        if(tens.find(x) != tens.end()){
            ret += tens[x];
        } else {
            mostSig = MSD(x);
            ret += aboveEqual20[mostSig];
            truncatedNum = intTrunc(x);
            ret += num[truncatedNum];
        }
    } else {
        //It's a single digit
        ret += num[x];
    }

    return ret;
}

long long
analyze(int upTo)
{
    long long ret = 0;
    for(int i = 1; i <= upTo; ++i){
        ret += analyzeNum(i);
    }
    return ret;
}

int main()
{
    long long letters;
    letters = analyze(1000);
    cout << "Number of letters: " << letters << endl;
    return 0;
}
