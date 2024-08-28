#include "EducationInstitute.h"
#include <cstdlib>  
#include <ctime>    
#include <algorithm> 

EducationRegion::EducationRegion(char &zoneType, int &population, int &pollution, int x, int y)
{
    this->type = zoneType;
    this->population = &population;
    this->pollution = &pollution;
    this->x = x;
    this->y = y;
}

EducationRegion::EducationRegion()
{
}

void EducationRegion::simStep(std::vector<std::vector<Cell>> grid, std::vector<std::vector<Cell>> &temp)
{
    int count = 0;
    for (auto &student : EnrolledStudents)
    {
        if (count >= workers)
            break;                 
        Cell newStudent = student; 
        temp[newStudent.x][newStudent.y].population++;
        count++;
    }
  
    while (count-- > 0 && !EnrolledStudents.empty())
    {
        EnrolledStudents.pop_front(); 
    }
    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            for (int q = 0; q < grid[i][j].population; q++)
            {
                int performanceFactor = std::max(1, 100 - (grid[i][j].pollution * 5));
                if (rand() % 100 > performanceFactor)
                {
                    temp[i][j].population--;
                    Cell dropout = temp[i][j];
                    DroppedOutStudents.push_back(dropout); 
                }
                else
                {
                    int extraCurricularBoost = (rand() % 10 < 3) ? 1 : 0;
                    if (extraCurricularBoost)
                    {
                        temp[i][j].population++;
                    }
                }
            }
        }
    }
}
