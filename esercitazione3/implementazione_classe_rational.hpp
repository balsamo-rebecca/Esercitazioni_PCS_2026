#include <concepts>
#include <iostream>
#include <numeric>	// per std::gcd
 
template<typename I> requires std::integral<I> 

class rational {
	I num_;
	I den_;
	
	void semplificazione() {	// semplificazione delle frazioni
		if (den_ == 0) { 	
			if (num_ != 0) num_= I{1};
			return;
		}
		if (den_!=0) {
			I MCD = std::gcd(num_,den_); 
			// gcd funzione build-in di <numeric> che calcola il massimo comun divisore
			num_ /= MCD;
			den_ /= MCD;
			if (den_ < 0) {
				num_ = -num_;
				den_= -den_;
				// es: invece di scrivere 2/-5 preferisco scrivere -2/5
			}
		}
	}
	
public:
	/* Costruttore di default */
	rational()
		: num_(I{0}), den_(I{1})
		// scrivo solo 0 e non 0.0 perchè lavoro con interi e non con double
		// inizializzo den_{1} invece di den_{0} affinchè non dia subito NaN 
	{}
	
	/* Costruttore user-defined */
	rational(const I& pnum, const I& pden)
		: num_(pnum), den_(pden)
		{
			semplificazione();
		}
	
	/* metodi num() den() per ottenere rispettivamente numeratore e denominatore */
	/* --> restituzione dei valori di num e den */
	I num() const {return num_;}
	I den() const {return den_;}
	
	// += 
	rational& operator+=(const rational& other) {
		num_ = (num_*other.den_) + (other.num_*den_);
		den_ = den_*other.den_;
		semplificazione();
		return *this;
	}
	
	// +	implementazione canonica della somma
	rational operator+(const rational& other) const {
		rational ret = *this;
		ret += other;
		return ret;
	}
	
	// -=
	rational& operator-=(const rational& other) {
		num_ = (num_*other.den_) - (other.num_*den_);
		den_ = den_*other.den_;
		semplificazione();
		return *this;
	}
	
	// -	implementazione canonica della sottrazione
	rational operator-(const rational& other) const {
		rational ret = *this;
		ret -= other;
		return ret;
	}
	
	// *= 
	rational& operator*=(const rational& other) {
		num_ *= other.num_;
		den_ *= other.den_;
		semplificazione();
		return *this;
	}
	
	// *
	rational operator*(const rational& other) const {
		rational ret = *this;
		ret *= other;
		return ret;
	}
	
	// /=
	rational& operator/=(const rational& other) {
		num_ *= other.den_;
		den_ *= other.num_;
		semplificazione();
		return *this;
	}
	
	// /
	rational operator/(const rational& other) const {
		rational ret = *this;
		ret /= other;
		return ret;
	}
	
};

template<typename I> requires std::integral<I>

/* operatore << per la stampa di un oggetto della classe rational + gestione errori */
	// numeratore / denominatore, ma se ho num/0 e 0/0 evitare che dia errore con Inf e NaN
std::ostream& operator<<(std::ostream& os, const rational<I>& r){
	if (r.den()==0 && r.num() !=0) {
		os << "Inf";
	}
	else if (r.den()==0 && r.num()==0) {
		os << "NaN";
	}
	else {
		os << r.num();
		if (r.den() !=1) {
			os << "/" << r.den();
		}
	}
	return os;
}