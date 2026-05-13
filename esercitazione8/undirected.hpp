#pragma once 
#include <optional>
#include <map>
#include <set>
#include <list>
#include <stdexcept>
#include <vector>
#include <ostream>
#include <algorithm>

// undirected_edge

// classe che rappresenta un arco in un grafo
// la classe ha un costruttore che permette di specificare i due nodi connessi dell'arco
// from() e to() metodi che restituiscono i due nodi
// la classe normalizza sempre i due nodi di un arco in ordine crescente

template<typename T>
class undirected_edge {
	T nodo1;
	T nodo2;
	
public: 
// voglio sempre che from < to, (ossia memorizzare i nodi in ordine crescente)
// questo mi permette di garantire che undirected_edge(x,y) == undirected_edge(y,x)
// infatti from e to non indicano propriamente partenza e arrivo, perchè si stanno trattando grafi non orientati.
	undirected_edge (T a, T b) {
		if (a <= b) { 
			nodo1 = a; nodo2 = b;	
		}
		else { 
			nodo1 = b, nodo2 = a;
		}
	}
	
	T from() const {return nodo1; }
	T to() const {return nodo2; }
	
	// confronto tra archi
	bool operator< (const undirected_edge& other) const {
		if (nodo1 != other.nodo1) {
			return nodo1 < other.nodo1;
		}
		else { 
			return nodo2 < other.nodo2;
		}
	}
	
	bool operator== (const undirected_edge& other) const {
		return nodo1 == other.nodo1 && nodo2 == other.nodo2;
	}
};

template <typename T>
std::ostream&
operator<<(std::ostream&os, const undirected_edge<T>& e) {
	os  << "(" << e.from() << "," << e.to() << ")";
	return os;
}

// -------------------------------------------------------------------------

// undirected_graph --> rappresento un grafo

template<typename T>
class undirected_graph {
	
	// si tengono tutti gli archi, senza duplicati e in ordine
	// ( è il set garantisce unicità e ordine )
	std::set<undirected_edge<T>> archi;
	
	// per ogni nodo tengo la lista dei suoi vicini
	std::map<T, std::list<T>> vicini;
	
	// si tengono gli archi nell'ordine in cui sono stati inseriti, per poterli numerare
	std::vector<undirected_edge<T>> indici;
	
public:
	// costruttore di default
	undirected_graph() = default; //=={}
	// set, map, vector si inizializzano già da soli come contenitori vuoti
	
	// costruttore di copia --> servirà per operator-
	undirected_graph(const undirected_graph&) = default;
	
	// metodo add_edge() che permetta di aggiungere un arco al grafo
	void add_edge(T nodo1, T nodo2) {
		undirected_edge<T> nuovo_arco(nodo1, nodo2);
		
		if (archi.count(nuovo_arco)) return; //se l'arco è già presente non fa nulla
		
		archi.insert(nuovo_arco); //inserisco l'arco nel set
		indici.push_back(nuovo_arco); //aggiungo l'arco in fondo al vettore, così da tenere traccia dell'ordine di inserimento
		
		vicini[nuovo_arco.from()].push_back(nuovo_arco.to()); // nella lista dei vicini di nodo1 aggiungo nodo 2
		vicini[nuovo_arco.to()].push_back(nuovo_arco.from()); // viceversa; lo faccio in entrambe le direzioni eprchè l'arco non ha direzione
	}
	// *l'operazione add_node() non è stata menzionata*
	// In un grafo non diretto i nodi non esistono da soli, esistono solo in relazione agli archi.
	// Nel nostro caso, un nodo viene aggiunyo automaticamente ogni volta che si aggiunge un arco che lo coinvolge.
	// Se si avesse add_node() si potrebbero creare nodi isolati, cioè nodi senza archi
	
	// metodo neighours() che, dato un nodo, restituisce i suoi vicini
	std::optional<std::list<T>> neighbours(T nodo) const {
		auto it = vicini.find(nodo); // it è un iteratore
		if (it == vicini.end()) //non punta a nessuna riga reale --> non trova niente
			return std::nullopt;
		return it-> second; 
		// first e second nomi fissi della libreria standard
		// first --> chiave 
		// second --> valore 
	}
	
	// metodo all_edges() che restituisce tutti gli archi
	const std::set<undirected_edge<T>>& all_edges() const {
		return archi;
	}
	
	// metodo all_nodes() che restituisce tutti i nodi 
	std::set<T> all_nodes() const {
		std::set<T> nodi;
		for (auto& [nodo, _] : vicini)
			nodi.insert(nodo);
		return nodi;
	}
	
	// metodo edge_number() che, dato un arco, ne restituisce la sua numerazione all'interno del grafo
	std::optional<int> edge_number(const undirected_edge<T>& arco) const {
		for (int i=0; i<(int)indici.size(); ++i) {
			if (indici[i] == arco) return i;
		}
		return std::nullopt;
	}
	
	// metodo edge_at() che, dato un numero d'arco, restituisce il corrispondente oggetto arco all'interno del grafo
	std::optional<undirected_edge<T>> edge_at(int indice) const {
		if (indice < 0 || indice >= (int)indici.size())
			return std::nullopt;
		return indici[indice];
	}
	
	// operatore operator-(), che permette di calcolare la differenza tra due grafi: dati g1 e g2, la differenza g1-g2 è data dagli archi presenti in g1 e non in g2 
	undirected_graph operator-(const undirected_graph& other) const {
		undirected_graph result;
		for (const auto& arco : archi) 
			if (!other.archi.count(arco))
				result.add_edge(arco.from(), arco.to());
		return result;
	}
};