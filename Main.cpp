#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include "Pollution.h"
#include "Doomsday.h"
#include "CommercialRegion.h"
#include "Industrial.h"
#include "ResidentialRegion.h"
#include "Tree.h"
#include "ResidentialType.h"
#include "PowerPlant.h"
#include "Hospital.h"
#include "Flood.h"
#include "EducationInstitute.h"

using namespace std;

// Cell class {attributes: zone type, population, pollution level}

// 2D vector to represent city grid
using Grid = vector<vector<Cell>>;

// Config class to hold configuration data
class Config
{
public:
    string regionLayoutFile;
    int maxTimeSteps;
    int refreshRate;
    int workers;
    int goods;
    Config() : maxTimeSteps(0), refreshRate(0) {}
};

// Read-in the config file
Config readConfigFile(string &configFilename)
{
    Config config;

    ifstream configFile(configFilename);
    if (!configFile.is_open())
    {
        cout << "Unable to open configuration file : " << configFilename << endl;
        return config;
    }

    string line;
    while (getline(configFile, line))
    {
        istringstream iss(line);
        string key, value;

        // Read the each line until encounters ":", and store everything before ":" in the key variable
        if (getline(iss, key, ':') && getline(iss, value))
        {
            if (key == "Region Layout")
            {
                config.regionLayoutFile = value;
            }
            else if (key == "Time Limit")
            {
                config.maxTimeSteps = stoi(value);
            }
            else if (key == "Refresh Rate")
            {
                config.refreshRate = stoi(value);
            }
        }
    }

    configFile.close();
    return config;
}

void initializeCityGrid(string &regionLayoutFile, Grid &grid, vector<ResidentialRegion> &ResidentialRegions, vector<CommercialRegion> &CommercialRegions, vector<IndustrialRegion> &IndustrialRegions, HospitalRegion Hospital, vector<EducationRegion> &EducationRegions)
{

    ifstream csvFile(regionLayoutFile);

    if (!csvFile.is_open())
    {
        cout << "Unable to open region file: " << regionLayoutFile << endl;
        return;
    }

    string line;
    while (getline(csvFile, line))
    {
        istringstream lineStream(line);
        string myCell;
        vector<Cell> row;

        while (getline(lineStream, myCell, ','))
        {
            Cell cell;
            cell.zoneType = char(myCell[0]);
            row.push_back(cell);
        }
        grid.push_back(row);
    }

    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {

            switch (grid[i][j].zoneType)
            {
            case 'I':
                grid[i][j].pollution = 0;
                grid[i][j].population = 0;
                IndustrialRegions.push_back(IndustrialRegion(grid[i][j].zoneType, grid[i][j].population, grid[i][j].pollution, i, j));
                // int mytemp1 = IndustrialRegions.size()-1;

                break;
            case 'C':
                grid[i][j].pollution = 0;
                grid[i][j].population = 0;
                CommercialRegions.push_back(CommercialRegion(grid[i][j].zoneType, grid[i][j].population, grid[i][j].pollution, i, j));
                break;
            case 'R':
                grid[i][j].pollution = 0;
                grid[i][j].population = 0;
                ResidentialRegions.push_back(ResidentialRegion(grid[i][j].zoneType, grid[i][j].population, grid[i][j].pollution, i, j));
                break;
            case '-':
                grid[i][j].pollution = 0;
                break;
            case 'T':
                grid[i][j].pollution = 0;
                break;
            case 'P':
                grid[i][j].pollution = 0;
                break;
            case '#':
                grid[i][j].pollution = 0;
                break;
            case ' ':
            {
                grid[i][j].pollution = 0;
                grid[i][j].population = 0;

                bool foundEducation = false; // Initialize inside a new scope block
                for (const auto &region : EducationRegions)
                {
                    if (region.type == 'E')
                    {
                        foundEducation = true;
                        break;
                    }
                }

                if (!foundEducation)
                {
                    // If no education region exists, set this zone as an education region
                    grid[i][j].zoneType = 'E';
                    EducationRegions.push_back(EducationRegion(grid[i][j].zoneType, grid[i][j].population, grid[i][j].pollution, i, j));
                }
                else
                {
                    // If at least one education region exists, set this zone as a hospital
                    grid[i][j].zoneType = 'H';
                    Hospital.type = 'H';
                    Hospital.x = i;
                    Hospital.y = j;
                }
                break;
            }
            default:
                cout << "Invalid Read-in Type" << endl;
                cout << "In initializeCityGrid" << endl;
                exit(0);


            }
        }
    }

    csvFile.close();
}

