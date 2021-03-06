#include <iostream>
#include <vector>
#include <algorithm>
#include "./Headers/functions.h"

void construction(Solution &solution, int dimension, double **matrizAdj) {

    double alfa = (rand() % 26)/(double) 100;    
    vector<int> circuit;
    vector<int> candidates;
    int lastVertex;

    circuit.push_back(1);
    lastVertex = 1;

    for(int i = 2; i <= dimension; i++) {
        candidates.push_back(i);
    }

    while(!candidates.empty()) {

        vector<InsertionInfo> insertionInfo;
        
        for(int i = 0; i < candidates.size(); i++) {
            insertionInfo.push_back({i, matrizAdj[candidates[i]][lastVertex]});
        }

        sort(insertionInfo.begin(), insertionInfo.end(), Compare);
        
        int n = (int)(alfa * insertionInfo.size());
        int N = n != 0 ? (rand() % n) : 0; 

        circuit.push_back(candidates[insertionInfo[N].insertedVertex]);
        lastVertex = candidates[insertionInfo[N].insertedVertex];
        candidates.erase(candidates.begin() + insertionInfo[N].insertedVertex);
    }

    circuit.push_back(1);
    
    solution.circuit = circuit;
}

bool Compare(InsertionInfo v1, InsertionInfo v2) {
    return v1.cost < v2.cost;
}