#include "Doomsday.h"
#include <iostream>
#include <cmath>

using namespace std;

//find average pollution per cell
double PollAvg(int totPoll, int numRows, int numCols) {
    int totCells = numRows*numCols;
    return ((double)totPoll/(double)totCells);
}

//find pollution rate based on initial and final pollution over time
double PollRate(double finPoll, int numYrs) {
    return (finPoll/numYrs);
}

//pollution at given time t years: pollution(t) = rate*t
//time t where pollution reaches threshold: tDoomsday = pollMax/rate
double YrsToDoomsday(int pollMax, double pollRate) {
    if (pollRate!=0) {
        return (pollMax/pollRate);
    }
    else {
        return (-1);
    }
}

//return number of years til doomsday (Christmas Day 🎅)
void PrintDoomsday(int totPoll, int numRows, int numCols, int numYrs) {
    //Maximum average pollution per cell
    int pollThreshold = 50;
    double avg = PollAvg(totPoll,numRows,numCols);
    double rate = PollRate(avg,numYrs);
    int yrsTilDoom = ceil(YrsToDoomsday(pollThreshold,rate));
    if (yrsTilDoom == -1) {
        cout<<"Congratulations! The pollution in the region has remained at 0. The world won't end because of pollution."<<endl;
    }
    else {
        //yrs til doom starting from end of simulation
        yrsTilDoom -=numYrs;
        //End of the world year is estimated from the current year (2024)
        int DoomYr = yrsTilDoom+2024;
        
        cout<<"The world will end due to overpollution in "<<yrsTilDoom<<" years."<<endl;
        cout<<"Doomsday: Dec. 25, "<<DoomYr<<endl;
    }


}

//     *
//    /@\
//   /@ @\
//  /@ @ @\
// /@ @ @ @\
// ___| |___ 

