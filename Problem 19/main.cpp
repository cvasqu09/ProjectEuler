#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#define STARTYEAR 1900
#define STARTDAY "Mon"

/* Problem 19: Program calculates the given number of Sundays that fell on the first
   of the month from the beginning of the year to the end of it after 1900 for a
   given range. Note that if a range is given before 1900 it will be defaulted
   to the beginning of the year 1900. */

using namespace std;

//Mapping of the months to the number of days in each
map<int, int> months =
{
    {1, 31}, {2, 28}, {3, 31}, {4, 30},
    {5, 31}, {6, 30}, {7, 31}, {8, 31},
    {9, 30}, {10, 31}, {11, 30}, {12, 31}
};

//Vector of strings that contains abbreviations for each day
vector<string> days =
{
    "Mon", "Tues", "Wed", "Thurs", "Fri", "Sat", "Sun"
};

/* Corrects the day given a string that represents a day in the week
   and an integer of how many days to advance forward. */
string
correctTheDay(string start, int mod)
{
    //Find 'start' day in our vector of day names
    vector<string>::iterator retIt = find(days.begin(), days.end(), start);
    int cnt = 0;
    //Advance until we reach mod days of incrementing
    while(cnt != mod){
        advance(retIt, 1);
        if(retIt == days.end())
           retIt = days.begin();
        ++cnt;
    }
    //Return the string of the correct day
    return *retIt;
}

/* Modulate day: modulates the day given the year and
   returns the resulting day. */
string
modulateDay(string start, int year)
{
    if(year % 4 == 0){          //Leap year
        int moveDay = 366 % 7;
        return correctTheDay(start, moveDay); //Correct the day
    } else {
        int moveDay = 365 % 7;
        return correctTheDay(start, moveDay);  //Correct the day
    }
}

/* Returns the string representation of the day that a given year over
   1900 starts with. */
string
calculateDay(int year)
{
    if(year <= STARTYEAR){
        return STARTDAY;
    } else {
        string ret = STARTDAY;
        int currentYear = STARTYEAR;
        while(currentYear != year){
            ret = modulateDay(ret, currentYear);
            ++currentYear;
        }
        return ret;
    }
}


string
modulateMonth(string day, int daysInMonth, int year)
{
    // Special case for February during leap year
    if(daysInMonth == 28 && year % 4 == 0)
        return correctTheDay(day, 29 % 7);
    else
        return correctTheDay(day, daysInMonth);
}

/* Returns the number of Sundays from the beginning of the year to the end
   of the second parameter year, 'yearEnd' */
int
countSundays(int yearBegin, int yearEnd)
{
    int sun = 0;
    //As given by the problem
    string currentDay = "Mon";
    //The day must be changed for the given year if necessary.
    currentDay = calculateDay(yearBegin);

    //For every year
    for(int i = yearBegin; i <= yearEnd; ++i){
        //for every month
        for(int mon = 1; mon <= 12; ++mon){
            //Modulate what the current day will be after the end of that month
            currentDay = modulateMonth(currentDay, months[mon], i);
            //If the following month begins on a Sunday.
            if(currentDay == "Sun")
                ++sun;
        }
    }

    return sun;
}

int main()
{
    int numSundays =  0;
    numSundays = countSundays(1901, 2000);
    cout << "Number of Sundays on the first: " << numSundays << endl;
}
