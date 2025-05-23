#include "Solver.h"
#include <cmath>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <iostream>
#include <stdexcept>


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

Solution solveGeneticAlgorithm(const Dataset& dataset) {
    const int POP_SIZE = 30;
    const int MAX_GENERATIONS = 20;
    const double MUTATION_RATE = 0.05;

    int n = static_cast<int>(dataset.pallets.size());
    int capacity = dataset.capacity;

    if (n == 0) {
        return {0, 0, {}};
    }

    std::mt19937 rng(static_cast<unsigned>(time(nullptr)));
    std::uniform_real_distribution<> probDist(0.0, 1.0);

    using Individual = std::vector<bool>;

    auto fitness = [&](const Individual& ind) -> int {
        int weight = 0, profit = 0;
        for (int i = 0; i < n; ++i) {
            if (ind[i]) {
                weight += dataset.pallets[i].weight;
                profit += dataset.pallets[i].profit;
            }
        }
        if (weight <= capacity) {
            return profit;
        } else {
            return profit - 10 * (weight - capacity);
        }
    };

    auto generateIndividual = [&]() -> Individual {
        Individual ind(n, false);
        for (int i = 0; i < n; ++i)
            ind[i] = probDist(rng) > 0.8;
        return ind;
    };

    auto crossover = [&](const Individual& a, const Individual& b) -> Individual {
        Individual child(n);
        std::uniform_int_distribution<> indexDist(0, n - 1);
        int point = indexDist(rng);
        for (int i = 0; i < n; ++i)
            child[i] = (i < point) ? a[i] : b[i];
        return child;
    };

    auto mutate = [&](Individual& ind) {
        for (int i = 0; i < n; ++i)
            if (probDist(rng) < MUTATION_RATE)
                ind[i] = !ind[i];
    };

    std::vector<Individual> population(POP_SIZE);
    for (int i = 0; i < POP_SIZE; ++i)
        population[i] = generateIndividual();

    Individual bestInd(n, false);
    int bestFitness = std::numeric_limits<int>::min();

    for (int gen = 0; gen < MAX_GENERATIONS; ++gen) {
        std::vector<std::pair<int, Individual>> scored;
        for (const auto& ind : population) {
            int f = fitness(ind);
            scored.emplace_back(f, ind);
            if (f > bestFitness) {
                bestFitness = f;
                bestInd = ind;
            }
        }

        std::sort(scored.rbegin(), scored.rend());

        int eliteSize = POP_SIZE / 4;
        if (eliteSize < 1) eliteSize = 1;

        std::vector<Individual> newPopulation;
        for (int i = 0; i < eliteSize; ++i)
            newPopulation.push_back(scored[i].second);

        std::uniform_int_distribution<> eliteIndexDist(0, eliteSize - 1);

        while ((int)newPopulation.size() < POP_SIZE) {
            int idx1 = eliteIndexDist(rng);
            int idx2 = eliteIndexDist(rng);

            Individual child = crossover(newPopulation[idx1], newPopulation[idx2]);
            mutate(child);
            newPopulation.push_back(child);
        }

        population = std::move(newPopulation);
    }

    if ((int)bestInd.size() != n) {
        return {0, 0, {}};
    }

    int totalWeight = 0;
    std::vector<int> selected;
    for (int i = 0; i < n; ++i) {
        if (bestInd[i]) {
            totalWeight += dataset.pallets[i].weight;
            selected.push_back(dataset.pallets[i].id);
        }
    }

    return {totalWeight, bestFitness, selected};
}
