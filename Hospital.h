#ifndef HOSPITAL_H
#define HOSPITAL_H
#include <iostream>
#include <vector>
#include "Cell.h"
#include <queue>
#include <ctime>
#include <cmath>

using namespace std;


class HospitalRegion{
	public:
	char type = '0';
	int *population;
	int *pollution;
	int x;
	int y;
	int workers = 0;
	queue<Cell> SickWorkers;

	HospitalRegion(char &zoneType, int &population,int &pollution, int x, int y);
	HospitalRegion();
	void simStep(vector<vector<Cell>> grid,vector<vector<Cell>> &temp);
		
		
		
		
		
};

#endif