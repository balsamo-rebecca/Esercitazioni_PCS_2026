#pragma once
#include <vector>
#include <set>
#include <algorithm>
#include "adapter.hpp"

template <typename T>
bool helper_find_path(const undirected_graph<T>& albero, const T& u, const T& v, std::set<T>& visitati, std::vector<T>& cammino) {
	visitati.insert(u);
	cammino.push_back(u);
	
	if (u==v) {
		return true;
	};
	
	auto vicini=albero.neighbours(u); 
	// per come ho definito neighbours in adapter, esso mi restituisce std::optional --> devo controllare se contiene un valore prima di usarlo
	// conteien una std::list<T>
	if (vicini) { // controllo che il nodo esista nel grafo e abbia dei vicini
		for (const T& vicino:*vicini) { //l'operatore *  "spacchetta" l'optional e mi permette di scorrere la lista
			if (!visitati.count(vicino)) {
				if (helper_find_path(albero, vicino, v, visitati, cammino)) {
					return true;
				}
			}
		}
	}
	
	cammino.pop_back();
	return false;
};

template <typename T> 
std::vector<T> find_path(const undirected_graph<T>& grafo, const T& u, const T& v) {
	std::set<T> visitati; 
	std::vector<T> cammino;
	
	if (helper_find_path(grafo, u, v, visitati, cammino)) {
		return cammino;
	}
	
	return {};
}