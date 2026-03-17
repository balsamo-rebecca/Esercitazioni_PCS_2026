// per la realizzazione di questo programma è stato utilizzato l'aiuto dell'intelligienza artificiale (Gemini)//
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
	if (argc < 2) {
		return 1;
	}
	
	std::ifstream ifs(argv[1]);
	if (!ifs.is_open()) {
		return 1;
	}
	else {
		std::string citta;
		double t1, t2, t3, t4;
	
		while (ifs >> citta >> t1 >> t2 >> t3 >> t4) {
			double media = (t1 + t2 + t3 + t4) / 4.0;
			std::cout << citta << " " << media << "\n" ;
		}
	}
	
	return 0;
	}
	
	