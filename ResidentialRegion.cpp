#include "ResidentialRegion.h"
using namespace std;

// Constructor for the ResidentialRegion object
ResidentialRegion::ResidentialRegion(char &zoneType, int &population, int &pollution, int i, int j)
{
    this->zoneType = &zoneType;
    this->population = &population;
	this->pollution = &pollution;
    this->i = i;
    this->j = j;
}

// Check if Cell is adjacent to a powerline 
bool ResidentialRegion::resAdjPower(vector<vector<Cell>> grid)
{
    //Checking boundaries of the grid
    int xMax = i + 1;
	int xMin = i - 1;
	int yMax = j + 1;
	int yMin = j - 1;
	if (xMax > grid.size() - 1)
	{
		xMax = grid.size() - 1;
	}
	if (xMin < 0)
	{
		xMin = 0;
	}
	if (yMax > grid[0].size() - 1)
	{
		yMax = grid[0].size() - 1;
	}

	if (yMin < 0)
	{
		yMin = 0;
	}
    if (grid[i][j].population == 0)
    {
        // looping through the adjacent Cells
        for (int x = xMin; x < xMax + 1; x++)
        {

            for (int y = yMin; y < yMax + 1; y++)
            {

                if (i == x && j == y)
                {
                    continue;
                }
                if (grid[x][y].zoneType == 'T' || grid[x][y].zoneType == '#')
                {
                    return true;
                }
            }
        }
    }
    return false;
}

