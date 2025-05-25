/**
 * @file dataset.cpp
 * @brief Implementação da função para carregar um dataset de pallets a partir de ficheiros CSV.
 */

#include "../include/Dataset.h"
#include <fstream>
#include <sstream>
#include <iostream>

/**
 * @brief Carrega um dataset com base no identificador fornecido.
 * 
 * Esta função lê dois ficheiros CSV:
 * - `TruckAndPallets_<datasetId>.csv`, que contém a capacidade do caminhão e o número de pallets;
 * - `Pallets_<datasetId>.csv`, que contém os dados individuais dos pallets (id, peso, lucro).
 * 
 * @param datasetId Identificador do dataset, usado para compor os nomes dos ficheiros.
 * @return Dataset Estrutura contendo a capacidade do caminhão, número de pallets e a lista de pallets carregados.
 * 
 * @note Complexidade temporal: O(n), onde n é o número de pallets.
 * @note Complexidade espacial: O(n), para armazenar os dados dos pallets na memória.
 */
Dataset loadDataset(const std::string& datasetId) {
    Dataset dataset;
    std::string base = "data/";

    // Abre o ficheiro com informações do caminhão e número de pallets
    std::ifstream truckFile(base + "TruckAndPallets_" + datasetId + ".csv");
    if (!truckFile.is_open()) {
        std::cerr << "Erro ao abrir ficheiro TruckAndPallets_" << datasetId << ".csv\n";
        return dataset;
    }

    std::string line;
    getline(truckFile, line);  // Ignora a linha de cabeçalho
    getline(truckFile, line);  // Lê a linha com os dados
    std::stringstream ss(line);
    std::string token;

    getline(ss, token, ',');
    dataset.capacity = std::stoi(token);  ///< Capacidade total do caminhão
    getline(ss, token, ',');
    dataset.numPallets = std::stoi(token);  ///< Número total de pallets disponíveis
    truckFile.close();

    // Abre o ficheiro com os dados individuais dos pallets
    std::ifstream palletsFile(base + "Pallets_" + datasetId + ".csv");
    if (!palletsFile.is_open()) {
        std::cerr << "Erro ao abrir ficheiro Pallets_" << datasetId << ".csv\n";
        return dataset;
    }

    getline(palletsFile, line);  // Ignora o cabeçalho
    while (getline(palletsFile, line)) {
        std::stringstream ssP(line);
        Pallet p;

        getline(ssP, token, ',');
        p.id = std::stoi(token);  ///< Identificador do pallet
        getline(ssP, token, ',');
        p.weight = std::stoi(token);  ///< Peso do pallet
        getline(ssP, token, ',');
        p.profit = std::stoi(token);  ///< Lucro associado ao pallet

        dataset.pallets.push_back(p);
    }

    palletsFile.close();
    return dataset;
}
