#include <iostream>
using namespace std;

class Contatore{
    private:
        int valore;
    public:
        Contatore(int v = 0) {
            valore = v;
        }
        //14.3 Sovraccaricamento degli operatori unari
        Contatore& operator++() {
            valore++;
            return *this;
        }

        void stampa() const {
            cout << "Numero:" << valore << endl;
        }
};

class Complesso{
    private:
        float parteReale;
        float parteImmaginaria;
    public:
        Complesso(float pr, float pi) : parteReale(pr), parteImmaginaria(pi) {}
        void stampaComplex() const;
        //14.4 Sovraccaricamento degli operatori binari
        Complesso operator*(double numero) const {
            return Complesso(parteImmaginaria * numero, parteReale * numero);
        }
};

void Complesso::stampaComplex() const {
    cout << parteReale << " + " << parteImmaginaria << "i" << endl;
}

int main() {
    Contatore c(5);
    c.stampa();
    ++c;
    c.stampa();

    Complesso cx(6, 4);
    cx.stampaComplex();
    Complesso risultato = cx * 2;
    risultato.stampaComplex();
    return 0;
}