#include <iostream>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <vector>
#include <limits>
#include <optional>
#include "adapter.hpp"

// funzione per stampa 
template<typename T>
void stampa_grafo(const std::string& nome, const undirected_graph<T>& g) {
	std::cout << "===" << nome << "===\n";
	std::cout << "Nodi: ";
	for (T nodo: g.all_nodes()) {
		std::cout << nodo << " ";
	}
	std::cout << "\nArchi: ";
	for (const auto& arco : g.all_edges()) {
		std::cout << arco << " ";
	}
	std::cout<<std::endl;
}

int main() {
	undirected_graph<int> G;
	G.add_edge(1,3);
	G.add_edge(6,3);
	G.add_edge(6,8);
	G.add_edge(6,1);
	G.add_edge(1,4);
	G.add_edge(4,6);
	G.add_edge(6,7);
	G.add_edge(8,9);
	G.add_edge(7,6);
	G.add_edge(4,7);
	G.add_edge(4,2);
	G.add_edge(1,2);
	G.add_edge(7,2);
	G.add_edge(5,7);
	G.add_edge(5,2);
	G.add_edge(7,9);
	
	stampa_grafo("Grafo G (interi)", G);
	
	// applicazione BFS
	fifo<int> q;
	auto bfsG = graph_visit(G,1,q);
	stampa_grafo("BFS da nodo 1", bfsG);
	
	esporta_dot(bfsG, "bfs_1.dot", "BFS_1");
	
	// applicazione DFS (con LIFO)
	lifo<int> s;
	auto dfsG = graph_visit(G,1,s);
	stampa_grafo("DFS da nodo 1", dfsG);
	
	esporta_dot(dfsG, "dfs_1.dot", "DFS_1");
	
	// DFS ricorsiva
	auto rdfsG = recursive_dfs(G,1);
	stampa_grafo("DFS ricorsiva da nodo 1", rdfsG);
	
	esporta_dot(rdfsG, "rdfs_1.dot", "RDFS_1");
	
	// Dijkstra SENZA PESI --> ogni arco ha peso =1.0 per ipotesi

	auto albero_dijkstra = dijkstra(G,1); //calcolo partendo dal nodo 1
	std::cout << "=== Albero dei Cammini Minimi da nodo 1 ===\n";
	for (const auto& arco : albero_dijkstra.all_edges()) {
		std::cout << " Arco inserito nell'albero " << arco << "\n";
	}
	std::cout << "\n";
	
	esporta_dot(albero_dijkstra,"dijkstra_int.dot", "alberoInt_dijkstra");
	// mi aspetto che coincida con l'albero generato dal BFS: quando tutti gli archi hanno stesso peso, 
	// entrambi esplorano il grafo a "livelli" concentrici, basandosi sulla minima distanza dalla sorgente 

// -------------

	// grafo esempio con stringhe
	undirected_graph<std::string> G_string;
	G_string.add_edge("king","killer");
	G_string.add_edge("king","beat");
	G_string.add_edge("killer","snow");
	G_string.add_edge("killer","league");
	G_string.add_edge("beat","snow");
	G_string.add_edge("snow","diamonds");
	
	stampa_grafo("Grafo G_string (stringhe)", G_string);
	
	// applicazione BFS
	fifo<std::string> q_string;
	auto bfsG_string = graph_visit(G_string,std::string("king"),q_string);
	stampa_grafo("BFS dal nodo king", bfsG_string);
	
	esporta_dot(bfsG_string, "bfs_king.dot", "BFS_king");
	
	// applicazione DFS  (con LIFO)
	lifo<std::string> s_string;
	auto dfsG_string = graph_visit(G_string,std::string("king"),s_string);
	stampa_grafo("DFS da nodo king", dfsG_string);

	esporta_dot(dfsG_string, "dfs_king.dot", "DFS_king");
	
	// DFS ricorsiva
	auto rdfsG_string = recursive_dfs(G_string,std::string("king"));
	stampa_grafo("DFS ricorsiva da nodo king", rdfsG_string);
	
	esporta_dot(rdfsG_string,"rdfs_king.dot", "RDFS_king");
	
	// Dijkstra SENZA PESI --> ogni arco ha peso =1.0 per ipotesi
	auto albero_string_dijkstra = dijkstra(G_string,std::string("king")); 
	std::cout << "=== Albero dei Cammini Minimi con stringhe da nodo king ===\n";
	for (const auto& arco : albero_string_dijkstra.all_edges()) {
		std::cout << " Arco inserito nell'albero " << arco << "\n";
	}
	std::cout << "\n";
	
	esporta_dot(albero_string_dijkstra,"dijkstra_string.dot", "alberoString_dijkstra");

	return 0;	
}

// per la revisione del codice e la correzione di bug logici, ci si è avvalsi del supporto dell'intelligienza artificiale (Gemini/Claude.ai)