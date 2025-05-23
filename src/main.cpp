#include <iostream>
#include <sstream>
#include <iomanip>
#include <chrono> 
#include <fstream>
#include "Dataset.h"
#include "Solver.h"

void showMainMenu() {
    std::cout << "=== Otimizador de Paletes ===\n";
    std::cout << "1. Carregar Dataset e Executar Algoritmo\n";
    std::cout << "0. Sair\n";
    std::cout << "Escolha uma opção: ";
}

void showAlgorithmMenu() {
    std::cout << "\n--- Escolha o Algoritmo ---\n";
    std::cout << "1. Força Bruta\n";
    std::cout << "2. Programação Dinâmica\n";
    std::cout << "3. Guloso\n";
    std::cout << "4. Algoritmo Genético\n";
    std::cout << "0. Voltar\n";
    std::cout << "Opção: ";
}

void writeCSVHeader(std::ofstream& out) {
    out << "Dataset,Algoritmo,Tempo(ms),Lucro,Peso\n";
}

void appendResult(std::ofstream& out, const std::string& datasetId, const std::string& algName, 
                  double timeMs, int profit, int weight) {
    out << datasetId << "," << algName << "," << timeMs << "," << profit << "," << weight << "\n";
}

int main() {
    int opcao;
    bool csvHeaderWritten = false;
    std::ofstream csvOut;

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
                if (!csvHeaderWritten) {
                    csvOut.open("results.csv", std::ios::out);
                    writeCSVHeader(csvOut);
                    csvHeaderWritten = true;
                } else {
                    csvOut.open("results.csv", std::ios::app);
                }

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

                            appendResult(csvOut, datasetId, "ForcaBruta", duration.count(), sol.totalProfit, sol.totalWeight);
                            break;
                        }
                        case 2: {
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

                            appendResult(csvOut, datasetId, "ProgDinamica", duration.count(), sol.totalProfit, sol.totalWeight);
                            break;
                        }
                        case 3: {
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

                            appendResult(csvOut, datasetId, "Guloso", duration.count(), sol.totalProfit, sol.totalWeight);
                            break;
                        }
                        case 4: {
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

                            appendResult(csvOut, datasetId, "AlgGenetico", duration.count(), sol.totalProfit, sol.totalWeight);
                            break;
                        }
                        case 0:
                            std::cout << "A voltar...\n";
                            break;
                        default:
                            std::cout << "Opção inválida.\n";
                    }
                } while (algChoice != 0);

                csvOut.close();
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
