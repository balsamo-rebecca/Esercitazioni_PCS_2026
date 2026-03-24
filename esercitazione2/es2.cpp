# include <iostream>
# include <cmath>

int main()
{
	static const int N = 10;
	double arr[N] = { 1.8 , -54 , 28.8 , 0.3 , 11.4 , 9.7 , 21.9 , 53 , -0.6, 18}; 
	
	// calcolo del minimo
	double a = arr[0];
	for (int i=1; i<N; i=i+1) {
		a = std::min(a,arr[i]);
	}
	
	// calcolo del massimo
	double b = arr[0];
	for (int i=1; i<N; i=i+1) {
		b = std::max(b,arr[i]);
	}
	
	// calcolo della media
	// step 1: somma di tutti gli elementi nell'array
	double c = arr[0]; 
	for (int i=1; i<N; i=i+1) {
		c = c + arr[i];
	}
	// step 2: divido per il numero totale di elementi 
	double media = c / N;
	
	// calcolo della deviazione standard --> sqrt((sum1 --> N) (xi - media)^2) / N)  
	// media è un dato già disponibile, xi è l'i-esimo elemento dell'array
	// sqrt (double num) 
	double d = 0;
	for (int i=0; i<N; i=i+1) {
		d = d + (arr[i] - media)*(arr[i] - media);
	}
	double argomento = (d / N);
	double dev_st = std::sqrt(argomento);
	
	std::cout << a << "\n";		
	std::cout << b << "\n";
	std::cout << media << "\n";
	std::cout << dev_st << "\n";
	
	return 0;
}