/**
 * @file solver.h
 * @brief Declaração das estruturas e funções para solucionar problemas de otimização de paletes.
 */

#ifndef SOLVER_H
#define SOLVER_H

#include "../include/Dataset.h"
#include <vector>

/**
 * @struct Solution
 * @brief Estrutura que representa uma solução para a otimização de paletes.
 *
 * Contém o peso total, lucro total e a lista de identificadores das paletes selecionadas.
 */
struct Solution {
    int totalWeight = 0;               /**< Peso total das paletes selecionadas. */
    int totalProfit = 0;               /**< Lucro total obtido com as paletes selecionadas. */
    std::vector<int> selectedPallets;  /**< Lista de identificadores das paletes escolhidas. */
};

/**
 * @brief Resolve o problema da otimização usando força bruta.
 *
 * Gera todas as combinações possíveis de paletes e escolhe a que proporciona o maior lucro sem exceder a capacidade.
 *
 * @param dataset Conjunto de paletes disponíveis.
 * @return Solução ótima encontrada.
 *
 * @note Complexidade temporal: O(2^n), onde n é o número de paletes.
 * @note Complexidade espacial: O(n), devido ao armazenamento da melhor combinação.
 */
Solution solveBruteForce(const Dataset& dataset);

/**
 * @brief Resolve o problema da otimização usando programação dinâmica.
 *
 * Utiliza uma abordagem bottom-up semelhante ao problema clássico da mochila 0/1.
 *
 * @param dataset Conjunto de paletes disponíveis.
 * @return Solução ótima encontrada por programação dinâmica.
 *
 * @note Complexidade temporal: O(n * W), onde n é o número de paletes e W a capacidade do camião.
 * @note Complexidade espacial: O(n * W), para armazenar a matriz de soluções.
 */
Solution solveDynamicProgramming(const Dataset& dataset);

/**
 * @brief Resolve o problema da otimização usando uma abordagem gulosa.
 *
 * Ordena as paletes por lucro/peso e seleciona as mais rentáveis até atingir a capacidade máxima.
 *
 * @param dataset Conjunto de paletes disponíveis.
 * @return Solução aproximada utilizando heurística gulosa.
 *
 * @note Complexidade temporal: O(n log n), devido à ordenação das paletes.
 * @note Complexidade espacial: O(n), para armazenar as paletes escolhidas.
 */
Solution solveGreedy(const Dataset& dataset);

/**
 * @brief Resolve o problema da otimização utilizando um algoritmo genético.
 *
 * Usa operadores genéticos (seleção, cruzamento e mutação) para evoluir soluções ao longo de várias gerações.
 *
 * @param dataset Conjunto de paletes disponíveis.
 * @return Solução aproximada baseada em evolução genética.
 *
 * @note Complexidade temporal: O(G * P * n), onde G é o número de gerações, P o tamanho da população e n o número de paletes.
 * @note Complexidade espacial: O(P * n), devido ao armazenamento da população.
 */
Solution solveGeneticAlgorithm(const Dataset& dataset);

#endif /* SOLVER_H */


