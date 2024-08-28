#ifndef CELL_H
#define CELL_H
class Cell
{
public:
    char zoneType;
    int population;
    int pollution;
    int numCleanup;
    int tree;
    int houses;
    int apartments;
	int x;
	int y;

    // Initalize the cell objects with default value (default constructor)
    Cell() : population(0), zoneType('-'), pollution(0), numCleanup(0), houses(0), apartments(0), x(0), y(0) {}
};
#endif
