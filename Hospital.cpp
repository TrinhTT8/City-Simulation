#include "Hospital.h"
HospitalRegion::HospitalRegion(char &zoneType, int &population, int &pollution, int x, int y)
{
	this->type = zoneType;
	this->population = &population;
	this->pollution = &pollution;
	this->x = x;
	this->y = y;
	// this->population = population;
}
HospitalRegion::HospitalRegion(){
	
}

void HospitalRegion::simStep(vector<vector<Cell>> grid,vector<vector<Cell>> &temp){
	for(int i = 0; i<workers; i++){
		if(!SickWorkers.empty()){
			Cell firstCell = SickWorkers.front();
			temp[firstCell.x][firstCell.y].population++;
			SickWorkers.pop();
		}
		else{
			break;
		}
	}
	srand(time(nullptr));
	
	for(int i = 0; i<grid.size(); i++){
		for(int j = 0; j<grid[i].size(); j++){
			for(int q = 0; q<grid[i][j].population; q++){
				int sickChance = (grid[i][j].pollution*4);
				if(sickChance!=0){
					if(rand() % (100/sickChance) == 1){
						temp[i][j].population--;
						Cell sick = temp[i][j];
						SickWorkers.push(sick);
						
					}
				
				}
			}
		}
		
	}
	
}



