# include <iostream>

int main()
{	// gli array sono memorizzati in memoria in modo contiguo
	double ad[4] = {0.0, 1.1, 2.2, 3.3}; 
	float af[8] = {0.0, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7}; 
	int ai[3] = {0, 1, 2};
	
	int x = 1;
	float y = 1.1;

	(&y)[1] = 0; //&y prende l'inidrizzo di memoria di y, mentre [1] dice di spostarsi avanti di un indirizzo (4 byte, dato da 1*sizeof(float)) 
				 // y rimane 1.1, mentre ciò che c'è scritto nello spazio di memoria successivo (x=1) viene sovrascritto con 0

	std::cout << x << "\n"; 		// stampa il valore di x, precedentemente sovrascritto con la linea di codice 12
	
	std::cout << &ad[2] << "\n"; 	// stampa l'indirizzo dell'elemento in posizione 2 di ad[], ossia di 2.2
	std::cout << &x << "\n";		// stampa l'indirizzo di x
	
									// tra i due indirizzi c'è una distanza di 64 byte, questo perché il compilatore non salva in memoria gli elementi
									// nello stesso ordine in cui vengono scritti nel codice 

	return 0;
}

// il comando "(&y)[1] = 0;" a linea 12, sovrascrive 0 al vecchio valore di x = 1 che vedo a linea 9 