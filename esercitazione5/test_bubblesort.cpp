#include "algoritmo_ordinamento.hpp"
#include "verifica_ordine.hpp"
#include "timecounter.h"
#include "randfiller.h"
#include <iostream>
#include <ostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>

int main() {
	
	randfiller rf;
	srand(time(NULL));
	
	timecounter tc;
	double sec = 0;
	
	for (int k=0; k<100; k++) {
		
		int n=(rand()%20)+1;
		std::cout << "la lunghezza del vettore " << k+1 << " è di " << n << " elementi" << "\n";	
	
		std::vector<int> vec(n);
		rf.fill(vec,-1000,1000);
		
		std::cout << "Vettore originale:";
		for (int x : vec) {
			std::cout << x << " ";
		}
		std::cout << std::endl;
		
		tc.tic();
		bubble_sort(vec);
		sec += tc.toc();
		std::cout << "Vettore ordinato:";
		for (int x : vec) {
			std::cout << x << " ";
		}
		std::cout << std::endl;
		std::cout << "\n";
		
		if (!is_sorted(vec)) {
			std::cout << "Errore" << "\n";
			return EXIT_FAILURE;
		}
	}
	
    /* sleep for some time */
    std::this_thread::sleep_for( std::chrono::milliseconds(1234) );
    
    std::cout << "Tempo impiegato: " << sec << " secondi\n";
	
	// ordinamento vettore con stringhe
	std::vector<std::string> parole =  {
		"xo", "attention-please", "knife", "flashover", "fever", "fate",
		"moonstruck", "noDoubt", "helium", "royalty", "daydream", "paranormal", "outside"
	};
	
	std::cout << "Vettore con stringhe originale:";
	for (const std::string x : parole) {
		std::cout << x << ", ";
	}
	std::cout << std::endl << '\n';
	
	bubble_sort(parole);
	std::cout << "Vettore con stringhe ordinate:";
	for (const std::string x : parole) {
		std::cout << x << ", ";
	}
	std::cout << std::endl;
	std::cout << "\n";
	
	if (!is_sorted(parole)) {
		std::cout << "Errore" << "\n";
		return EXIT_FAILURE;
	}
  
	return EXIT_SUCCESS;
}