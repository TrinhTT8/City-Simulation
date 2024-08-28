//This file will calculate the polution
#include "Pollution.h"

using namespace std;

//Polluion is 0 before the program initialize
//the pollution = population in each cell after the program run

    void incPoll(vector<vector<Cell>>& grid, vector<IndustrialRegion>& IndustrialRegions) {
        //iterate through the grid to find the first industrial cell with a population to be the sourc

        //Find the source of the pollution
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[0].size(); ++j) {
                grid[i][j].pollution = grid[i][j].population;
                //If population is larger than 2 in the Industrial region, then make that the source
                if (grid[i][j].population >= 2) {
                    int population = grid[i][j].population;
                    int pollution = grid[i][j].pollution;
                     
                    // Spread the pollution to the cells around it
                    for (int k = i - pollution; k <= i + pollution; ++k) {
                        for (int l = j - pollution; l <= j + pollution; ++l) {
                            if (k >= 0 && l >= 0 && k < grid.size() && l < grid[0].size()) {
                                if (grid[k][l].pollution == 0) {
                                    //Increase the pollution based on the population and the distance of the cell between the source point
                                    grid[k][l].pollution += population - abs(i - k) - abs(j - l);
                                }
                            }
                        }
                    }
                }
            }
        }
    }


    //Calculate the pollution of the user chosen region by looping through the grid
    int sumregionPoll(vector<vector<Cell>>& grid, int Lrow, int Rrow, int Lcol, int Rcol) {
        int sum = 0;
        for (int i=Lrow; i <= Rrow; ++i){
            for (int j=0; j < grid[i].size(); ++j) {
                    sum += grid[i][j].pollution;
                }
            }
        return sum;
    }  

    //Calculate the pollution of the entire region by looping through the grid
    int sumPoll(vector<vector<Cell>>& grid) {
        int sum = 0;        
        for (int i=0; i < grid.size(); ++i){
            for (int j=0; j < grid[i].size(); ++j){
                    sum += grid[i][j].pollution;    
            }
        }
        return sum;
    }


