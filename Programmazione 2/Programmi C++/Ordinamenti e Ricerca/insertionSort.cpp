#include <iostream>

using namespace std;

void insertionSort(int array[], int n) {
    for(int i=1;i<n;i++) {
        int key = array[i];
        int j = i-1;
        while(j>=0 && array[j] > key) {
            array[j+1] = array[j];
            j--;
        }
        array[j+1] = key;
    }
}

void stampa(int array[], int n) {
    for(int i=0;i<n;i++) {
        cout << "Array [" << i << "] = " << array[i] << endl;
    }
}

int main(void) {

    int array[] = {3, 5, 11, 104, 99, 2};
    int n = sizeof(array) / sizeof(array[0]);
    cout << "========Array========" << endl;
    stampa(array, n);
    insertionSort(array, n);
    cout << "========Array ordinato========" << endl;  
    stampa(array, n);
    return 0;
}