#include "CommercialRegion.h"
using namespace std;
CommercialRegion::CommercialRegion(char &zoneType, int &population, int &pollution, int i, int j)
{
    this->zoneType = &zoneType;
    this->population = &population;
    this->i = i;
    this->j = j;
	this->pollution = &pollution;
    this->workers = workers;
    this->goods = goods;
}
// function checks if it is adjacent to a powerline and returns number of powerlines it is adjacent to
int CommercialRegion::isAdjacentPower(vector<vector<Cell>> grid)
{
    int xMax = i + 1;
    int xMin = i - 1;
    int yMax = j + 1;
    int yMin = j - 1;
    int adjToPowerline = 0;
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
    for (int x = xMin; x < xMax + 1; x++)
    {
        for (int y = yMin; y < yMax + 1; y++)
        {
            if (grid[x][y].zoneType == 'T' || grid[x][y].zoneType == '#' && workers >= 1 && goods >= 1)
            {
                if (grid[x][y].population == 0)
                {
                    adjToPowerline++;
                }
            }
        }
    }
    return adjToPowerline;
}
// function checks if it is adjacent to a cell with a populations of 1 or greater and returns the number of cells adjacent to
int CommercialRegion::isAdjacentCell(vector<vector<Cell>> grid)
{
    int xMax = i + 1;
    int xMin = i - 1;
    int yMax = j + 1;
    int yMin = j - 1;
    int adjToCell = 0;
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
    for (int x = xMin; x < xMax + 1; x++)
    {
        for (int y = yMin; y < yMax + 1; y++)
        {
            if (grid[x][y].population == 0)
            {
                adjToCell++;
            }
        }
    }
    return adjToCell;
}
// function steps through the region rules and updates the population based on them
bool CommercialRegion::simulateStep(vector<vector<Cell>> grid, vector<vector<Cell>> &temp, int &availableWorkers, int &goods)
{
    isAdjacentCell(grid);
	
    isAdjacentPower(grid);
    if (grid[i][j].population == 0 && isAdjacentPower(grid) > 0 && availableWorkers >= 1 && goods >= 1)
    {
        temp[i][j].population++;
		this->goods++;
		goods--;
        CleanUpCrew(temp[i][j], 5);
		return true;
    }
    if (grid[i][j].population == 0 && isAdjacentCell(grid) >= 1 && availableWorkers >= 1 && goods >= 1)
    {
        temp[i][j].population++;
		this->goods++;
		goods--;
        CleanUpCrew(temp[i][j], 5);
		return true;
    }
    if (grid[i][j].population == 1 && isAdjacentCell(grid) >= 2 && availableWorkers >= 1 && goods >= 1)
    {
        temp[i][j].population++;
		this->goods++;
		goods--;
        CleanUpCrew(temp[i][j], 5);
		return true;
    }
	else{
		return false;
	}
}
