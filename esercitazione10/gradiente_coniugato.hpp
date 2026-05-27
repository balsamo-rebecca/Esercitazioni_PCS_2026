#pragma once
#include <Eigen/Dense>
#include <Eigen/SVD>
#include <iostream>

// calcolo numero di condizionamento di una matrice A tramite SVD
// (rapporto tra il valore singolare massimo e quello minimo)
inline double condA(const Eigen::MatrixXd& A)
{
	Eigen::JacobiSVD<Eigen::MatrixXd> svd(A);
	Eigen::VectorXd singularValues = svd.singularValues();
	return singularValues.maxCoeff() / singularValues.minCoeff();
}

// struttura per raccogliere i risultati del metodo del gradiente coniugato
struct Risultati
{
	Eigen::VectorXd x; 				// soluzione calcolata
	unsigned int iterations;			// numero di iterazioni effettuate
	double residual_ratio; 			// norma residuo relativa finale (||r_k|| / ||r_0||)
};

// Parametri implementazione del metodo del gradiente coniugato per sistemi Ax=b
inline Risultati gradiente_coniugato(
	const Eigen::MatrixXd& A, 			// A		: matrice del sistema (simmetrica def positiva)
	const Eigen::VectorXd& b, 			// b 		: termine noto
	const Eigen::VectorXd& x0, 			// x0 		: vettore soluzione iniziale
	const double tol = 1.0e-12, 		// tol 		: tolleranza sul residuo relativo (criterio di arresto)
	const unsigned int it_max = 10000)	// it_max 	: numero iterazioni massime
{
	Eigen::VectorXd x = x0;
	Eigen::VectorXd res = b-A*x;			// r_0 = b - A*x_0
	Eigen::VectorXd p = res;				// p_0 = r_0 (prima direzione di discesa)
	
	const double res_norm_0 = res.norm();	// norma del residuo iniziale
	unsigned int it=0;
	
	while (it<it_max && res.norm() > tol * res_norm_0) {
		//Eigen::VectorXd Ap = A*p;
		
		// alpha_k = (p_k^T * r_k) / (p_k^T * A * p_k)
		const double alpha_k = ((p.transpose() * res)/(p.transpose() * A * p)).value();
		
		x = x + alpha_k * p;		// x_{k+1} = x_k + alpha_k * p_k
		res = b - A*x;				// r_{k+1} = b - A*x_{k+1}
		
		// beta_k = (p_k^T * A * r_{k+1}) / (p_k^T) * A * p_k)
		const double beta_k = ((p.transpose() * A * res) / (p.transpose() * A * p)).value();
		
		p = res - beta_k * p; // p_{k+1}=r_{k+1} - beta_k * p_k
		
		it++;
	}
	
	Risultati result;
	result.x 				=x;
	result.iterations		=it;
	result.residual_ratio	=res.norm() / res_norm_0;
	return result;
}