#include <iostream>
#include <vector>
#include <algorithm>
#include "./Headers/structures.h"

void orOpt3(reOptimization &bestNeighbour, vector<vector<Subseq>> subseqInfo, Solution &solution, double **matrizAdj) {

    int bestI, bestJ, lastSwitchablevertex = solution.circuit.size()-2;
    double cost, bestCost = __DBL_MAX__;
    vector<int> circuit = solution.circuit;

    for(int i = 1; i < lastSwitchablevertex - 3; i++) {
        for(int j = i + 3; j <= lastSwitchablevertex; j++) {
            
            cost = subseqInfo[DEPOT][i-1].cost
                    +subseqInfo[i+3][j].width * (subseqInfo[DEPOT][i-1].time
                                                    +matrizAdj[circuit[i-1]][circuit[i+3]])
                    +subseqInfo[i+3][j].cost
                    + subseqInfo[i][i+2].width * (subseqInfo[0][i-1].time
                            +matrizAdj[circuit[i-1]][circuit[i+3]]
                            +subseqInfo[i+3][j].time
                            +matrizAdj[circuit[j]][circuit[i]])
                    +subseqInfo[i][i+2].cost
                    +subseqInfo[j+1][lastSwitchablevertex+1].width * (subseqInfo[0][i-1].time
                                                                        +matrizAdj[circuit[i-1]][circuit[i+3]]
                                                                        +subseqInfo[i+3][j].time
                                                                        +matrizAdj[circuit[j]][circuit[i]]
                                                                        +subseqInfo[i][i+2].time
                                                                        +matrizAdj[circuit[i+2]][circuit[j+1]])
                    +subseqInfo[j+1][lastSwitchablevertex+1].cost
                    ;
            
            if(cost < bestCost) {
                bestI = i;
                bestJ = j;
                bestCost = cost;
            }
        }
    }
    
    for(int i = 3; i < lastSwitchablevertex-1; i++) {

        for(int j = i - 1; j > DEPOT; j--) {

            cost = subseqInfo[DEPOT][j-1].cost
                    + subseqInfo[i][i+2].width * (subseqInfo[0][j-1].time + matrizAdj[circuit[j-1]][circuit[i]])
                    +subseqInfo[i][i+2].cost
                    +subseqInfo[j][i-1].width * (subseqInfo[0][j-1].time
                                                    +matrizAdj[circuit[j-1]][circuit[i]]
                                                    +subseqInfo[i][i+2].time
                                                    +matrizAdj[circuit[i+2]][circuit[j]])
                    +subseqInfo[j][i-1].cost
                    +subseqInfo[i+3][lastSwitchablevertex+1].width * (subseqInfo[0][j-1].time
                                                                        +matrizAdj[circuit[j-1]][circuit[i]]
                                                                        +subseqInfo[i][i+2].time
                                                                        +matrizAdj[circuit[i+2]][circuit[j]]
                                                                        +subseqInfo[j][i-1].time
                                                                        +matrizAdj[circuit[i-1]][circuit[i+3]])
                    +subseqInfo[i+3][lastSwitchablevertex+1].cost

                    ;

            if(cost < bestCost) {
                bestI = i;
                bestJ = j;
                bestCost = cost;
            }
        }
    }
    bestNeighbour.firstvertex = bestI;
    bestNeighbour.secondvertex = bestJ;
    bestNeighbour.cost = bestCost;
}