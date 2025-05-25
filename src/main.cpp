/**
 * @file main.cpp
 * @brief Ponto de entrada principal para o Otimizador de Paletes.
 * 
 * Permite ao utilizador carregar datasets e escolher entre diferentes algoritmos de otimização
 * para selecionar paletes com base em lucro e peso, respeitando a capacidade do caminhão.
 */

#include <iostream>
#include <sstream>
#include <iomanip>
#include <chrono> 
#include "../include/Dataset.h"
#include "../include/Solver.h"

/**
 * @brief Mostra o menu principal ao utilizador.
 */
void showMainMenu() {
    std::cout << "=== Otimizador de Paletes ===\n";
    std::cout << "1. Carregar Dataset e Executar Algoritmo\n";
    std::cout << "0. Sair\n";
    std::cout << "Escolha uma opção: ";
}

/**
 * @brief Mostra o menu de seleção de algoritmos.
 */
void showAlgorithmMenu() {
    std::cout << "\n--- Escolha o Algoritmo ---\n";
    std::cout << "1. Força Bruta\n";
    std::cout << "2. Programação Dinâmica\n";
    std::cout << "3. Guloso\n";
    std::cout << "4. Algoritmo Genético\n";
    std::cout << "0. Voltar\n";
    std::cout << "Opção: ";
}

/**
 * @brief Função principal do programa.
 * 
 * Esta função permite ao utilizador:
 * - Carregar datasets de paletes;
 * - Visualizar os dados carregados;
 * - Selecionar e executar um dos algoritmos disponíveis;
 * - Observar os resultados (lucro total, peso total e paletes selecionadas), assim como o tempo de execução.
 * 
 * Algoritmos disponíveis:
 * - Força Bruta: Garante solução ótima, mas com complexidade exponencial O(2^n).
 * - Programação Dinâmica: Solução ótima com complexidade O(n * W), onde W é a capacidade do caminhão.
 * - Guloso: Solução aproximada com tempo linearithmic O(n log n), baseada em razão lucro/peso.
 * - Algoritmo Genético: Solução heurística com tempo dependente de parâmetros (gerações, população, etc).
 * 
 * @return int Código de saída do programa (0 se encerrado com sucesso).
 */
int main() {
    int opcao;

    do {
        showMainMenu();
        std::cin >> opcao;

        switch (opcao) {
            case 1: {
                std::string rawInput;
                std::cout << "Introduza o número do dataset (ex: 01, 02, 03...): ";
                std::cin >> rawInput;

                std::stringstream ss;
                int num = std::stoi(rawInput);
                ss << std::setfill('0') << std::setw(2) << num;
                std::string datasetId = ss.str();

                Dataset d = loadDataset(datasetId);

                std::cout << "\nCapacidade do camião: " << d.capacity << " kg\n";
                std::cout << "Número de paletes: " << d.pallets.size() << "\n";
                for (const auto& p : d.pallets) {
                    std::cout << "P" << p.id << " - Peso: " << p.weight << ", Lucro: " << p.profit << "\n";
                }

                int algChoice;
                do {
                    showAlgorithmMenu();
                    std::cin >> algChoice;

                    switch (algChoice) {
                        case 1: {
                            /**< Força Bruta - Solução ótima (Complexidade: O(2^n)) */
                            auto start = std::chrono::high_resolution_clock::now();
                            Solution sol = solveBruteForce(d);
                            auto end = std::chrono::high_resolution_clock::now();
                            std::chrono::duration<double, std::milli> duration = end - start;

                            std::cout << "\n>> Solução ótima (Força Bruta):\n";
                            std::cout << "Lucro total: " << sol.totalProfit << "\n";
                            std::cout << "Peso total: " << sol.totalWeight << "\n";
                            std::cout << "Paletes escolhidas: ";
                            for (int id : sol.selectedPallets)
                                std::cout << "P" << id << " ";
                            std::cout << "\n";
                            std::cout << "Tempo de execução: " << duration.count() << " ms\n";
                            break;
                        }
                        case 2: {
                            /**< Programação Dinâmica - Solução ótima (Complexidade: O(n * W)) */
                            auto start = std::chrono::high_resolution_clock::now();
                            Solution sol = solveDynamicProgramming(d);
                            auto end = std::chrono::high_resolution_clock::now();
                            std::chrono::duration<double, std::milli> duration = end - start;

                            std::cout << "\n>> Solução ótima (Programação Dinâmica):\n";
                            std::cout << "Lucro total: " << sol.totalProfit << "\n";
                            std::cout << "Peso total: " << sol.totalWeight << "\n";
                            std::cout << "Paletes escolhidas: ";
                            for (int id : sol.selectedPallets)
                                std::cout << "P" << id << " ";
                            std::cout << "\n";
                            std::cout << "Tempo de execução: " << duration.count() << " ms\n";
                            break;
                        }
                        case 3: {
                            /**< Guloso - Solução aproximada (Complexidade: O(n log n)) */
                            auto start = std::chrono::high_resolution_clock::now();
                            Solution sol = solveGreedy(d);
                            auto end = std::chrono::high_resolution_clock::now();
                            std::chrono::duration<double, std::milli> duration = end - start;

                            std::cout << "\n>> Solução aproximada (Guloso):\n";
                            std::cout << "Lucro total: " << sol.totalProfit << "\n";
                            std::cout << "Peso total: " << sol.totalWeight << "\n";
                            std::cout << "Paletes escolhidas: ";
                            for (int id : sol.selectedPallets)
                                std::cout << "P" << id << " ";
                            std::cout << "\n";
                            std::cout << "Tempo de execução: " << duration.count() << " ms\n";
                            break;
                        }
                        case 4: {
                            /**< Algoritmo Genético - Solução aproximada (Complexidade variável) */
                            auto start = std::chrono::high_resolution_clock::now();
                            Solution sol = solveGeneticAlgorithm(d);
                            auto end = std::chrono::high_resolution_clock::now();
                            std::chrono::duration<double, std::milli> duration = end - start;

                            std::cout << "\n>> Solução aproximada (Algoritmo Genético):\n";
                            std::cout << "Lucro total: " << sol.totalProfit << "\n";
                            std::cout << "Peso total: " << sol.totalWeight << "\n";
                            std::cout << "Paletes escolhidas: ";
                            for (int id : sol.selectedPallets)
                                std::cout << "P" << id << " ";
                            std::cout << "\n";
                            std::cout << "Tempo de execução: " << duration.count() << " ms\n";
                            break;
                        }
                        case 0:
                            std::cout << "A voltar...\n";
                            break;
                        default:
                            std::cout << "Opção inválida.\n";
                    }
                } while (algChoice != 0);

                break;
            }

            case 0:
                std::cout << "A sair...\n";
                break;

            default:
                std::cout << "Opção inválida.\n";
        }

        std::cout << "\n";
    } while (opcao != 0);

    return 0;
}


