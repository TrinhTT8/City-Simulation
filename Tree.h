#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include "Cell.h"

using namespace std;

void assignTree(vector<vector<Cell>>& grid);
void changeTree(vector<vector<Cell>>& grid); 
int sumTree(vector<vector<Cell>>& grid);
int sumregionTree(vector<vector<Cell>>& grid, int Lrow, int Rrow, int Lcol, int Rcol);
int floodDamage(vector<vector<Cell>>& grid, char type);

#endif
