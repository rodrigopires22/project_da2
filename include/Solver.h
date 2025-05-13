#ifndef SOLVER_H
#define SOLVER_H

#include "Dataset.h"
#include <vector>

struct Solution {
    int totalWeight;
    int totalProfit;
    std::vector<int> selectedPallets; 
};

Solution solveBruteForce(const Dataset& dataset);
Solution solveDynamicProgramming(const Dataset& dataset);
Solution solveGreedy(const Dataset& dataset);
Solution solveGeneticAlgorithm(const Dataset& dataset);

#endif
