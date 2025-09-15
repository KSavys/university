#include <iostream>

using namespace std;

void ricerca(int a, int array[], int n) {
    bool trovato = false;
    for(int i=0;i<n;i++) {
        if(a == array[i]) {
            cout << "Il numero " << a << " è presente nella posizione " << i << endl;
            trovato = true;
        }
    }
    if(!trovato) 
        cout << "Il numero inserito non è presente" << endl;
}

int main(void) {
    int array[] = {9, 2, 3, 5};
    int n = sizeof(array)/sizeof(array[0]);
    for(int i=0;i<n;i++) {
        cout << "Array ["<< i <<"] = " << array[i] << endl;  
    }
    int a = 0;
    cout << "Inserisci un valore" << endl;
    cin >> a;
    ricerca(a, array, n);

}