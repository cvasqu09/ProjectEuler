#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <istream>
#include <algorithm>
#include <ctype.h>
#include <iterator>
#include <sstream>

using namespace std;

/* Problem 18: By starting at the top of a triangle and moving to adjacent
   numbers on the row below, find the maximum total */


//Returns if a given character is a digit
bool
boolDig(char& c)
{
    return isdigit(c);
}

//Returns if a given character is a space character
bool
boolSpace(char& c)
{
    return isspace(c);
}


void
split(string line, vector<vector<string> >& levels)
{
    string::iterator it = line.begin();
    string::iterator itend = line.begin();
    vector<string> lineValues;

    while(it != line.end()){
        string value;
        // Find the first space or the end of the line character.
        itend = find_if(it, line.end(), boolSpace);

        //Append to value up until itend
        for(string::iterator i = it; i != itend; ++i){
            value += *i;
        }

        //Push back the value onto lines
        lineValues.push_back(value);
        it = find_if(itend, line.end(), boolDig);
    }

    levels.push_back(lineValues);
}

/* Stores the levels of the triangle into a vector where each item in
   the vector is a vector of strings that represent each value of that
   given level */
void
storeLevels(ifstream& tree, vector<vector<string> >& lev)
{
    string line;
    while(getline(tree, line)){
        cout << line << endl;
        split(line, lev);
    }
}

//Converts a string to a long long
long long
convert2ll(string val)
{
    stringstream ss;
    long long ret;
    ss << val;
    ss >> ret;
    return ret;
}

/* Returns the element at a given key and level in our triangle
   if the element is larger than the key + 1 element */
long long
compare(vector<vector<string> > &levs, int level, int key)
{
    long long ret;
    if(levs[level][key] > levs[level][key + 1]){
        ret = convert2ll(levs[level][key]);
    } else {
        ret = convert2ll(levs[level][key+1]);
    }
    return ret;
}

long long
findLargestSum(vector<vector<string> > &levs, int lev, int &key)
{
    long long x = convert2ll(levs[lev][key]);
    long long y = convert2ll(levs[lev][key + 1]);
    // Look ahead to calculate sum;
    long long nextX = compare(levs, lev + 1, key);
    long long nextY = compare(levs, lev + 1, key + 1);
    if((x + nextX) > (y + nextY)){
        //Key correction
        if(nextX != convert2ll(levs[lev+1][key]))
            key += 1;
        return x + nextX;
    } else {
        //Key correction
        if(nextY == convert2ll(levs[lev + 1][key + 1])){
            //Right side is greater; need to increment regardless
            key += 1;
        } else {
            //Need to increment since traversing the right side twice
            key += 2;
        }
        return y + nextY;
    }
}

//Analyzes the tree and returns the largest sum by traversing adjacent elements in lower rows
long long
analyze(vector<vector<string> > &levs)
{
    //Ret is initially the first value in levs
    long long ret = convert2ll(levs[0][0]);
    int key = 0;
    /* Increment by 2 is to look ahead and traverse the path
       with the largest sum from the next two subsequent levels
       If you traverse greedily then there is possibility of traversing
       a path which will produce a smaller sum. */
    for(int i = 1; i != levs.size(); i += 2){
        ret += findLargestSum(levs, i, key);
    }
    return ret;
}


int main()
{
    ifstream treeFile;
    vector<vector<string> > levels;
    struct tnode *Tree = NULL;
    treeFile.open("tree.txt");
    storeLevels(treeFile, levels);

//    Print tree for testing
//    cout << "Printing tree: " << endl;
//    for(vector<vector<string> >::iterator it = levels.begin(); it != levels.end(); ++it){
//        for(vector<string>::iterator iter = (*it).begin(); iter != (*it).end(); ++iter){
//            cout << *iter << " ";
//        }
//        cout << endl;
//    }

//For problem 67 modify to optimize the process
    long long answer;
    answer = analyze(levels);
    cout << "Answer = " << answer << endl;

    treeFile.close();
    return 0;
}
