#ifndef INDUSTRIAL_H
#define INDUSTRIAL_H
#include <iostream>
#include <vector>
#include "Cell.h"
#include "Cleanup.h"

using namespace std;

class IndustrialRegion
{
	public:
	char *type;
	int *population;
	int *pollution;
	int x;
	int y;
	int workers = 0;

	IndustrialRegion(char &zoneType, int &population,int &pollution, int x, int y);

	bool increasePop(vector<vector<Cell>> grid,vector<vector<Cell>> &temp, int &availableWorkers);
	
	bool simStep(vector<vector<Cell>> grid,vector<vector<Cell>> &temp, int &availableWorkers, int &goods);
};
#endif
