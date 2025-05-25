/**
 * @file dataset.h
 * @brief Declaração das estruturas e funções relacionadas ao dataset de paletes.
 */

#ifndef DATASET_H
#define DATASET_H

#include <string>
#include <vector>

/**
 * @struct Pallet
 * @brief Representa uma palete armazenada no dataset.
 */
struct Pallet {
    int id;       /**< Identificador único da palete. */
    int weight;   /**< Peso da palete. */
    int profit;   /**< Lucro associado à palete. */
};

/**
 * @struct Dataset
 * @brief Representa um conjunto de paletes e a capacidade máxima do camião.
 */
struct Dataset {
    int capacity;               /**< Capacidade máxima do camião (em kg). */
    int numPallets;             /**< Número total de paletes disponíveis. */
    std::vector<Pallet> pallets; /**< Lista de paletes disponíveis no dataset. */
};

/**
 * @brief Carrega um dataset a partir de ficheiros CSV com base no identificador fornecido.
 *
 * Esta função lê dois ficheiros CSV:
 * - `TruckAndPallets_<id>.csv`, que contém a capacidade do camião e o número de paletes.
 * - `Pallets_<id>.csv`, que contém os dados individuais das paletes (ID, peso, lucro).
 *
 * @param datasetId Identificador do dataset (por exemplo, "01", "02", etc.).
 * @return Um objeto Dataset preenchido com os dados lidos dos ficheiros.
 *
 * @note Complexidade temporal: O(n), onde n é o número de paletes no ficheiro.
 * @note Complexidade espacial: O(n), pois todos os dados das paletes são armazenados em memória.
 */
Dataset loadDataset(const std::string& datasetId);

#endif /* DATASET_H */


