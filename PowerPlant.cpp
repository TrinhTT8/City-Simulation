#include "PowerPlant.h"

using namespace std;

PowerPlant::PowerPlant(char &zoneType, int &pollution) {
    this->zoneType = &zoneType;
    this->pollution = &pollution;
}

//this will be implemented in main and the char type will be changed
//if ((row + col)%3) == 0 (solar)
//if ((row + col)%3) == 1 (wind)
//if ((row + col)%3) == 2 (nuclear)

//to set pollution:
//define the amount of pollution for a Solar Power Plant
void PowerPlant::Solar(vector<vector<Cell>>& grid, int row, int col) {
    grid[row][col].zoneType = 'S';
    grid[row][col].pollution = 2;
}

//define the amount of pollution for a Wind Power Plant
void PowerPlant::Wind(vector<vector<Cell>>& grid, int row, int col) {
    grid[row][col].zoneType = 'W';
    grid[row][col].pollution = 2;
}

//define the amount of pollution for a Nuclear Power Plant
void PowerPlant::Nuclear(vector<vector<Cell>>& grid, int row, int col) {
    grid[row][col].zoneType = 'N';
    grid[row][col].pollution = 6;
}

//increases pollution
void PowerPlant::pollPowerPlant(vector<vector<Cell>>& grid) {
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size(); ++j) {
            grid[i][j].pollution = grid[i][j].population;
            //checks if a cell is a Power Plant
            if (grid[i][j].zoneType == 'S' || grid[i][j].zoneType == 'N' || grid[i][j].zoneType == 'W') { 
                // Spread the pollution to the cells around it
                for (int k = i - grid[i][j].pollution; k <= i + grid[i][j].pollution; ++k) {
                    for (int l = j - grid[i][j].pollution; l <= j + grid[i][j].pollution; ++l) {
                        if (k >= 0 && l >= 0 && k < grid.size() && l < grid[i].size()) {
                            if (grid[k][l].pollution == 0) {
                                grid[k][l].pollution += (grid[i][j].population - abs(i - k) - abs(j - l));
                            }
                        }    
                    }
                }
            }
        }
    }

}

//to simulate the spread of pollution, incPoll in Pollution.cpp will be used
