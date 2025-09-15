#include <iostream>
using namespace std;

int partition(int array[], int low, int high) {
    int pivot = array[high];
    int i = low - 1;

    for(int j=low;j<high;j++) {
        if(array[j] < pivot) {
            i++;
            swap(array[i], array[j]);
        }
    }
    swap(array[i+1], array[high]);
    return i+1;
}

void quickSort(int array[], int low, int high) {
    if(low < high) {
        int pi = partition(array, low, high);
        quickSort(array, low, pi-1);
        quickSort(array, pi+1, high);
    }
}

void stampa(int array[], int n) {
    for(int i=0;i<n;i++) {
        cout << "Array [" << i << "] = " << array[i] << endl;
    }
}

void swap(int &x, int &y) {
    int temp = x;
    x = y;
    y = temp;
}

int main(void) {
    int array[] = {3, 5, 11, 104, 99, 2};
    int n = sizeof(array) / sizeof(array[0]);
    cout << "========Array========" << endl;
    stampa(array, n);
    quickSort(array, 0, n-1);
    cout << "========Array ordinato========" << endl;  
    stampa(array, n);
    return 0;
}