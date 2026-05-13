#include <iostream>
#include <ostream>
#include "undirected.hpp"

int main() {
	std::cout << "Test di undirected_edge \n";
	
	undirected_edge<int> arco1(1,3);
	undirected_edge<int> arco2(3,1); //stesso arco, nodi invertiti
	undirected_edge<std::string> arco3("farfalla","aereo"); //stringhe ai nodi
	undirected_edge<int> arco4(5,2);
	undirected_edge<int> arco5 (7,-4);
	undirected_edge<std::string> arco6("spotify", "iTunes");
	undirected_edge<std::string> arco7("iTunes", "spotify");
	undirected_edge<int> arco8(1,0);
	undirected_edge<int> arco9(5,-8);
	
	// i nodi vengono normalizzati correttamente?
	std::cout << "Test corretta normalizzazione \n";
	std::cout<< "(stessi nodi, ordine invertito) arco1 == arco2 ?   "<< arco1 << "=" << arco2 << " \n";
	std::cout<< "nodi type string " << arco3 <<"\n";
	std::cout<< "(normalizzazione, nodi in ordine crescente) arco4 = "<< arco4 << "\n";
	
	std::cout << std::endl;
	
	// confronto tra archi --> operator<
	std::cout << "Test dell'operator< --> confronto tra archi \n";
	std::cout<< "arco8 < arco1 --> " << (arco8 < arco1 ? "true":"false") << "\n"; //expected arco8<arco1 --> true
	std::cout<< "arco < arco9 --> " << (arco4 < arco9 ? "true":"false") << "\n"; //expected arco9<arco4 --> false
	std::cout<< "arco3 < arco7 --> " << (arco3 < arco7 ? "true":"false") << "\n"; //expected arco7<arco3 --> true
	
	std::cout << std::endl;
	
	// confronto tra archi --> operator==
	std::cout << "Test dell'opertaro== --> uguaglianza tra archi \n";
	std::cout<< "arco6==arco7? " << (arco6==arco7 ? "true":"false") << "\n"; //expected TRUE
	std::cout<< "arco1==arco2? " << (arco1==arco2 ? "true":"false") << "\n"; //expected TRUE
	std::cout<< "arco3==arco7? " << (arco3==arco7 ? "true":"false") << "\n"; //expected FALSE
	
	std::cout << std::endl;
	
	// stampa dell'arco --> operator<<
	std::cout << "check sulla stampa \n";
	std::cout<< arco6 << " " << arco7 << " " << arco8 << "\n";
		
	std::cout << std::endl;
	
	//------------------------------------------------------------------------------------------------------------
	
	//std::cout << "Test di undirected_graph \n";
	std::cout << "Test di undirected_graph \n";
	undirected_graph<int> g1;
	undirected_graph<std::string> g_string1;

	// aggiungere un arco al grafo
	g1.add_edge(1,2);
	g1.add_edge(7,10);
	g1.add_edge(-3,-2);
	g1.add_edge(9,-1);
	g1.add_edge(0,1);
	g1.add_edge(32,9);
	g1.add_edge(32,9); //arco ripetuto (dovrebbe essere ignorato)
	g1.add_edge(-2,-3); // anche questo dovrebbe essere ignorato
	
	g_string1.add_edge("tnt","redred");
	g_string1.add_edge("acai","wassup");
	g_string1.add_edge("wassup","acai"); //arco ripetuto (dovrebbe essere ignorato)
	g_string1.add_edge("lips","crew");
	g_string1.add_edge("acai","tnt");
	
	std::cout << std::endl;
	
	// vicini di un nodo
	std::cout << "Dato un nodo, elenco dei suoi vicini \n";
	int nodo_test = 9;
	std::cout << "Vicini di " << nodo_test << ": ";
	auto vicini = g1.neighbours(nodo_test);
	if (vicini) { //se il nodo è stato trovato e la lista dei vicini è disponibile...
		for (int nodo_vicino : *vicini) {
			std::cout << nodo_vicino << " ";
		}
	}
	else {
			std::cout << "nodo non trovato";
	}	//mi aspetto : -1 32
	
	std::cout << "\n",
	std::cout << std::endl;
	
	std::string nodo_stringa_test = "acai";
	std::cout << "Vicini di " << nodo_stringa_test << ": ";
	auto vicini_stringa = g_string1.neighbours(nodo_stringa_test);
	if (vicini_stringa) { //se il nodo è stato trovato e la lista dei vicini è disponibile...
		for (std::string nodo_stringa_test : *vicini_stringa) {
			std::cout << nodo_stringa_test << " ";
		}
	}
	else {
			std::cout << "nodo non trovato";
	} //mi aspetto : tnt wassup
	
	std::cout << "\n",
	std::cout << std::endl;
	
	// elenco di tutti gli archi
	std::cout << "Elenco degli archi \n";
	for (const auto& arco:g1.all_edges()) {
		std::cout << arco << " ";
	}
	std::cout << "\n";// Ci aspettiamo: (-3,-2) (-1,9) (0,1) (1,2) (7,10) (9,32)
	
	std::cout << std::endl;
	
	for (const auto& arco:g_string1.all_edges()) {
		std::cout << arco << " ";
	}
	std::cout << "\n";// Ci aspettiamo: (acai,wassup) (acai,tnt) (crew,lips) (redred,tnt)
	
	// elenco di tutti i nodi
	std::cout << "Elenco dei nodi \n";
	for (int nodo : g1.all_nodes()) {
		std::cout << nodo << " ";
	} // ci aspettiamo: -3 -2 -1 0 1 2 7 9 10 32
	
	std::cout << std::endl;

	for (const std::string& nodo : g_string1.all_nodes()) {
		std::cout << nodo << " ";
	} // ci aspettiamo: acai crew lips redred tnt wassup
	
	std::cout << std::endl;
	
	// numerazione di un arco nel grafo e viceversa: dato il numero di un arco nel grafo, arco corrispondente
	std::cout << "Dato un arco, viene restituita la sua numerazione all'interno del grafo? E viceversa? \n";
	undirected_edge<int> cerca(9,32);
	auto num=g1.edge_number(cerca);
	if (num) {
		std::cout << "L'arco" << cerca << " ha indice: " << *num << "\n";
	}
	else {
		std::cout << "Arco non trovato nel grafo\n";
	}
	
	int indice_test=4;
	auto arco_trovato=g1.edge_at(indice_test);
	if (arco_trovato) {
		std::cout << "L'arco trovato a indice " << indice_test << " è " << *arco_trovato << "\n";
	}
	else {
		std::cout << "Indice " << indice_test << " fuori dai limiti\n";		
	}

	std::cout << std::endl;
	
	std::cout << "Dato un arco con stringhe, viene restituita la sua numerazione all'interno del grafo? E viceversa?\n";
	undirected_edge<std::string> cerca_s("crew","lips");
	auto num_stringa=g_string1.edge_number(cerca_s);
	if (num_stringa) {
		std::cout << "L'arco " << cerca_s << " ha indice: " << *num_stringa << "\n";
	}
	else {
		std::cout << "Arco non trovato nel grafo\n";	
	}
	
	int indice_test_s=3;
	auto arco_trovato_s=g1.edge_at(indice_test_s);
	if (arco_trovato_s) {
		std::cout << "L'arco con stringhe trovato a indice " << indice_test_s << " è " << *arco_trovato_s << "\n";
	}
	else {
		std::cout << "Indice " << indice_test_s << " fuori dai limiti\n";		
	}
	
	std::cout << std::endl;
	
	// differenza tra grafi
	undirected_graph<int> g2;
	g2.add_edge(1,2); //arco comune a g1
	g2.add_edge(7,10); //arco comune a g1
	g2.add_edge(-17,-2); //arco presente solo in g2
	
	undirected_graph<std::string> g_string2;
	g_string2.add_edge("lips","crew"); // in comune con g_string1
	g_string2.add_edge("acai","tnt"); // in comune con g_string1
	g_string2.add_edge("tnt","acai"); //verrà ignorato
	g_string2.add_edge("enhypen","cortis"); //solo di g_string2

	std::cout << "Differenza g1-g2: elenco archi presenti in g1 e non in g2 \n";
	undirected_graph<int> diff = g1 - g2;
	for (const auto& arco:diff.all_edges()) {
		std::cout << arco << " ";
	}
	std::cout << "\n";// Ci aspettiamo: (-3,-2),(-1,9),(0,0),(9,32) 
	
	std::cout << std::endl;
	
	std::cout << "Differenza g_string1-g_string2: \n";
	undirected_graph<std::string> diff_string = g_string1 - g_string2;
	for (const auto& arco:diff_string.all_edges()) {
		std::cout << arco << " ";
	}
	std::cout << "\n";// Ci aspettiamo: ("acai","wassup"),("tnt","redred")
	
};