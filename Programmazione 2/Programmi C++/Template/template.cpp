#include <iostream>

using namespace std;

template <typename T> 
void scambia(T& v1, T& v2) {
    T temp = v1;
    v1 = v2;
    v2 = temp;
}

template <typename T2>
T2 massimo (T2 x, T2 y) {
    return (x > y) ? x : y;
}

template <typename T3>
void scambia2 (T3 &x_A, T3 &x_B) {
    T3 temp = x_A;
    x_A = x_B;
    x_B = temp;
}

class Libro{
    public:
        string titolo;
        Libro(const char*t) : titolo(t) {}
        string getTitolo() {
            return titolo;
        }
};

int main(void) {
    int v1 = 6, v2 = 9;
    cout << "Valori originali" << endl;
    cout << "v1 = " << v1 << " v2 = " << v2 << endl;

    scambia(v1, v2);
    cout << "Valori scambiati" << endl;
    cout << "v1 = " << v1 << " v2 = " << v2 << endl;

    char c = 'G', g = 'K';
    cout << "Valori originali" << endl;
    cout << "c = " << c << " g = " << g << endl;
    scambia(c, g);
    cout << "Valori scambiati" << endl;
    cout << "c = " << c << " g = " << g << endl;

    int x = 6, y = 7;

    cout << "Il massimo è: " << massimo(x, y) << endl;

    int x_valore = 5, y_valore = 2;

    cout << "Il massimo è: " << massimo(x_valore, y_valore) << endl;
    
    Libro l1("Wiimmfi - La nascita del servizio");
    Libro l2("Calogero e i video di TikTok");
    cout << "Primo Libro: " << l1.getTitolo() << endl;
    cout << "Secondo Libro: " << l2.getTitolo() << endl;
    scambia2(l1, l2);
    cout << "Primo Libro: " << l1.getTitolo() << endl;
    cout << "Secondo Libro: " << l2.getTitolo() << endl;
    



}