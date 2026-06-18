#pragma once
#include <vector>
#include <set>
#include <map>
#include <limits>
#include <algorithm>
#include "adapter.hpp"
#include "finding_path.hpp"

// LiftingNode: rappresenta un nodo "sdoppiato" nel grafo G' 
// Ogni nodo v del grafo originale diventa v+ (positivo=true) oppure v- (positivo=false)
template <typename T>
struct LiftingNode {
	T nodo_originale; // nodo originario del grafo G
	bool positivo; //true se rappresenta v+, false se rappresenta v-
	
	bool operator<(const LiftingNode& other) const {
		if (nodo_originale != other.nodo_originale) {
			return nodo_originale < other.nodo_originale;
		}
		return positivo < other.positivo; 
		// v- viene prima di v+; ossia v- (false=0) precede v+ (true=1)
	}
	// operatore= per controllare se due nodi sdoppiati coincidono perfettamente
	bool operator==(const LiftingNode& other) const {
		return nodo_originale == other.nodo_originale && positivo == other.positivo;
	}
	
	bool operator!=(const LiftingNode& other) const {return !(*this == other);}
	bool operator<=(const LiftingNode& other) const {return (*this < other) || (*this == other);}
};

template <typename T>
std::vector<int> trova_ciclo_minimo(const undirected_graph<T>& grafo, const std::vector<int>& S, int n) {

    // costruisco G' --> conterrà i nodi sdoppiati
    undirected_graph<LiftingNode<T>> G_ausiliario;

    for (const auto& arco:grafo.all_edges()) {
        T u=arco.from();
        T v=arco.to();

        auto indice = grafo.edge_number(arco);
        bool attivo=indice && S[*indice] == 1;

        LiftingNode<T> u_pos{u, true}, u_neg{u, false};
        LiftingNode<T> v_pos{v, true}, v_neg{v, false};

        if (attivo) {
            G_ausiliario.add_edge(u_pos,v_neg);
            G_ausiliario.add_edge(u_neg,v_pos);
        } else {
            G_ausiliario.add_edge(u_pos,v_pos);
            G_ausiliario.add_edge(u_neg,v_neg);
        }
    }

    // per ogni cammino v- -> v+
    std::vector<int> ciclo_migliore;
    int minimo = std::numeric_limits<int>::max();

    for (T v:grafo.all_nodes()) {
        LiftingNode<T> v_neg{v,false};
        LiftingNode<T> v_pos{v,true};

        // dijikstra da v- in G' 
        auto albero = dijkstra(G_ausiliario,v_neg);

        //ricostruisco il cammino v- -> v+ sull'albero
        std::vector<LiftingNode<T>> cammino = find_path(albero, v_neg, v_pos);
        if (cammino.empty()) continue;

        //costruisco vettore di incidenza 
        std::vector<int> vet(n,0);
        for (int i=0; i<(int)cammino.size()-1; ++i) {
            T u_orig = cammino[i].nodo_originale;
            T v_orig = cammino[i+1].nodo_originale;

            undirected_edge<T> arco(u_orig,v_orig);
            auto indice = grafo.edge_number(arco);
            if (indice) vet[*indice] ^= 1;
        }

        int count = 0;
        for (int x:vet) count += x;
        if (count > 0 && count < minimo) {
            minimo = count;
            ciclo_migliore = vet;
        }
    }
    return ciclo_migliore;
}

template <typename T>
std::vector<std::vector<int>> de_pina(const undirected_graph<T>& grafo) {
    
    //1. albero DFS e coalbero
    int n=grafo.all_edges().size();
    T sorgente = *grafo.all_nodes().begin();

    auto albero = recursive_dfs(grafo, sorgente);
    auto coalbero = grafo - albero;
    int k = coalbero.all_edges().size();

    //2. inizializzo S: S[i] ha 1 solo nella posizione dell'i-esimo arco del coalbero
    std::vector<std::vector<int>> S(k, std::vector<int>(n,0));
    int i=0;
    for (const auto& arco:coalbero.all_edges()) {
        auto indice = grafo.edge_number(arco);
        if (indice) S[i][*indice] = 1;
        i++;
    }

    std::vector<std::vector<int>> B;
    for (int i=0;i<k; ++i) {
        std::vector<int> Ci = trova_ciclo_minimo(grafo, S[i], n);
        B.push_back(Ci);
        for (int j=i+1; j<k; ++j) {
            int prod =0; 
            for (int e=0; e<n; ++e) {
                prod += Ci[e]*S[j][e];
            }
            prod %= 2;
            if (prod==1) {
                for (int e=0; e<n; ++e) {
                    S[j][e] ^= S[i][e];
                }
            }
        }
    }

    return B;

    }