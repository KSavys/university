#include <iostream>

using namespace std;

void stampa(int array[], int n) {
    for(int i=0;i<n;i++) {
        cout << "Array [" << i << "] = " << array[i] << endl;
    }
}

void selectionSort(int array[], int n) {
    for(int i=0;i<n-1;i++) {
        int minIndex = i;
        for(int j=i+1;j<n;j++) {
            if(array[j] < array[minIndex])
                minIndex = j;
        }
        int temp = array[i];
        array[i] = array[minIndex];
        array[minIndex] = temp;
    }
}

int main(void) {
    
    int array[] = {9, 43, 6, 182, 438, 312, 1, 34, 2, 5};
    int n = sizeof(array) / sizeof(array[0]);
    cout << "===Array===" << endl;
    stampa(array, n);
    selectionSort(array, n);
    cout << "===Array ordinato===" << endl;
    stampa(array, n);

    return 0;
}