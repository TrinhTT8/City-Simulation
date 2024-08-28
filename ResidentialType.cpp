#include "ResidentialType.h"

using namespace std;

// called to assign and increment the number of houses and apartments
void housingType(vector<vector<Cell>>& grid, vector<ResidentialRegion>& ResidentialRegions) 
{
    // iterate through the grid searching for residential cells
    for (int i = 0; i < grid.size(); ++i) 
    {
        for (int j = 0; j < grid[i].size(); ++j) 
        {
            if (grid[i][j].zoneType == 'R') 
            {
                // if a residential cell has a population from 1 to 2 it will be considered an apartment
                if (grid[i][j].population > 0 && grid[i][j].population <= 1 && grid[i][j].apartments != 1) 
                {
                    grid[i][j].apartments += 1;
                }
                else if (grid[i][j].apartments == 1 && grid[i][j].population == 2)
                {
                    continue;
                }
                // if a residential cell has a population from 3 and above it will be considered a house
                else if (grid[i][j].population == 3 && grid[i][j].houses == 0) 
                {
                    grid[i][j].apartments -= 1;
                    grid[i][j].houses += 1;
                }
                else if (grid[i][j].population > 2 && grid[i][j].houses == 1)
                {
                    continue;
                }
            }
        }  
    }
}

// called to calculate the total number of houses on the grid
int sumHouses(vector<vector<Cell>>& grid) 
{
    int total = 0;
    for (int i=0; i < grid.size(); ++i)
    {
        for (int j=0; j < grid[i].size(); ++j)
        {
                total += grid[i][j].houses;    
        }
    }
    return total;
}

// called to calculate the total number of apartments on the grid
int sumApartments(vector<vector<Cell>>& grid) 
{
    int total = 0;
    for (int i=0; i < grid.size(); ++i) 
    {
        for (int j=0; j < grid[i].size(); ++j)
        {
                total += grid[i][j].apartments;    
        }
    }
    return total;

}

// called to calculate the total number of houses in the user specified region
int sumRegionHouses(vector<vector<Cell>>& grid, int Lrow, int Rrow, int Lcol, int Rcol) {
    int total = 0;
    for (int i=Lrow; i <= Rrow; ++i)
    {
        for (int j=0; j < grid[i].size(); ++j) 
        {
                total += grid[i][j].houses;
        }
    }
    return total;
}

// called to calculate the total number of apartments in the user specified region
int sumRegionApartments(vector<vector<Cell>>& grid, int Lrow, int Rrow, int Lcol, int Rcol) {
    int total = 0;
    for (int i=Lrow; i <= Rrow; ++i)
    {
        for (int j=0; j < grid[i].size(); ++j) 
        {
                total += grid[i][j].apartments;
        }
    }
    return total;

}

