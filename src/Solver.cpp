#include "Solver.h"
#include <cmath>

Solution solveBruteForce(const Dataset& dataset) {
    int n = dataset.pallets.size();
    int maxProfit = 0;
    int bestWeight = 0;
    std::vector<int> bestSelection;

    int totalComb = 1 << n;

    for (int mask = 0; mask < totalComb; ++mask) {
        int currentWeight = 0;
        int currentProfit = 0;
        std::vector<int> currentSelection;

        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                currentWeight += dataset.pallets[i].weight;
                currentProfit += dataset.pallets[i].profit;
                currentSelection.push_back(dataset.pallets[i].id);
            }
        }

        if (currentWeight <= dataset.capacity && currentProfit > maxProfit) {
            maxProfit = currentProfit;
            bestWeight = currentWeight;
            bestSelection = currentSelection;
        }
    }

    return {bestWeight, maxProfit, bestSelection};
}
