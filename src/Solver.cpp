#include "Solver.h"
#include <cmath>
#include <vector>
#include <algorithm>

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

Solution solveDynamicProgramming(const Dataset& dataset) {
    int n = dataset.pallets.size();
    int W = dataset.capacity;

    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(W + 1, 0));

    for (int i = 1; i <= n; ++i) {
        int w = dataset.pallets[i - 1].weight;
        int p = dataset.pallets[i - 1].profit;

        for (int cap = 0; cap <= W; ++cap) {
            if (w > cap)
                dp[i][cap] = dp[i - 1][cap];
            else
                dp[i][cap] = std::max(dp[i - 1][cap], dp[i - 1][cap - w] + p);
        }
    }

    int cap = W;
    std::vector<int> selected;
    int totalWeight = 0;
    for (int i = n; i > 0 && cap > 0; --i) {
        if (dp[i][cap] != dp[i - 1][cap]) {
            int w = dataset.pallets[i - 1].weight;
            int p = dataset.pallets[i - 1].profit;

            selected.push_back(dataset.pallets[i - 1].id);
            cap -= w;
            totalWeight += w;
        }
    }

    std::reverse(selected.begin(), selected.end());
    return {totalWeight, dp[n][W], selected};
}

Solution solveGreedy(const Dataset& dataset) {
    struct Item {
        int id, weight, profit;
        double ratio;
    };

    std::vector<Item> items;

    for (const auto& p : dataset.pallets) {
        items.push_back({p.id, p.weight, p.profit, (double)p.profit / p.weight});
    }

    std::sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return a.ratio > b.ratio;
    });

    int totalWeight = 0;
    int totalProfit = 0;
    std::vector<int> selected;

    for (const auto& item : items) {
        if (totalWeight + item.weight <= dataset.capacity) {
            totalWeight += item.weight;
            totalProfit += item.profit;
            selected.push_back(item.id);
        }
    }

    return {totalWeight, totalProfit, selected};
}
