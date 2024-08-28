#ifndef RESIDENTIALTYPE_H
#define RESIDENTIALTYPE_H

#include <iostream>
#include <vector>
#include "ResidentialRegion.h"
#include "Cell.h"
using namespace std;

void housingType(vector<vector<Cell>>& grid, vector<ResidentialRegion>& ResidentialRegions);
int sumHouses(vector<vector<Cell>>& grid);
int sumApartments(vector<vector<Cell>>& grid);
int sumRegionHouses(vector<vector<Cell>>& grid, int Lrow, int Rrow, int Lcol, int Rcol);
int sumRegionApartments(vector<vector<Cell>>& grid, int Lrow, int Rrow, int Lcol, int Rcol);

#endif
