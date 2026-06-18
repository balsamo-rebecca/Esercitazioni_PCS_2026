#pragma once 
#include <optional>
#include <map>
#include <set>
#include <list>
#include <stdexcept>
#include <vector>
#include <ostream>
#include <algorithm>
#include <fstream>
#include <queue>
#include <stack>
#include <limits>

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

//----------------------------------------------------------------------

// Contenitore con politica FIFO (coda) --> usato per BFS
template<typename T>
class fifo { // First In - First Out
	std::queue<T> q;
public:
	void put(T val) {  
		q.push(val); // inserisco un elemento in fondo alla coda
	}
	T get() {
		T v=q.front(); // prendo un elemento che si trova in cima alla coda
		q.pop(); // lo rimuovo dalla struttura
		return v; // restituisco valore preso e rimosso
	}
	bool empty() const { // valore booleano per dire se la coda è vuota o meno
		return q.empty();
	}
};

// Contenitore con politica LIFO (stack) --> usato per DFS
template<typename T> 
class lifo { // Last In - First Out
	std::stack<T> s;
public:
	void put(T val) {
		s.push(val); // inserisco un elemento in cima alla pila
	}
	T get() {
		T v=s.top(); // prendo l'elemento che si trova in cima alla pila
		s.pop(); // lo rimuovo
		return v; // lo restituisco 
	}
	bool empty() const { // la pila è vuota?
		return s.empty();
	}
};

template<typename T, typename Container>
undirected_graph<T> graph_visit(const undirected_graph<T>& g, T sorgente, Container contenitore) {
// ricevo un grafo g per riferimento costante, per non copiarlo e non modificarlo
// nodo sorgente da cui far partire la visita
// il tipo di contenitore che passo come argomento stabilirà se la visita si comporterà come
// BFS usando la coda FIFO  --> esplora il vicinato			   oppure come
// DFS usando lo stack LIFO --> profondità
	
	undirected_graph<T> grafo; 
	// grafo di output inizialmente vuoto, man mano che scopriamo nuovi nodi, aggiungiamo archi
	std::set<T> visitati; 
	// insieme set che tiene traccia dei nodi già scoperti
	
	contenitore.put(sorgente);
	visitati.insert(sorgente);
	// inizializzo la visita e inserisco il nodo di partenza dentro il contenitore marcandolo come già "visitato"
	
	while (!contenitore.empty()) { // finchè ci sono odi da visitare ...
		T corrente = contenitore.get();
		// estraggo il prossimo nodo da visitare
		// se il contenitore è FIFO --> prenderà il più vecchio (BFS)
		// se il contenitore è LIFO --> prenderà l'ultimo inserito (DFS)
		
		auto vicini_opt = g.neighbours(corrente);
		if(!vicini_opt) continue;
		
		// copio i vicini in un vettore e li ordino per renderli indipendenti dall'ordine di inserimento degli archi nel file 
		std::vector<T> vicini_ordinati(vicini_opt->begin(),vicini_opt->end());
		std::sort(vicini_ordinati.begin(),vicini_ordinati.end());
		
		for (T vicino: vicini_ordinati) {
			if(!visitati.count(vicino)) { 
			//controllo che il vicino in esame non sia già stato visitato
			//count restituisce 1 se l'elemento esiste nel set, 0 altrimenti
				visitati.insert(vicino);
				contenitore.put(vicino);
				grafo.add_edge(corrente,vicino);
			}
		}
	}
	
	return grafo;
}

// === DFS ricorsiva ===
template<typename T>
void dfs_ricorsiva(const undirected_graph<T>& g, T corrente, std::set<T>& visitati, undirected_graph<T>& albero) {
	visitati.insert(corrente);
	
	auto vicini_opt = g.neighbours(corrente);
	if (!vicini_opt) return;
	
	std::vector<T> vicini_ordinati(vicini_opt->begin(), vicini_opt->end());
	std::sort(vicini_ordinati.begin(),vicini_ordinati.end());
	
	for (T vicino : vicini_ordinati) {
		if (!visitati.count(vicino)) {
			albero.add_edge(corrente,vicino);
			dfs_ricorsiva(g,vicino,visitati,albero);
		}
	}
}

// === funzione ===
template<typename T>
undirected_graph<T> recursive_dfs(const undirected_graph<T>& g, T sorgente) {
	undirected_graph<T> albero;
	std::set<T> visitati;
	dfs_ricorsiva(g, sorgente, visitati, albero);
	return albero;
}

// === dijkstra ===
template<typename T>
undirected_graph<T> dijkstra(const undirected_graph<T>& g, T sorgente) {
	
	// grafo che conterrà l'albero dei cammini minimi risultatnte
	undirected_graph<T> albero_cammini_min;
	
	// inizializzazione delle distanze
	const double INF=std::numeric_limits<double>::infinity(); // definisco una costante che rappresenta il valore matematico di infinito
	//alternativamente pongo un valore arbitrariamente grande --> const double INF=99999999.0 
	std::map<T, double> dist; 
	// creo una mappa per associare a ogni nodo la sua distanza provvisoria dalla sorgente
	for (T nodo : g.all_nodes()) {
		dist[nodo] = INF; //inizalizzo la distanza di tutti i nodi a infinito --> nodo non ancora raggiungibile
	}
	dist[sorgente]=0.0; //distanza del nodo sorgente da se stesso
	
	// mappa che tiene traccia del predecessore ottimale di ogni nodo
	std::map<T,T> predecessore;
	
	// per farlo funzionare in modo efficiente esamino prima i nodi più vicini: coda a priorità
	using coppia = std::pair<double,T>;
	using min_queue = std::priority_queue<coppia, std::vector<coppia>, std::greater<coppia>>;
	min_queue pq;
	pq.push({0.0, sorgente}); //primo elemento inserito nella coda: nodo sorgente a distanza zero
	
	std::set<T> finalizzati; // tengo traccia dei nodi per cui abbiamo già trovato il cammino minimo
	
	while (!pq.empty()) {
		auto[d,u] =pq.top();
		// estraggo la coppia in cima alla coda: u = nodo corrente; d = distanza 
		pq.pop();
		
		if(finalizzati.count(u)) {
			continue;
		}
		finalizzati.insert(u);
		
		// se il nodo corrente ha un predecessore nella mappa, significa che 
		// l'arco che lo collega al cammini minimo è definitivo.
		// --> lo inseriamo nell'albero
		if (predecessore.count(u)) {
			albero_cammini_min.add_edge(predecessore[u],u);
		}
				
		auto vicini_opt = g.neighbours(u);
		if(!vicini_opt) continue;
		
		// ordino i vicini
		std::vector<T> vicini_ordinati(vicini_opt->begin(),vicini_opt->end());
		std::sort(vicini_ordinati.begin(),vicini_ordinati.end());
		
		for(T v: vicini_ordinati) {
			// fissdimso il peso di ogni arco a 1.0
			double peso=1.0;

			double nuova_dist = dist[u] + peso; 
			if (nuova_dist < dist[v]) {
				dist[v] = nuova_dist;
				predecessore[v]=u;
				pq.push({nuova_dist,v});
			}
		}
	}
	
	return albero_cammini_min;
}


// === funzione per esportazione grafo in formato DOT per Graphviz
template<typename T>
void esporta_dot(const undirected_graph<T>& g, const std::string& nome_file, const std::string& titolo="G") {
	std::ofstream f(nome_file);
	f << "graph " << titolo << " {\n";
	for (const auto& arco: g.all_edges()) {
		f << " \"" << arco.from() << "\" -- \"" << arco.to() << "\";\n";
	}
	f << "}\n";
}


