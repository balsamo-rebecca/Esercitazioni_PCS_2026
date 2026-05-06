#include "algoritmo_ordinamento.hpp"
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

// definisco una funzione da richiamare ad ogni metodo che mi generi il vettore da riordinare
// per non dover lavorare con copie di un solo vettore

void fill_vectors(vector<vector<int>> &vecs, int dim)
{
	randfiller rf;
	
	for (unsigned int i=0; i<vecs.size(); i++) {
		vecs[i].resize(dim);
		rf.fill(vecs[i], -1000,1000);
	}
}

int main() {
	// inizializzazioni per calcolo tempi
	srand(time(NULL));
	timecounter tc;
	
	// per il calcolo del tempo totale di ogni algoritmo
	double time_bubble=0;
	double time_insertion=0;
	double time_selection=0;
	double time_mergesort=0;
	double time_quicksort=0;
	double time_f=0;

	//creo e apro file per la raccolta dei tempi
	std::ofstream outfileALG_bubble("dati_algBubble.txt"); 
	std::ofstream outfileALG_insertion("dati_algInsertion.txt"); 
	std::ofstream outfileALG_selection("dati_algSelection.txt");
	std::ofstream outfileALG_mergesort("dati_algMergeSort.txt"); 
	std::ofstream outfileALG_quick("dati_algQuick.txt"); 
	std::ofstream outfileFUNZ("dati_funz.txt");
	
	for (int k=2; k<=1000; k=k+20)	{		    	
		int dim = k; 					//numero di dimensioni che voglio misurare
		int n_vettori = 100;			//numero di vettori per ogni dimensione
		// vettore di n_vettori vettori, ciascuno di lunghezza dim
		
		vector<vector<int>> vecs(n_vettori);
		
		std::cout <<"VETTORI DI LUNGHEZZA "<< k<< " \n";
		std::cout << std::endl;
		std::cout << "\n";
		
		// BUBBLE
		// prima di far partire il tempo richiamo la funzione precedentemente definita e mi genero il vettore che andrò a riordinare	fill_vectors(vecs,dim);
		fill_vectors(vecs,dim);
		
		std:: cout <<"vettore iniziale: \n";
		for (int i=0; i<n_vettori; i++) {
			for (int x : vecs[i]) {
				std::cout << x << " ";
			}
			std::cout << "\n";
		}
		std::cout << std::endl;
		std::cout << "\n";
		
		tc.tic();
		for (int j=0; j<n_vettori; j++) {
			bubble_sort(vecs[j]);
		}
		double time_b = tc.toc();
		
		std:: cout <<"vettore ordinato con bubble: \n";
		for (int i=0; i<n_vettori; i++) {
			for (int x : vecs[i]) {
				std::cout << x << " ";
			}
			std::cout << "\n";
		}
		std::cout << std::endl;
		std::cout << "\n";
		
		double media_bubble = time_b / n_vettori; // tempo medio impiegato per riordinare i 100 vettori nella singola iterata
		time_bubble = time_bubble + time_b; // tempo che viene incrementato ad ogni iterata
		// raccolgo i tempi medi per la realizzazione del grafico
		if (outfileALG_bubble.is_open()) {
			outfileALG_bubble << media_bubble << "\n";
		} else {std::cout << "Errore: file non aperto\n"; }
		
		// -----------------------------------------------------------------------------
		
		// INSERTION
		fill_vectors(vecs,dim);
		
		std:: cout <<"vettore iniziale: \n";
		for (int i=0; i<n_vettori; i++) {
			for (int x : vecs[i]) {
				std::cout << x << " ";
			}
			std::cout << "\n";
		}
		std::cout << std::endl;
		std::cout << "\n";
		
		tc.tic();
		for (int j=0; j<n_vettori; j++) {
			insertion_sort(vecs[j]);
		}
		double time_i = tc.toc();
		
		std:: cout <<"vettore ordinato con insertion: \n";
		for (int i=0; i<n_vettori; i++) {
			for (int x : vecs[i]) {
				std::cout << x << " ";
			}
			std::cout << "\n";
		}
		std::cout << std::endl;
		std::cout << "\n";
		
		double media_insertion = time_i / n_vettori;
		time_insertion = time_insertion + time_i;
		
		if (outfileALG_insertion.is_open()) {
			outfileALG_insertion << media_insertion << "\n";
		} else {std::cout << "Errore: file non aperto\n"; }
				
		// -----------------------------------------------------------------------------
		
		// SELECTION
		fill_vectors(vecs,dim);
		
		std:: cout <<"vettore iniziale: \n";
		for (int i=0; i<n_vettori; i++) {
			for (int x : vecs[i]) {
				std::cout << x << " ";
			}
			std::cout << "\n";
		}
		std::cout << std::endl;
		std::cout << "\n";
		
		tc.tic();
		for (int j=0; j<n_vettori; j++) {
			selection_sort(vecs[j]);
		}
		double time_sel = tc.toc();
		
		std:: cout <<"vettore ordinato con selection: \n";
		for (int i=0; i<n_vettori; i++) {
			for (int x : vecs[i]) {
				std::cout << x << " ";
			}
			std::cout << "\n";
		}
		std::cout << std::endl;
		std::cout << "\n";
		
		double media_selection = time_sel / n_vettori;
		time_selection = time_selection + time_sel;
		
		if (outfileALG_selection.is_open()) {
			outfileALG_selection << media_selection << "\n";
		} else {std::cout << "Errore: file non aperto\n"; }
		
		// -----------------------------------------------------------------------------
		
		// MERGE_SORT
		fill_vectors(vecs,dim);
		
		std:: cout <<"vettore iniziale: \n";
		for (int i=0; i<n_vettori; i++) {
			for (int x : vecs[i]) {
				std::cout << x << " ";
			}
			std::cout << "\n";
		}
		std::cout << std::endl;
		std::cout << "\n";
		
		tc.tic();
		for (int j=0; j<n_vettori; j++) {
			merge_sort(vecs[j],0,(int)vecs[j].size()-1);
		}
		double time_m = tc.toc();
		
		std:: cout <<"vettore ordinato con mergesort: \n";
		for (int i=0; i<n_vettori; i++) {
			for (int x : vecs[i]) {
				std::cout << x << " ";
			}
			std::cout << "\n";
		}
		std::cout << std::endl;
		std::cout << "\n";
		
		double media_mergeSort = time_m / n_vettori;
		time_mergesort = time_mergesort + time_m;
		
		if (outfileALG_mergesort.is_open()) {
			outfileALG_mergesort << media_mergeSort << "\n";
		} else {std::cout << "Errore: file non aperto\n"; }
		
		// -----------------------------------------------------------------------------
		
		// QUICKSORT
		fill_vectors(vecs,dim);
		
		std:: cout <<"vettore iniziale: \n";
		for (int i=0; i<n_vettori; i++) {
			for (int x : vecs[i]) {
				std::cout << x << " ";
			}
			std::cout << "\n";
		}
		std::cout << std::endl;
		std::cout << "\n";
		
		tc.tic();
		for (int j=0; j<n_vettori; j++) {
			quicksort(vecs[j],0,(int)vecs[j].size()-1);
		}
		double time_q = tc.toc();
		
		std:: cout <<"vettore ordinato con quicksort: \n";
		for (int i=0; i<n_vettori; i++) {
			for (int x : vecs[i]) {
				std::cout << x << " ";
			}
			std::cout << "\n";
		}
		std::cout << std::endl;
		std::cout << "\n";
		
		double media_quick = time_q / n_vettori;
		time_quicksort = time_quicksort + time_q;
		
		if (outfileALG_quick.is_open()) {
			outfileALG_quick << media_quick << "\n";
		} else {std::cout << "Errore: file non aperto\n"; }
		
		// -----------------------------------------------------------------------------
		
		// SORT
		fill_vectors(vecs,dim);
		
		std:: cout <<"vettore iniziale: \n";
		for (int i=0; i<n_vettori; i++) {
			for (int x : vecs[i]) {
				std::cout << x << " ";
			}
			std::cout << "\n";
		}
		std::cout << std::endl;
		std::cout << "\n";
		
		tc.tic();		
		for (int j=0; j<n_vettori; j++) {
			std::sort(vecs[j].begin(), vecs[j].end());
		}
		double time_sort = tc.toc();
		
		std:: cout <<"vettore ordinato con sort: \n";
		for (int i=0; i<n_vettori; i++) {
			for (int x : vecs[i]) {
				std::cout << x << " ";
			}
			std::cout << "\n";
		}
		std::cout << std::endl;
		std::cout << "\n";
		
		double media_std = time_sort / n_vettori;
		time_f = time_f + time_sort;
		
		if (outfileFUNZ.is_open()) {
			outfileFUNZ << media_std << "\n";
		} else {std::cout << "Errore: file non aperto\n"; }
		
		std::cout <<" ----------------------------------------------- \n";

	}
// ---------------------------------------------------------------------------------
	
	//vettore con stringhe per verificare funzionamento degli algoritmi
	std::vector<string> parole =  {
	"body", "hooligan", "aliens", "FYA", "2", "no", "sun", "wonder",
	"merry", "normal", "animals", "swim", "know", "night", "please"
	};
	// creo copie per non avere un vettore già ordinamto negli algoritmi a seguire
	std::vector<string> parole_insertion = parole;
	std::vector<string> parole_selection = parole;
	std::vector<string> parole_mergeS = parole; 
	std::vector<string> parole_quick = parole; 
	std::vector<string> parole_copia = parole;
	
	// verifica del funzionamento di bubble con il vettore di stringhe
	bubble_sort(parole);
	std:: cout <<"riordino parole con bubble:\n";
	for (string x : parole) {
		std::cout << x << " ";
	}
	std::cout << std::endl;
	std::cout << "\n";
	
	// verifica del funzionamento di insertion con il vettore di stringhe
	insertion_sort(parole_insertion);
	std:: cout <<"riordino parole con insertion:\n";
	for (string x : parole_insertion) {
		std::cout << x << " ";
	}
	std::cout << std::endl;
	std::cout << "\n";
	
	// verifica del funzionamento di selection con il vettore di stringhe
	selection_sort(parole_selection);
	std:: cout <<"riordino parole con selection:\n";
	for (string x : parole_selection) {
		std::cout << x << " ";
	}
	std::cout << std::endl;
	std::cout << "\n";
	
	// verifica del funzionamento di merge_sort con il vettore di stringhe
	merge_sort(parole_mergeS, 0, (int)parole_mergeS.size()-1);
	std::cout << "riordino parole con merge-sort:\n";
	for (string x : parole_mergeS) {
		std::cout << x << " ";
	}
	std::cout << std::endl;
	std::cout << "\n";
	
	// verifica del funzionamento di quick_sort con il vettore di stringhe
	quicksort(parole_quick, 0, parole_quick.size()-1);
	std:: cout <<"riordino parole con quick:\n";
	for (string x : parole_quick) {
		std::cout << x << " ";
	}
	std::cout << std::endl;
	std::cout << "\n";
	
	// verifica del funzionamento di std::sort con il vettore di stringhe
	std::sort(parole_copia.begin(), parole_copia.end());
	std:: cout <<"riordino parole con sort:\n";
	for (string x : parole_copia) {
		std::cout << x << " ";
	}
	std::cout << std::endl;
	std::cout << "\n";

	std::this_thread::sleep_for( std::chrono::milliseconds(1234));
	
	std::cout << "Tutti i vettori sono stati ordinati correttamente\n tempi: " << time_bubble <<", " << time_insertion<<", "<< time_selection<<", "<< time_mergesort<<", "<< time_quicksort<<", "<< time_f<< "\n";
	return EXIT_SUCCESS;

}