// Check if Cell is adjacent to another Cell with population of at least 1
bool ResidentialRegion::resAdj0(vector<vector<Cell>> grid)
{
    //Checking boundaries of the grid
    int xMax = i + 1;
	int xMin = i - 1;
	int yMax = j + 1;
	int yMin = j - 1;
	if (xMax > grid.size() - 1)
	{
		xMax = grid.size() - 1;
	}
	if (xMin < 0)
	{
		xMin = 0;
	}
	if (yMax > grid[0].size() - 1)
	{
		yMax = grid[0].size() - 1;
	}

	if (yMin < 0)
	{
		yMin = 0;
	}
    if (grid[i][j].population == 0)
    {
        // looping through the adjacent Cells
        for (int x = xMin; x < xMax + 1; x++)
        {

            for (int y = yMin; y < yMax + 1; y++)
            {

                if (i == x && j == y)
                {
                    continue;
                }
                if (grid[x][y].population >= 1)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

// Check if Cell is adjacent to at least 2 other Cells with population of at least 1
bool ResidentialRegion::resAdj1(vector<vector<Cell>> grid)
{
    // number of Cells with population of at least 1
    int found = 0;

    // checking boundaries
    int xMax = i + 1;
	int xMin = i - 1;
	int yMax = j + 1;
	int yMin = j - 1;
	if (xMax > grid.size() - 1)
	{
		xMax = grid.size() - 1;
	}
	if (xMin < 0)
	{
		xMin = 0;
	}
	if (yMax > grid[0].size() - 1)
	{
		yMax = grid[0].size() - 1;
	}

	if (yMin < 0)
	{
		yMin = 0;
	}
    if (grid[i][j].population == 1)
    {
        // looping through the adjacent Cells
        for (int x = xMin; x < xMax + 1; x++)
        {

            for (int y = yMin; y < yMax + 1; y++)
            {

                if (i == x && j == y)
                {
                    continue;
                }
                if (grid[x][y].population >= 1)
                {
                    found++;
                }
            }
        }
    }
    if (found >= 2)
    {
        return true;
    }
    return false;
}

// Check if Cell is adjacent to at least 4 other Cells with population of at least 2
bool ResidentialRegion::resAdj2(vector<vector<Cell>> grid)
{
    // number of Cells with population of at least 2
    int found = 0;

    // checking boundaries
    int xMax = i + 1;
	int xMin = i - 1;
	int yMax = j + 1;
	int yMin = j - 1;
	if (xMax > grid.size() - 1)
	{
		xMax = grid.size() - 1;
	}
	if (xMin < 0)
	{
		xMin = 0;
	}
	if (yMax > grid[0].size() - 1)
	{
		yMax = grid[0].size() - 1;
	}

	if (yMin < 0)
	{
		yMin = 0;
	}
    if (grid[i][j].population == 2)
    {
        // looping through the adjacent Cells
        for (int x = xMin; x < xMax + 1; x++)
        {

            for (int y = yMin; y < yMax + 1; y++)
            {

                if (i == x && j == y)
                {
                    continue;
                }
                if (grid[x][y].population >= 2)
                {
                    found++;
                }
            }
        }
    }
    if (found >= 4)
    {
        return true;
    }
    return false;
}

// Check if Cell is adjacent to at least 6 other Cells with population of at least 3
bool ResidentialRegion::resAdj3(vector<vector<Cell>> grid)
{
    // number of Cells with population of at least 6
    int found = 0;

    //checking boundaries
    int xMax = i + 1;
	int xMin = i - 1;
	int yMax = j + 1;
	int yMin = j - 1;
	if (xMax > grid.size() - 1)
	{
		xMax = grid.size() - 1;
	}
	if (xMin < 0)
	{
		xMin = 0;
	}
	if (yMax > grid[0].size() - 1)
	{
		yMax = grid[0].size() - 1;
	}

	if (yMin < 0)
	{
		yMin = 0;
	}
    if (grid[i][j].population == 3)
    {
        // looping through the adjacent Cells
        for (int x = xMin; x < xMax + 1; x++)
        {

            for (int y = yMin; y < yMax + 1; y++)
            {

                if (i == x && j == y)
                {
                    continue;
                }
                if (grid[x][y].population >= 3)
                {
                    found++;
                }
            }
        }
    }
    if (found >= 6)
    {
        return true;
    }
    return false;
}

// Check if Cell is adjacent to at least 8 other Cells with population of at least 4
bool ResidentialRegion::resAdj4(vector<vector<Cell>> grid)
{
    // number of Cells with population of at least 4
    int found = 0;

    // checking boundaries
    int xMax = i + 1;
	int xMin = i - 1;
	int yMax = j + 1;
	int yMin = j - 1;
	if (xMax > grid.size() - 1)
	{
		xMax = grid.size() - 1;
	}
	if (xMin < 0)
	{
		xMin = 0;
	}
	if (yMax > grid[0].size() - 1)
	{
		yMax = grid[0].size() - 1;
	}

	if (yMin < 0)
	{
		yMin = 0;
	}
    if (grid[i][j].population == 4)
    {
        // looping through the adjacent Cells
        for (int x = xMin; x < xMax + 1; x++)
        {

            for (int y = yMin; y < yMax + 1; y++)
            {

                if (i == x && j == y)
                {
                    continue;
                }
                if (grid[x][y].population >= 4)
                {
                    found++;
                }
            }
        }
    }
    if (found >= 8)
    {
        return true;
    }
    return false;
}

// Simulates growth of the Residential region
void ResidentialRegion::simulateRes(vector<vector<Cell>> grid, vector<vector<Cell>> &temp)
{
    //checking if any of the adjacency conditions for the population to grow are satisfied
    if (resAdjPower(grid) || resAdj0(grid) || resAdj1(grid) || resAdj2(grid) || resAdj3(grid) || resAdj4(grid))
    {
        temp[i][j].population++; // outputted next time step
        CleanUpCrew(temp[i][j], 3);
    }
}

// Expand the residential region as necessary
void ResidentialRegion::newRes(vector<vector<Cell>> grid, vector<vector<Cell>> &temp)
{
    // check if cell has a population of 4
    if (resAdj4(grid)) 
    {
        // expand to adjacent cell if available
        if (grid[i + 1][j].zoneType = ' ') 
        {
            grid[i + 1][j].zoneType = 'R';
        } 
        else if (grid[i - 1][j].zoneType = ' ')
        {
            grid[i - 1][j].zoneType = 'R';
        }
        else if (grid[i][j + 1].zoneType = ' ')
        {
            grid[i][j + 1].zoneType = 'R';
        }
        else if (grid[i][j - 1].zoneType = ' ')
        {
            grid[i][j - 1].zoneType = 'R';
        }
        else if (grid[i + 1][j + 1].zoneType = ' ')
        {
            grid[i + 1][j + 1].zoneType = 'R';
        }
        else if (grid[i + 1][j - 1].zoneType = ' ')
        {
            grid[i + 1][j - 1].zoneType = 'R';
        }
        else if (grid[i - 1][j + 1].zoneType = ' ')
        {
            grid[i - 1][j + 1].zoneType = 'R';
        }
        else if (grid[i - 1][j - 1].zoneType = ' ')
        {
            grid[i - 1][j - 1].zoneType = 'R';
        }
    }
}
