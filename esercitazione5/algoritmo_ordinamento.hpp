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

template <typename T>
void merge(vector<T> & vec, int left, int mid, int right) {
	int n1 = mid-left+1;
	int n2 = right-mid;
	
	vector<T> L(n1), R(n2);
	
	for (int i=0; i < n1; i++) {
		L[i] = vec[left+i];
	}
	for (int j=0; j<n2; j++) {
		R[j] = vec[mid+1+j];
	}
	
	int i=0, j=0;
	int k=left;
	
	while (i<n1 && j<n2) {
		if (L[i] <= R[j]) {
			vec[k] = L[i];
			i=i+1;
		} 
		else {
			vec[k] = R[j];
			j=j+1;
		}
		k=k+1;
	}
	
	while (i<n1) {
		vec[k] = L[i];
		i=i+1;
		k=k+1;
	}
	
	while (j<n2) {
		vec[k] = R[j];
		j=j+1;
		k=k+1;
	}
	
}

template <typename T>
void merge_sort(vector<T> & vec, int left, int right) {
	if (left >= right) {
		return;
	}	
	int mid = left + (right - left)/2;
	merge_sort(vec,left,mid);
	merge_sort(vec,mid+1,right);
	merge(vec,left,mid,right);
	}

template <typename T>
int partition(vector<T>& vec, int p, int r) {
    T pivot = vec[r];
	int i = p -1;

	for (int j=p; j<=r-1; j++) {
		if (vec[j] < pivot) {
			i=i+1;
			swap(vec[i],vec[j]);
		}
	}
	swap(vec[i+1],vec[r]);
	return i+1;
}

template <typename T>
void quicksort(vector<T> & vec, int low, int high) {
		if (low<high) {
			int pi = partition(vec,low,high);
			quicksort(vec,low,pi-1);
			quicksort(vec,pi+1,high);
		}
}

template <typename T>
void quicksort_ottimizzato(vector<T> &vec, int low, int high) {
	const int soglia=325;
	
	if (low<high) {
		if ((high - low +1) <= soglia) {
			//insertion solo sul vettore [low,high]
			for (int j=low +1; j<=high; j++) {
				T key = vec[j];
				int i=j-1;
				while (i >= low && vec[i]>key) {
					vec[i+1]=vec[i];
					i--;
				}
				vec[i+1] = key;
			}
			return;
		}
		int pi=partition(vec,low,high);
		quicksort_ottimizzato(vec,low,pi-1);
		quicksort_ottimizzato(vec,pi+1,high);
	}
}