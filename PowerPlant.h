#ifndef POWERPLANT_H
#define POWERPLANT_H

#include <vector>
#include <iostream>

#include "Industrial.h"
#include "Cell.h"
#include "Pollution.h"
using namespace std;

class PowerPlant {
    public:
        //constructor
        PowerPlant(char &zoneType, int &pollution);

        //sets a power plant to a Solar power plant
        void Solar(vector<vector<Cell>>& grid, int row, int col);
        //sets a power plant to a Wind power plant
        void Wind(vector<vector<Cell>>& grid, int row, int col);
        //sets a power plant to a Nuclear power plant
        void Nuclear(vector<vector<Cell>>& grid, int row, int col);
        //spreads pollution
        void pollPowerPlant(vector<vector<Cell>>& grid);

        char *zoneType;
        int *pollution;

};


#endif