// sets power plant type
void setPowerPlantType(Grid &grid)
{
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            if (grid[i][j].zoneType == 'P')
            {
                // current PowerPlant object
                PowerPlant curr(grid[i][j].zoneType, grid[i][j].pollution);
                // solar power plant
                if ((i + j) % 3 == 0)
                {
                    curr.Solar(grid, i, j);
                }
                // wind power plant
                else if ((i + j) % 3 == 1)
                {
                    curr.Wind(grid, i, j);
                }
                // nuclear power plant
                else
                {
                    curr.Nuclear(grid, i, j);
                }
            }
        }
    }
}

// rough draft of hierarchy rules
int hierarchyRules(int cell1x, int cell1y, int cell2x, int cell2y, Grid &grid)
{
    int cell1AdjPop = 0;
    int cell2AdjPop = 0;

    if (grid[cell1x][cell1y].zoneType == 'C' && grid[cell2x][cell2y].zoneType != 'C')
    {

        return 1;
    }
    if (grid[cell2x][cell2y].zoneType == 'C' && grid[cell1x][cell1y].zoneType != 'C')
    {
        return 2;
    }
    if (grid[cell1x][cell1y].population > grid[cell2x][cell2y].population)
    {
        return 1;
    }
    if (grid[cell1x][cell1y].population < grid[cell2x][cell2y].population)
    {
        return 2;
    }
    int rows = grid.size();
    int cols = grid[0].size();

    int xMax = cell1x + 1;
    int xMin = cell1x - 1;
    int yMax = cell1y + 1;
    int yMin = cell1y - 1;
    int adjToCell = 0;
    if (xMax > grid.size() - 1)
    {
        xMax = grid.size() - 1;
    }
    if (xMin < 0)
    {
        xMin = 0;
    }
    if (yMax > grid[0].size() - 1)
    {
        yMax = grid[0].size() - 1;
    }
    if (yMin < 0)
    {
        yMin = 0;
    }
    for (int x = xMin; x < xMax + 1; x++)
    {
        for (int y = yMin; y < yMax + 1; y++)
        {
            cell1AdjPop += grid[x][y].population;
        }
    }

    xMax = cell2x + 1;
    xMin = cell2x - 1;
    yMax = cell2y + 1;
    yMin = cell2y - 1;

    if (xMax > grid.size() - 1)
    {
        xMax = grid.size() - 1;
    }
    if (xMin < 0)
    {
        xMin = 0;
    }
    if (yMax > grid[0].size() - 1)
    {
        yMax = grid[0].size() - 1;
    }

    if (yMin < 0)
    {
        yMin = 0;
    }
    for (int x = xMin; x < xMax + 1; x++)
    {
        for (int y = yMin; y < yMax + 1; y++)
        {

            cell2AdjPop += grid[x][y].population;
        }
    }

    if (cell1AdjPop > cell2AdjPop)
    {
        return 1;
    }
    if (cell1AdjPop < cell2AdjPop)
    {
        return 2;
    }
    if (cell1x < cell2x || cell1y < cell2y)
    {
        return 1;
    }
    else
    {
        return 2;
    }
}

void outputRegionState(Grid &grid)
{
    cout << " ";
    for (int x = 0; x < grid.size(); x++)
    {
        cout << " " << x;
    }
    cout << endl;

    int y = 0;
    for (auto &row : grid)
    {
        cout << y << " ";
        ++y;
        for (auto &cell : row)
        {
            if (cell.population == 0)
            {
                cout << cell.zoneType << ' ';
            }
            else
            {
                // test cleanup
                // cout<<cell.numCleanup<<"/";
                cout << cell.population << ' ';
            }
        }
        cout << endl;
    }
}
int sumAvailableWorkers(vector<CommercialRegion> CommercialRegions, vector<ResidentialRegion> ResidentialRegions, vector<IndustrialRegion> IndustrialRegions, vector<vector<Cell>> grid)
{
    int workers = 0;
    int people = 0;
    for (int i = 0; i < CommercialRegions.size(); i++)
    {
        workers += CommercialRegions[i].workers;
    }

    for (int i = 0; i < IndustrialRegions.size(); i++)
    {
        workers += IndustrialRegions[i].workers;
    }

    for (int i = 0; i < ResidentialRegions.size(); i++)
    {
        int x = ResidentialRegions[i].i;
        int y = ResidentialRegions[i].j;
        people += grid[x][y].population;
    }
    return (people - workers);
}

