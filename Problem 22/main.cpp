#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <ctype.h>
#include <map>
#include <numeric>

using namespace std;

/* Problem 22: Given the text file "names.txt" containing over five-thousand first names
   begin by sorting into alphabetical order. Find the name score by finding the sum of all
   the values in the name and multiplying it by its position in the list. What is the total of all
   the name scores in the file? */

//Returns true if c is alphabetical character
bool
alpha(const char c)
{
    return isalpha(c);
}

//Returns true if c is non alphabetical
bool
notalpha(const char c)
{
    return !alpha(c);
}

//Finds the first alphabetical character in a given string and returns the position of that character
unsigned int
findAlpha(string &l, unsigned int i)
{
    while(notalpha(l[i]))
        ++i;
    return i;
}

// findNameLen: returns the length of a name given the line and position of the beginning of a name
unsigned int
findNameLen(string &l, unsigned int i)
{
    unsigned int ret = 0;
    while(alpha(l[i])){
        ++ret;
        ++i;
    }
    return ret;
}


// storeNames: stores the names in a line into a vector
void
storeNames(string line, vector<string> &names)
{

    unsigned int i = 0, j = 0;
    while(i != line.size()){
        string name;
        // Find first alpha and store in i and length to copy for j
        i = findAlpha(line, i);
        j = findNameLen(line, i);

        // Create the substring and push back onto the vector
        name = line.substr(i, j);
        names.push_back(name);

        // 'i' must be moved from its position a length of j + 1 to be
        // the character after the end of the name in line
        i = i + j + 1;
    }
}


// alphabeticValue: finds the value of a name; note that all the names must be capitalized
// since the ASCII codes are used to determine the value.
long long
alphabeticValue(string &name)
{
    long long ret = 0;
    for(string::iterator it = name.begin(); it != name.end(); ++it){
        // 'A' is 65 in ASCII so you must subtract 64 to get its alpha value.
        ret += int(*it) - 64;
    }
    return ret;
}

// calculateValues: calculates the name scores and stores them into a vector of long longs
void
calculateValues(vector<string> names, vector<long long> &vals)
{
    for(unsigned i = 0; i != names.size(); ++i){
        long long alphaVal = alphabeticValue(names[i]);
        vals.push_back(alphaVal * (i + 1));
    }
}

int main()
{
    ifstream nameFile;
    nameFile.open("names.txt");
    string line;
    vector<string> nameList;

    while(getline(nameFile, line)){
        storeNames(line, nameList);
    }

    // Alphabetize list of names
    sort(nameList.begin(), nameList.end());

    vector<long long> nameValues;
    calculateValues(nameList, nameValues);

    //Add all the name scores
    cout << accumulate(nameValues.begin(), nameValues.end(), 0) << endl;

    return 0;
}
