#include <iostream>
#include <sstream>
#include <iomanip>
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
    std::cout << "2. Programação Dinâmica (em breve)\n";
    std::cout << "3. Guloso (em breve)\n";
    std::cout << "0. Voltar\n";
    std::cout << "Opção: ";
}

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
                            Solution sol = solveBruteForce(d);
                            std::cout << "\n>> Solução ótima (Força Bruta):\n";
                            std::cout << "Lucro total: " << sol.totalProfit << "\n";
                            std::cout << "Peso total: " << sol.totalWeight << "\n";
                            std::cout << "Paletes escolhidas: ";
                            for (int id : sol.selectedPallets)
                                std::cout << "P" << id << " ";
                            std::cout << "\n";
                            break;
                        }
                        case 2:
                        case 3:
                            std::cout << "Algoritmo ainda não implementado.\n";
                            break;
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
