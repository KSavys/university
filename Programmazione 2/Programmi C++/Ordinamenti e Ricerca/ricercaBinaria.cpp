z#include <iostream>

using namespace std;

int ricerca (int array[], int n, int a) {
    int sinistra = 0, destra = n-1;
    while(sinistra <= destra) {
        int medio = sinistra + (destra - sinistra) / 2;
        if(array[medio] == a) {
            return medio;
        }

        if(array[medio] < a) {
            sinistra = medio + 1;
        } else {
            destra = medio - 1;
        }
        
    }
    return -1;
}
int main(void) {
    int array[] = {1, 2, 3, 4};
    int n = sizeof(array)/sizeof(array[0]);
    for(int i=0;i<n;i++) {
        cout << "Array ["<< i <<"] = " << array[i] << endl;  
    }
    int a = 0;
    cout << "Inserisci un valore:" << endl;
    cin >> a;
    int b = ricerca(array, n, a);
    if(b != -1) {
        cout << "Valore trovato nella posizione " << b << endl;
    } else {
        cout << "Nessun valore trovato" << endl;
    }
}