#ifndef RESIDENTIALREGIONH
#define RESIDENTIALREGIONH

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include "Cell.h"
#include "Cleanup.h"
using namespace std;

class ResidentialRegion
{
public:
    ResidentialRegion(char &zoneType, int &population,int &pollution, int x, int y);

    bool resAdjPower(vector<vector<Cell>> grid);
    bool resAdj0(vector<vector<Cell>> grid);
    bool resAdj1(vector<vector<Cell>> grid);
    bool resAdj2(vector<vector<Cell>> grid);
    bool resAdj3(vector<vector<Cell>> grid);
    bool resAdj4(vector<vector<Cell>> grid);
    void simulateRes(vector<vector<Cell>> grid, vector<vector<Cell>> &temp);
    void newRes(vector<vector<Cell>> grid, vector<vector<Cell>> &temp);

    char *zoneType;
    int *population;
	int *pollution;
    int i;
    int j;
};

#endif
