
#include "Cleanup.h"
#include <iostream>
#include <ctime>
#include "Cell.h"


using namespace std;





//Called whenever population increases
//different regions have different chances in increasing pollution cleanup
//chances: industrial < commercial < residential
void CleanUpCrew (Cell &cell, int chance) {
    //the lower the variable chance, the greater the chance
    //ex. chance = 3, 1/3 chance
    //random number generator
    int randNum = (rand()%chance);

    //test output
    //cout<<"generator num: "<<randNum<<endl;

    //if 3 is generated, increase numCleanup in cell
    //3 is an arbitrary number, just making a 1/5 chance
    if (randNum == 1) {
        cell.numCleanup += 1;
    }
}



//Increase Trees
    //increase trees in cell/adjacent cells