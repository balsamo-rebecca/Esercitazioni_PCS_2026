#include "algoritmi_ordinamento.hpp"
#include "verifica_ordine.hpp"
#include "timecounter.h"
#include "randfiller.h"
#include <iostream>
#include <ostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <algorithm>

int main() {
	
	//creo e apro file 
	std::ofstream outfileALG_bubble("dati_algBubble.txt"); 
	std::ofstream outfileALG_insertion("dati_algInsertion.txt"); 
	std::ofstream outfileALG_selection("dati_algSelection.txt"); 
	std::ofstream outfileFUNZ("dati_funz.txt");
	
	randfiller rf;
	srand(time(NULL));
	
	// inizializzazioni per calcolo tempi
	timecounter tc;
	timecounter tc_TOT;
	double tempo_bubble = 0;
	double tTOT_buble = 0;
	double tempo_insertion = 0;
	double tTOT_insertion = 0;
	double tempo_selection = 0;
	double tTOT_selection = 0;
	double tempo_std = 0;
	double tTOT_std = 0;

    std::this_thread::sleep_for( std::chrono::milliseconds(1234) );
	
	for (int i=4; i<=8192; i=i*2) { //impongo lunghezza crescente dei vettori
		std::cout << "la lunghezza dei vettori è di " << i << " elementi" << "\n";
		 
		for (int k=0; k<100; k++){ //impongo il numero di interazioni per ogni serie di lunghezza
	
			std::vector<int> vec;
			vec.resize(i);
			rf.fill(vec,-1000,1000);
			
			std::vector<int> vec_insertion = vec;
			std::vector<int> vec_selection = vec;
			std::vector<int> vec_copia = vec; 
			// se non facessi una copia di vec, quando implemento std::sort(vec) o gli altri algoritmi avrei un vettore già ordinato dal bubblesort o da un metodo precedentemente usato
			
			std::cout << "vettore numero "<< k+1 << "." << "\n";
			std::cout << "Vettore originale:";
			for (int x : vec) {
				std::cout << x << " ";
			}
			std::cout << std::endl;
			
			// BUBBLE SORT
			tc.tic();
			tc_TOT.tic();
			bubble_sort(vec);
			tempo_bubble = tc.toc();
			tTOT_buble += tc_TOT.toc();
			if(outfileALG_bubble.is_open()) {
				outfileALG_bubble << tempo_bubble << "\n";
			};
			std::cout << "Vettore ordinato con algoritmo di ordinamento bubble sort:";
			for (int x : vec) {
				std::cout << x << " ";
			}
			std::cout << std::endl;
			std::cout << "Tempo impiegato con algoritmo di ordinamento bubble sort: " << tempo_bubble << " secondi\n";
			std::cout << "\n";
			
			// INSERTION SORT
			tc.tic();
			tc_TOT.tic();
			insertion_sort(vec_insertion);
			tempo_insertion = tc.toc();
			tTOT_insertion += tc_TOT.toc();
			if(outfileALG_insertion.is_open()) {
				outfileALG_insertion << tempo_insertion << "\n";
			};
			std::cout << "Vettore ordinato con algoritmo di ordinamento insertion sort:";
			for (int x : vec_insertion) {
				std::cout << x << " ";
			}
			std::cout << std::endl;
			std::cout << "Tempo impiegato con algoritmo di ordinamento insertion sort: " << tempo_insertion << " secondi\n";
			std::cout << "\n";
			
			// SELECTION SORT
			tc.tic();
			tc_TOT.tic();
			selection_sort(vec);
			tempo_selection = tc.toc();
			tTOT_selection += tc_TOT.toc();
			if(outfileALG_selection.is_open()) {
				outfileALG_selection << tempo_selection << "\n";
			};
			std::cout << "Vettore ordinato con algoritmo di ordinamento selection sort:";
			for (int x : vec_selection) {
				std::cout << x << " ";
			}
			std::cout << std::endl;
			std::cout << "Tempo impiegato con algoritmo di ordinamento selection sort: " << tempo_selection << " secondi\n";
			std::cout << "\n";
			
			// SORT
			tc.tic();
			tc_TOT.tic();
			std::sort (vec_copia.begin(), vec_copia.end());
			tempo_std = tc.toc();
			tTOT_std += tc_TOT.toc();
			if(outfileFUNZ.is_open()) {
				outfileFUNZ << tempo_std << "\n";
			};
			std::cout << "Vettore ordinato con la funzione di ordinamento fornita dalla libreria standard:";
			for (int y : vec_copia) {
				std::cout << y << " ";
			}
			std::cout << std::endl;
			std::cout << "Tempo impiegato con la funzione di ordinamento fornita dalla libreria standard: " << tempo_std << " secondi\n";
			std::cout << "\n";
			
			if (!is_sorted(vec) || !is_sorted(vec_copia)) {
				std::cout << "Errore" << "\n";
				return EXIT_FAILURE;
			}
			
			std::cout << "-----------------------" << "\n";
		}
		
	}
	
	std::cout <<"Tempo totale: " << tTOT_buble + tTOT_insertion + tTOT_selection + tTOT_std << "\n";
	
	return EXIT_SUCCESS;
}