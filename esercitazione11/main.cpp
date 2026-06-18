#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include "adapter.hpp"
#include "finding_path.hpp"
#include "DePina.hpp"

// grafo di test condiviso tra i due test
undirected_graph<int> costruisci_grafo() {
    undirected_graph<int> G;
    G.add_edge(1,3); G.add_edge(6,3); G.add_edge(6,8); G.add_edge(6,1);
    G.add_edge(1,4); G.add_edge(4,6); G.add_edge(6,7); G.add_edge(8,9);
    G.add_edge(4,7); G.add_edge(4,2); G.add_edge(1,2);
    G.add_edge(7,2); G.add_edge(5,7); G.add_edge(5,2); G.add_edge(7,9);
    return G;
}

void test_finding_path() {
    std::cout << "TEST 1: find_path" << std::endl;

    undirected_graph<int> G = costruisci_grafo();
    auto albero  = recursive_dfs(G, 1);
    auto coalbero = G - albero;

    for (const auto& arco : coalbero.all_edges()) {
        int u = arco.from();
        int v = arco.to();
        std::vector<int> cammino = find_path(albero, u, v);

        std::cout << "Arco coalbero (" << u << "," << v << ") -> Ciclo: ";
        for (int nodo : cammino) std::cout << nodo << " -> ";
        std::cout << u << std::endl;
    }
    std::cout << std::endl;
}

void test_de_pina() {
    std::cout << "TEST 2: base di cicli minimi (De Pina)  " << std::endl;

    undirected_graph<int> G = costruisci_grafo();
    std::vector<std::vector<int>> base = de_pina(G);

    int attesi = G.all_edges().size() - G.all_nodes().size() + 1;
    std::cout << "Cicli attesi:  " << attesi << std::endl;
    std::cout << "Cicli trovati: " << base.size() << std::endl << std::endl;

    for (size_t i = 0; i < base.size(); ++i) {
        int lunghezza = 0;
        for (int val : base[i]) lunghezza += val;

        std::cout << "Ciclo " << i+1 << " : ";

        if (lunghezza == 0) {
            std::cout << "Ciclo vuoto";
        } else {
            for (int e = 0; e < (int)base[i].size(); ++e) {
                if (base[i][e] == 1) {
                    auto arco = G.edge_at(e);
                    if (arco) std::cout << *arco << " ";
                }
            }
        }
        std::cout << std::endl;
    }
}

int main() {
    test_finding_path();
    test_de_pina();
    return 0;
}