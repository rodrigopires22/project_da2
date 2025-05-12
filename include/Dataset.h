#ifndef DATASET_H
#define DATASET_H

#include <string>
#include <vector>

struct Pallet {
    int id;
    int weight;
    int profit;
};

struct Dataset {
    int capacity;
    int numPallets;
    std::vector<Pallet> pallets;
};

Dataset loadDataset(const std::string& datasetId);

#endif 
