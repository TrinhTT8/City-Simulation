#include "Flood.h"

bool flood(vector<vector<Cell>>& grid) {
    bool survive = false;
    
    //On a scale of 1 through 10, how strong the flood wil be with 1 being the weakest and 10 will be the strongest
    char type; 
    int chance = (rand() % 3) + 1;         //Randomly assign a number from1 to 10
    if (chance == 1) {
        type = 'E';          //Flood will be an "easy" flood  if the chance is between 1 and 3
        cout << "~~~~ A small flood incoming ~~~~\n";
    }
    else if (chance == 2) {
        type = 'M';          //Flood will be a "medium" flood  if the chance is between 1 and 3
        cout << "~~~~ A medium flood incoming ~~~~\n";
    }
    else {
        type = 'H';          //Flood will be a "hard" flood  if the chance is between 1 and 3
        cout << "~~~~ A BIG flood incoming ~~~~\n";
    }

    int sum = sumTree(grid);

    switch (type) {
        case 'E':
        if (sum >= 300) {
            survive = true;
        }
        break;

        case 'M':
        if (sum >= 600) {
            survive = true;
        }
        break;

        case 'H':
        if (sum >= 1000) {
            survive = true;
        }
        break;
    }

    sum = floodDamage(grid, type);
    cout << "Total trees left: " << sum << endl;

    return survive;
}

//100 trees will make up of one forest


//An easy flood will only require the city to have at least 300 trees (made up to around 2 forests)

//A medium flood will require the city to have at least 600 trees (with some damage to the tree population)

//A hard flood will require the city to have at least 1000 trees (with some damage to the tree population)

