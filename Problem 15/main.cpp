#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

/* Problem 15:
    The program builds a grid to determine the number of lattice paths to the right and doubling
    that amount to get the lattice paths downwards.
    Ex. for 2x2 grid:

    column:   0   1
    row:
            ---------
        0   | 3 | 1 |   There are n + 1 rows in order to store the paths rightward. The value in each box
            ---------   indicates the number of lattice paths at the bottom right point in that box. Therefore
        1   | 2 | 1 |   the value at point 0,0 is all the lattice paths to the right and needs to be doubled
            ---------   to account for the paths down.
        2   | 1 | 0 |
            ---------

/* fillCol:
    Finds the bottommost and rightmost empty grid box and fills it in with
    the right value + the bottom. Note that the value at each box in the grid
    represents the number of lattice paths at the bottom right point of that
    box.
*/
void
fillCol(vector<vector<long long> > &grid)
{
    int i = 0;
    int j = 0;
    int filled = false;
    while(!filled){
        while(grid[i][j+1] == 0)
            ++j;
        while(grid[i+1][j] == 0)
            ++i;
        grid[i][j] = grid[i+1][j] + grid[i][j+1];
        if(i == 0)
            filled = true;
        else
            --i;
    }
}


/* buildGrid:
    Produces the grid with all the values filled in.
*/
void
buildGrid(vector<vector<long long> > &grid, int sz)
{
    int done = false;
    while(!done){
        fillCol(grid);
        if(grid[0][0] == 0)
            done = false;
        else
            done = true;
    }
    return;
}


long long
findPaths(vector<vector<long long> > &grid, int sz)
{
    buildGrid(grid, sz);
    // Must multiply by 2 in order to get other half of paths.
    return grid[0][0] * 2;
}


/* sizeGrid:
    Inserts sz+1 rows and sz columns. The extra row is used at the top of the grid to
    store the lattice paths to the right plus the lattice paths down. The last column
    and last row will contain
*/
void
sizeGrid(int sz, vector<vector<long long> > &grid)
{
    for(int i = 0; i < sz + 1; ++i){
        int j = 0;
        vector<long long> row;
        while(j < sz){
            if(j == sz - 1 || i == sz){
                if(j == sz - 1 && i == sz)
                {
                    row.push_back(0);
                    ++j;
                } else {
                    row.push_back(1);
                    ++j;
                }
            } else {
                row.push_back(0);
                ++j;
            }

        }
        grid.push_back(row);
    }
}


/* printGrid:
    Prints out the grid that is built. Note that if you start with the first element at position
    [0][0] will be half of the paths that exist. The other half will result in traveling down initially
*/
void
printGrid(vector<vector<long long> > &grid)
{
    for(vector<vector<long long> >::iterator it = grid.begin(); it != grid.end(); ++it){
        for(vector<long long>::iterator iter = (*it).begin(); iter != (*it).end(); ++iter){
            cout << *iter << "\t";
        }
        cout << endl;
    }
}

int main()
{
    int gridSize = 20;
    long long pcount = 0;
    vector<vector<long long> > grid;

    sizeGrid(gridSize, grid);
    pcount = findPaths(grid, gridSize);

//  Uncomment to see grid. Large values do not print nicely in command prompt.
//    printGrid(grid);

    cout << "Number of paths: " << pcount << endl;


    return 0;

}
