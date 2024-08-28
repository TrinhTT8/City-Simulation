#ifndef INDUSTRIAL_CPP
#define INDUSTRIAL_CPP
#include "Industrial.h"

bool IndustrialRegion::increasePop(vector<vector<Cell>> grid ,vector<vector<Cell>> &temp, int &availableWorkers)
{
	int xMax = x + 1;
	int xMin = x - 1;
	int yMax = y + 1;
	int yMin = y - 1;
	int cellsWith2 = 0;
	int myCell = 0;
	int cellsWith1 = 0;
	if (xMax > temp.size() - 1)
	{
		xMax = temp.size() - 1;
	}
	if (xMin < 0)
	{
		xMin = 0;
	}
	if (yMax > temp[0].size() - 1)
	{
		yMax = temp[0].size() - 1;
	}

	if (yMin < 0)
	{
		yMin = 0;
	}
	if (availableWorkers < 2)
	{
		
		return false;
	}
	switch (grid[x][y].population)
	{
	case 0:
		// bool
		for (int i = xMin; i < xMax + 1; i++)
		{

			for (int j = yMin; j < yMax + 1; j++)
			{

				if (i == x && j == y)
				{
					continue;
				}
				if (grid[i][j].zoneType == 'T' || grid[i][j].zoneType == '#')
				{
					
					temp[x][y].population += 1;
					workers += 2;
					return true;
					break;
				}
				else if (grid[i][j].population >= 1)
				{
					temp[x][y].population += 1;
					workers += 2;
					return true;
					break;
				}
			}
		}

		break;

	case 1:

		for (int i = xMin; i < xMax + 1; i++)
		{

			for (int j = yMin; j < yMax + 1; j++)
			{

				if (grid[i][j].population >= 1)
				{
					cellsWith1++;
				}
			}
		}
		if (cellsWith1 >= 2)
		{
			temp[x][y].population += 1;
			workers += 2;
			return true;
		}
		break;
	case 2:

		for (int i = xMin; i < xMax + 1; i++)
		{

			for (int j = yMin; j < yMax + 1; j++)
			{

				if (grid[i][j].population >= 2)
				{
					cellsWith2++;
				}
			}
		}
		if (cellsWith2 >= 4)
		{
			temp[x][y].population += 1;
			workers += 2;
			CleanUpCrew(temp[x][y], 10);
			return true;
		}
		break;
	/*default:

		for (int i = xMin; i < xMax + 1; i++)
		{

			for (int j = yMin; j < yMax + 1; j++)
			{

				if (grid[i][j].population >= 2)
				{
					myCell++;
				}
			}
		}
		if (myCell >= 4)
		{
			temp[x][y].population += 1;
			workers += 2;
			return true;
		}
		break;*/
	}
	return false;
}
IndustrialRegion::IndustrialRegion(char &zoneType, int &population, int &pollution, int x, int y)
{
	this->type = &zoneType;
	this->population = &population;
	this->pollution = &pollution;
	this->x = x;
	this->y = y;
	// this->population = population;
}
bool IndustrialRegion::simStep(vector<vector<Cell>> grid,vector<vector<Cell>> &temp , int &availableWorkers, int &goods){

	if(IndustrialRegion::increasePop(grid,temp,availableWorkers) == true){
		goods+=temp[x][y].population;
		return true;
	}
	else{
	goods+=temp[x][y].population;
	return false;
	}
}
#endif
