#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <numeric>
#include <algorithm>

//Problem 11: In a given 20x20 grid find the greatest product of four adjacent numbers
//in the same direction.

using namespace std;

long multiply(long x, long y)
{
    return x * y;
}

//Calculate Right Diagonals
void calculateRDs(vector<vector<int> >& grid, vector<long>& store)
{
    for(vector<vector<int> >::iterator it = grid.begin(); it != grid.end() - 4; ++it){
		//For every row that can create a full four number diagonal
        for(int i = 0; i <= 15; ++i){
			//Add first element to total
            long total = (*it)[i];
			//Add up the next 3 right diagonal numbers
            for(int j = 1; j <= 3; ++j){
                total = total * (*(it + j))[j];
            }
            store.push_back(total);
        }
    }
}

//Calculate left diagonals
void calculateLDs(vector<vector<int> >&grid, vector<long>& store)
{
    for(vector<vector<int> >::iterator it = grid.begin(); it != grid.end() - 4; ++it){
        //Starting with the third row
        for(int i = 3; i < 20; ++i){
            //Start with the first element
            long total = (*it)[i];
            //Multiply diagonally to the right and up 3 times
            for(int j = 1; j <= 3; ++j){
                total = total * (*(it + j))[i - j];
            }
        //Add to total to vector
        store.push_back(total);
        }
    }
}

//Calculate 4 products along horizontal
void calculateHrztals(vector<vector<int> >& grid, vector<long>& store)
{
    //For every row
    for(vector<vector<int> >::iterator it = grid.begin(); it != grid.end(); ++it){
        long product = 1;
        //Calculate the product of the 4 horizontal numbers
        for(vector<int>::iterator iter = (*it).begin(); iter != (*it).end() - 4; ++iter){
             product = accumulate(iter, iter + 4, product, multiply);
        }
        //Store the products
        store.push_back(product);
    }
}

//Calculate vertical products
void calculateVrticals(vector<vector<int> >& grid, vector<long>& store)
{
    //For every row that can produce 4 numbers in a column
    for(vector<vector<int> >::iterator it = grid.begin(); it != grid.end() - 4; ++it){
        //For every element in the row
        for(int i = 0; i != 20; ++i){
            //Start with the element the iterator is pointing at
            long product = (*it)[i];
            //Calculate the product of multiplying the 3 elements below it
            for(int j = 1; j <= 3; ++j){
                product = product * (*(it+j))[i];
            }
            //Store the product
            store.push_back(product);
        }
    }
}

int main()
{
    ifstream grid;
    grid.open("grid.txt");

    vector<vector<int> > gridNumbers;

    string line;

    // Import grid
    while(getline(grid, line)){
        istringstream iss(line);
        int num;
        vector<int> vecNum;

        while(iss >> num){
            vecNum.push_back(num);
        }
        gridNumbers.push_back(vecNum);
    }

    // Calculate all possible products
    vector<long> Products;

    calculateRDs(gridNumbers, Products);
    calculateLDs(gridNumbers, Products);
    calculateHrztals(gridNumbers, Products);
    calculateVrticals(gridNumbers, Products);

    long largest = 0;
    //Look for largest element in vector of products.
    for(vector<long>::iterator it = Products.begin(); it != Products.end(); ++it){
        if(*it > largest){
            largest = *it;
        }
    }

    cout << "The largest product is: " << largest;

    grid.close();

    return 0;
}
