#include <iostream>
#include <Eigen/Dense>
#include "gradiente_coniugato.hpp"

// per verificare che l'algoritmo effettivamente funzioni, lo testo in 3 situazioni diverse:
// 1. matrice casuale piccola 
// 2. matrice casuale grande 
// 3. matrice d'identità --> con A=I il gradiente_coniugato deve convergere in 1 sola iterazione

// TEST 1 --> matrice dim piccole
bool test_1() {
	const double tol_zero = 1.0e-15;
	const unsigned int n = 3;
	
	// costruzione matrice A simm def pos: A = B^T*B
	Eigen::MatrixXd B = Eigen::MatrixXd::Random(n,n);
	if (std::abs(B.determinant())<tol_zero) {
		std::cerr << "Test 1 fallito" << std::endl;
		return false;
	}
	Eigen::MatrixXd A=B.transpose()*B;
	
	Eigen::VectorXd x_ex = Eigen::VectorXd::Ones(n); //soluzione esatta: [1,1,1]
	Eigen::VectorXd b = A*x_ex;
	Eigen::VectorXd x0 = Eigen::VectorXd::Zero(n); // partenza da zero
	
	std::cout.precision(2);
	std::cout << std::scientific << "Numero di condizionamento: " << condA(A) << std::endl;
	
	auto result = gradiente_coniugato(A,b,x0);
	
	double err_rel;
	if (x_ex.norm() == 0) {
		err_rel = (result.x - x_ex).norm();
	} else {
		err_rel = (result.x - x_ex).norm() / x_ex.norm();
	}
	
	std::cout.precision(4);
	std::cout << std::scientific;
	std::cout << "Iterazioni: " << result.iterations << " / " << 10000 << std::endl;
	std::cout << "Residuo rel: " << result.residual_ratio << " (tol = 1e-12)" << std::endl;
	std::cout << "Errore rel: " << err_rel << std::endl;
	std::cout << "Soluzione calcolata:\n" << result.x << std::endl;
	
	const bool passed = (err_rel < 1.0e-10);
	std::cout << "Risultato: " << (passed ? "PASSED" : "FAILED") << std::endl;
	return passed;
}

// TEST 2 --> matrice dim grandi
bool test_2() {
	const double tol_zero = 1.0e-15;
	const unsigned int n = 50;
	
	// costruzione matrice A simm def pos: A = B^T*B
	Eigen::MatrixXd B = Eigen::MatrixXd::Random(n,n);
	if (std::abs(B.determinant())<tol_zero) { 
		std::cerr << "Test 2 fallito" << std::endl;
		return false;
	}
	Eigen::MatrixXd A=B.transpose()*B;
	
	Eigen::VectorXd x_ex = Eigen::VectorXd::Ones(n); //soluzione esatta: [1,1,1]
	Eigen::VectorXd b = A * x_ex;
	Eigen::VectorXd x0 = Eigen::VectorXd::Zero(n); // partenza da zero
	
	std::cout.precision(2);
	std::cout << std::scientific << "Numero di condizionamento: " << condA(A) << std::endl;
	
	auto result = gradiente_coniugato(A,b,x0);
	
	double err_rel; 
	if (x_ex.norm() == 0) {
		err_rel = (result.x - x_ex).norm();
	} else {
		err_rel = (result.x - x_ex).norm() / x_ex.norm();
	}
	
	std::cout.precision(4);
	std::cout << std::scientific;
	std::cout << "Iterazioni: " << result.iterations << " / " << 10000 << std::endl;
	std::cout << "Residuo rel: " << result.residual_ratio << " (tol = 1e-12)" << std::endl;
	std::cout << "Errore rel: " << err_rel << std::endl;
	std::cout << "Soluzione calcolata:\n" << result.x << std::endl;
	
	const bool passed = (err_rel < 1.0e-8);
	std::cout << "Risultato: " << (passed ? "PASSED" : "FAILED") << std::endl;
	return passed;
}

// TEST 3 --> matrice identità
bool test_3() {
	const unsigned int n=6;
	Eigen::MatrixXd A = Eigen::MatrixXd::Identity(n,n);
	Eigen::VectorXd x_ex = Eigen::VectorXd::Random(n);
	Eigen::VectorXd b = x_ex; // A=I --> b=x_ex
	Eigen::VectorXd x0 = Eigen::VectorXd::Zero(n);
	
	std::cout.precision(2);
	std::cout << std::scientific << "Numero di condizionamento: " << condA(A) << std::endl;
	
	auto result=gradiente_coniugato(A,b,x0);
	const double err_rel = (result.x -x_ex).norm() / x_ex.norm();
	
	//Con A=I il gradiente_coniugato converge in esattamente 1 iterazione
	const bool passed = (err_rel < 1.0e-12 && result.iterations == 1);
	std::cout << "Risultato: " << (passed ? "PASSED" : "FAILED") << std::endl;
	return passed;
}

// possiamo dire che l'algoritmo funziona se tutti i test riportano esito positivo

int main() {
	bool all_passed = true;
	all_passed &=test_1();
	all_passed &=test_2();
	all_passed &=test_3();
	
	if (all_passed) {
		std::cout << "Tutti i test sono stati superati con successo." << std::endl;
	} else {
		std::cout << "Uno o più test hanno fallito" << std::endl;
	}
	
	return all_passed ? 0:1;
}