int sumPop(vector<CommercialRegion> CommercialRegions, vector<ResidentialRegion> ResidentialRegions, vector<IndustrialRegion> IndustrialRegions, vector<vector<Cell>> grid)
{
    int people = 0;
    for (int i = 0; i < CommercialRegions.size(); i++)
    {
        int x = CommercialRegions[i].i;
        int y = CommercialRegions[i].j;
        people += grid[x][y].population;
    }

    for (int i = 0; i < IndustrialRegions.size(); i++)
    {
        int x = IndustrialRegions[i].x;
        int y = IndustrialRegions[i].y;
        people += grid[x][y].population;
    }

    for (int i = 0; i < ResidentialRegions.size(); i++)
    {
        int x = ResidentialRegions[i].i;
        int y = ResidentialRegions[i].j;
        people += grid[x][y].population;
    }
    return people;
}

int main()
{
    int goods = 0;
    vector<CommercialRegion> CommercialRegions;
    vector<ResidentialRegion> ResidentialRegions;
    vector<IndustrialRegion> IndustrialRegions;
    vector<EducationRegion> EducationRegions;
    cout << "Enter the name of your configuration file: ";
    string configFilename;
    getline(cin, configFilename);
    Config config = readConfigFile(configFilename);
    HospitalRegion Hospital;
    vector<EducationRegion> educationRegions;
    cout << "Region layout file: " << config.regionLayoutFile << endl;
    cout << "Max time steps: " << config.maxTimeSteps << endl;
    cout << "Refresh rate: " << config.refreshRate << endl;

    Grid grid;

    string regionLayoutFile = config.regionLayoutFile;
    initializeCityGrid(regionLayoutFile, grid, ResidentialRegions, CommercialRegions, IndustrialRegions, Hospital, EducationRegions);

    // set power plant type
    setPowerPlantType(grid);

    // Outputting initial state
    outputRegionState(grid);

    // Outputting the tree population at the beginning
    assignTree(grid);
    cout << "Total trees before the simulation: " << sumTree(grid) << endl;

    // SIMULATION
    //  At the final state, the pollution function should be called.
    int step;
    int currentPop;
    int previousPop = -1;
    for (step = 1; step <= config.maxTimeSteps; ++step)
    {
        // call on each function.

        vector<vector<Cell>> temp = grid;
        for (int i = 0; i < CommercialRegions.size(); i++)
        {
            for (int j = i + 1; j < CommercialRegions.size(); j++)
            {

                int x1 = CommercialRegions[i].i;
                int y1 = CommercialRegions[i].j;
                int x2 = CommercialRegions[j].i;
                int y2 = CommercialRegions[j].j;
                if (hierarchyRules(x1, y1, x2, y2, grid) == 2)
                {
                    swap(CommercialRegions[i], CommercialRegions[j]);
                }
            }
        }

        for (int i = 0; i < IndustrialRegions.size(); i++)
        {
            int x1 = IndustrialRegions[i].x;
            int y1 = IndustrialRegions[i].y;

            for (int j = i + 1; j < IndustrialRegions.size(); j++)
            {

                int x2 = IndustrialRegions[j].x;
                int y2 = IndustrialRegions[j].y;
                if (hierarchyRules(x1, y1, x2, y2, grid) == 2)
                {
                    swap(IndustrialRegions[i], IndustrialRegions[j]);
                }
            }
        }

        int com = 0;
        int ind = 0;
        int timesran = 0;

        while (com < CommercialRegions.size() || ind < IndustrialRegions.size())
        {

            timesran = 0;
            while (com < CommercialRegions.size() && timesran < 2)
            {
                int availableWorkers = sumAvailableWorkers(CommercialRegions, ResidentialRegions, IndustrialRegions, temp);
                if (CommercialRegions[com].simulateStep(grid, temp, availableWorkers, goods) == false && timesran > 2)
                {
                    timesran++;
                    break;
                }
                com++;
            }
            while (ind < IndustrialRegions.size())
            {
                int availableWorkers = sumAvailableWorkers(CommercialRegions, ResidentialRegions, IndustrialRegions, temp);
                if (IndustrialRegions[ind].simStep(grid, temp, availableWorkers, goods) == true)
                {
                    break;
                }
                ind++;
            }
        }

        for (int i = 0; i < ResidentialRegions.size(); i++)
        {
            ResidentialRegions[i].simulateRes(grid, temp);
            ResidentialRegions[i].newRes(grid, temp);
        }

        Hospital.simStep(grid, temp);
        for (EducationRegion &region : educationRegions)
        {
            region.simStep(grid, temp);
        }

        // perform any necessary operations for each time step here
        currentPop = sumPop(CommercialRegions, ResidentialRegions, IndustrialRegions, grid);
        grid = temp;

        if (currentPop != previousPop)
        {
            previousPop = currentPop;
            continue;
        }
        else
        {
            break;
        }
    }

    // Change the pollution
    incPoll(grid, IndustrialRegions);
    // Spread pollution from Power Plants
    for (int step = 1; step <= config.maxTimeSteps; ++step) {
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                if (grid[i][j].zoneType == 'S' || grid[i][j].zoneType == 'N' || grid[i][j].zoneType == 'W') {
                    //intializes PowerPlant object
                    PowerPlant curr(grid[i][j].zoneType, grid[i][j].pollution);
                    //increases pollution
                    curr.pollPowerPlant(grid);
                }
            }
        }
    }
    // Change the trees population
    changeTree(grid);
    // Assign residential types
    housingType(grid, ResidentialRegions);

    // Outputting final state
    cout << "\n**Final State**\n";
    outputRegionState(grid);

    // Output the final regional pollution state
    cout << "Total pollution: " << sumPoll(grid) << endl;

    // Output the tree population in the end
    cout << "Total trees left: " << sumTree(grid) << endl;

    // Output the total houses and apartments in the city
    cout << "Total # of Houses: " << sumHouses(grid) << endl;
    cout << "Total # of Apartments: " << sumApartments(grid) << endl;

    // Output Doomsday Estimation
    PrintDoomsday(sumPoll(grid), grid.size(), grid[1].size(), step);

    // Ask the user to input the area they want to see
    int Lrow, Rrow;
    int Lcol, Rcol;
    int maxRows = grid.size();
    int maxCols = grid[0].size();
    bool coordinates = true;

    // While the user inputs the inapplicable coordinates, keep prompting for new coordinates from them
    do
    {
        cout << "\nWhat area do you want to examine?\n";

        cout << "Based on the final state grid, please pick out your coordinates.\n\n";
        cout << "Enter top LEFT ROW number (ex: 0, 1, etc.): ";
        cin >> Lrow;
        cout << "Enter top LEFT COLUMN number (ex: 0, 1, etc.): ";
        cin >> Lcol;
        cout << "Enter bottom RIGHT ROW number (ex: 0, 1, etc.): ";
        cin >> Rrow;
        cout << "Enter bottom RIGHT COLUMN number (ex: 0, 1, etc.): ";
        cin >> Rcol;

        if (Lrow < 0 || Rrow < 0 || Lcol < 0 || Rcol < 0)
        {
            cout << "You enter a negative coordinate, please try again...\n";
            coordinates = false;
        }
        else if (Lrow > maxRows || Rrow > maxRows || Lcol > maxCols || Rcol > maxCols)
        {
            cout << "Your coordinates are out of bound, please try again...\n";
            coordinates = false;
        }
    } while (coordinates == false);

    // Print out the state of the chosen region
    for (int i = Lrow; i <= Rrow; ++i)
    {
        for (int j = Lcol; j <= Rcol; ++j)
        {
            // If population is zero, print out the zone type
            if (grid[i][j].population == 0)
            {
                cout << grid[i][j].zoneType << ' ';
            }
            // Else if it is not zero, print out the population
            else
            {
                cout << grid[i][j].population << ' ';
            }
        }
        cout << endl;
    }

    cout << "Region pollution = " << sumregionPoll(grid, Lrow, Rrow, Lcol, Rcol) << endl;
    cout << "Region tree = " << sumregionTree(grid, Lrow, Rrow, Lcol, Rcol) << endl;
    cout << "Region Houses = " << sumRegionHouses(grid, Lrow, Rrow, Lcol, Rcol) << endl;
    cout << "Region Apartments = " << sumRegionApartments(grid, Lrow, Rrow, Lcol, Rcol) << endl;

    // Natural disaster: Flood
    cout << "\n\n***FLOOD WARNING!!!!***\n\n";
    cout << "Will the city survive?\n";
    bool survive = flood(grid);

    if (!survive)
    {
        cout << "The city will not survive, plan more trees next time :C!\n";
    }
    else
    {
        cout << "Whew...The city survive, keep planting trees :D!\n\n";
    }

    return 0;
}
