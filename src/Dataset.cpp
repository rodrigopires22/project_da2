#include "Dataset.h"
#include <fstream>
#include <sstream>
#include <iostream>

Dataset loadDataset(const std::string& datasetId) {
    Dataset dataset;
    std::string base = "data/";

    std::ifstream truckFile(base + "TruckAndPallets_" + datasetId + ".csv");
    if (!truckFile.is_open()) {
        std::cerr << "Erro ao abrir ficheiro TruckAndPallets_" << datasetId << ".csv\n";
        return dataset;
    }

    std::string line;
    getline(truckFile, line); 
    getline(truckFile, line);
    std::stringstream ss(line);
    std::string token;

    getline(ss, token, ',');
    dataset.capacity = std::stoi(token);
    getline(ss, token, ',');
    dataset.numPallets = std::stoi(token);
    truckFile.close();

    std::ifstream palletsFile(base + "Pallets_" + datasetId + ".csv");
    if (!palletsFile.is_open()) {
        std::cerr << "Erro ao abrir ficheiro Pallets_" << datasetId << ".csv\n";
        return dataset;
    }

    getline(palletsFile, line); 
    while (getline(palletsFile, line)) {
        std::stringstream ssP(line);
        Pallet p;
        getline(ssP, token, ',');
        p.id = std::stoi(token);
        getline(ssP, token, ',');
        p.weight = std::stoi(token);
        getline(ssP, token, ',');
        p.profit = std::stoi(token);
        dataset.pallets.push_back(p);
    }

    palletsFile.close();
    return dataset;
}
