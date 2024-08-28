#ifndef POLLUTION_H
#define POLLUTION_H

#include <vector>
#include <iostream>

#include "Industrial.h"
#include "Cell.h"

void incPoll(vector<vector<Cell>>& grid, vector<IndustrialRegion>& IndustrialRegions);
int sumPoll(vector<vector<Cell>>& grid);
int sumregionPoll(vector<vector<Cell>>& grid, int Lrow, int Lcol, int Rrow, int Rcol);


#endif

