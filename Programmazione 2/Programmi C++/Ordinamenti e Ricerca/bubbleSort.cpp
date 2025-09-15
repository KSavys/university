#include <iostream>

using namespace std;

void bubbleSort(int array[], int n) {
    for(int i=0;i<n-1;i++) {
        for(int j=0;j<n-i-1;j++) {
            if(array[j] > array[j+1]) {
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }
}

void stampa(int array[], int n) {
    for(int i=0;i<n;i++) {
        cout << "Array [" << i << "] = " << array[i] << endl;
    }
}

int main(void) {

    int array[] = {5, 6, 7, 3, 1};
    int n = sizeof(array) / sizeof(array[0]);
    cout << "========Array========" << endl;
    stampa(array, n);
    bubbleSort(array, n);
    cout << "========Array ordinato========" << endl;  
    stampa(array, n);
    return 0;
}