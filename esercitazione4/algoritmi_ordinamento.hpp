#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

template <typename T>
void bubble_sort(vector<T> & vec) {
	int n = vec.size();
	for (int i=0; i<(n-1); i++) {
		for (int j=(n-1); j>=i+1; j--) {
			if (vec[j]<vec[j-1]) {
				swap(vec[j],vec[j-1]);
			}
		}
	}
}

template <typename T>
void insertion_sort(vector<T> & vec) {
	int n = vec.size();
	for (int j=1; j<n; j++) {
		T key = vec[j];
		int i = j - 1;
		while (i>=0 && vec[i] > key) {
			vec[i+1] = vec[i];
			i = i-1; 
		}
		vec[i+1]=key;
	}
}

template <typename T>
void selection_sort(vector<T> & vec) {
	int n = vec.size();
	for (int i=0; i<n-1; i++) {
		int min_indice = i;
		for (int j=i+1; j<(n); j++) {
			if (vec[j]<vec[min_indice]) {
				min_indice = j;
			}
		}
		if (min_indice != i) {
			swap(vec[i],vec[min_indice]);
		}
	}
}
