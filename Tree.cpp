#include "Tree.h"

//Assign a certain tree population 
void assignTree(vector<vector<Cell>>& grid){
    int tree = 2;
    for (int i = 0; i < grid.size(); ++i){
        for (int j=0; j < grid[i].size(); ++j) {
            if (grid[i][j].zoneType != '-' && grid[i][j].zoneType != 'T' && grid[i][j].zoneType != 'P' && grid[i][j].zoneType != '#') {
                grid[i][j].tree = tree;
            }
            else {
                grid[i][j].tree = 0;
            }
        }
    }
}

void changeTree(vector<vector<Cell>>& grid){
    for (int i = 0; i < grid.size(); ++i){
        for (int j=0; j < grid[i].size(); ++j) {
            //Case 1: If the cell has pollution , the number of trees decrease based on the pollution population
            if (grid[i][j].pollution > 0 && grid[i][j].tree > grid[i][j].pollution) {
                grid[i][j].tree = grid[i][j].tree - grid[i][j].pollution; 
            }
            else if (grid[i][j].tree < grid[i][j].pollution) {
                grid[i][j].tree = 0;
            }
            //Case 2: If the cell only has population, for every 2 population, a tree will be decrease
            if(grid[i][j].population > 0 && grid[i][j].pollution == 0 && grid[i][j].tree > 0) {
                int rate = floor(grid[i][j].population/2);
                grid[i][j].tree = grid[i][j].tree - (rate*1);
            }          
        }
    }
}

int sumTree(vector<vector<Cell>>& grid) {
    int sum = 0;        
    for (int i=0; i < grid.size(); ++i){
        for (int j=0; j < grid[i].size(); ++j){
                sum += grid[i][j].tree;    
        }
    }
    sum = sum * 10;
    return sum;
}

//Calculate the number of trees from the user chosen region by looping through the grid
int sumregionTree(vector<vector<Cell>>& grid, int Lrow, int Rrow, int Lcol, int Rcol) {
    int sum = 0;
    for (int i=Lrow; i <= Rrow; ++i){
        for (int j=0; j < grid[i].size(); ++j) {
                sum += grid[i][j].tree;
            }
        }
    sum = sum * 10;
    return sum;
}

//This function decreases the number of trees based on the type of flood
int floodDamage(vector<vector<Cell>>& grid, char type) {
    int sum = sumTree(grid);
    //If it is a small flood then the tree population will decrease between 1-5 trees.    
    if (type == 'E') {
        int deadtree = (rand()%5)+1;
        sum -= deadtree;
        cout << "Dead trees: " << deadtree << endl;
    }
    //If it is a medium flood then the tree population will decrease between 10-20 trees.
    if (type == 'M') {
        int deadtree = (rand()%20)+10;
        sum -= deadtree;
        cout << "Dead trees: " << deadtree << endl;
    }
    //If it is a hard flood then the tree population will decrease between 50-100 trees.
    else if (type == 'H') {
        int deadtree = (rand()%100)+50;
        sum -= deadtree;
        cout << "Dead trees: " << deadtree << endl;    }
    return sum;
}
