#include <iostream>

using namespace std;

void merge(int array[], int left, int mid, int right) {
    int n1 = mid - left + 1; // dimensione del primo sotto-array
    int n2 = right - mid;    // dimensione del secondo sotto-array

    int *L = new int[n1];
    int *R = new int[n2];

    for(int i = 0; i < n1; i++) {
        L[i] = array[left + i];
    }

    for(int j = 0; j < n2; j++) {
        R[j] = array[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;

    while(i < n1 && j < n2) {
        if(L[i] <= R[j]) {
            array[k++] = L[i++];
        } else {
            array[k++] = R[j++];
        }
    }

    while(i < n1) {
        array[k++] = L[i++];
    }

    while(j < n2) {
        array[k++] = R[j++];
    }

    delete[] L;
    delete[] R;
}

void mergeSort(int array[], int left, int right) {
    if(left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(array, left, mid);
        mergeSort(array, mid + 1, right);
        merge(array, left, mid, right);
    }
}

void stampa(int array[], int n) {
    for(int i=0;i<n;i++) {
        cout << "Array [" << i << "] = " << array[i] << endl;
    }
}

int main(void) {
    int array[] = {8, 3, 2, 6, 1};
    int n = sizeof(array) / sizeof(array[0]);
    cout << "Array" << endl;
    stampa(array, n);
    mergeSort(array, 0, n-1);
    cout << "Merge Sort" << endl;
    stampa(array, n);
}