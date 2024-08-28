#ifndef EDUCATIONINSTITUTE_H
#define EDUCATIONINSTITUTE_H
#include <iostream>
#include <vector>
#include <deque>
#include "Cell.h"
#include <cstdlib>  
#include <ctime>    
#include <algorithm>
class EducationRegion {
public:
    char type;
    int* population;
    int* pollution;
    int x;
    int y;

    std::deque<Cell> EnrolledStudents;
    std::deque<Cell> DroppedOutStudents;
    int workers;

    EducationRegion(char &zoneType, int &population, int &pollution, int x, int y);
    EducationRegion();

    void simStep(std::vector<std::vector<Cell>> grid, std::vector<std::vector<Cell>> &temp);
};

#endif // EDUCATIONINSTITUTE_H
