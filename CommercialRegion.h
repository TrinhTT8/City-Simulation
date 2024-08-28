#ifndef COMMERCIALREGION_H
#define COMMERCIALREGION_H

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include "Cell.h"
#include "Cleanup.h"

using namespace std;
class CommercialRegion
{
public:
    CommercialRegion(char &zoneType, int &population,int &pollution, int i, int j);
    int isAdjacentPower(vector<vector<Cell>> grid);
    int isAdjacentCell(vector<vector<Cell>> grid);
    bool simulateStep(vector<vector<Cell>> grid, vector<vector<Cell>> &temp, int &availableWorkers, int &goods);

    char *zoneType;
    int *population;
	int *pollution;
    int i;
    int j;
    int workers = 0;
    int goods = 0;
};

#endif
