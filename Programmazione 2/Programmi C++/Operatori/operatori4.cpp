#include <iostream>
#include <fstream>
using namespace std;

class Complesso{
    private:
        float parteReale, parteImmaginaria;
    public:
        Complesso(float xx = 0, float yy = 0) : parteReale(xx), parteImmaginaria(yy) {}
        //14.6 Sovraccaricamento degli operatori di inserimento ed estrazione
        friend ostream& operator<<(ostream& os, const Complesso &c) { ///esempio con cout:
            os << c.parteReale << " + " << c.parteImmaginaria << "i" << endl;
            return os;
        }

        //esempio con cin
        friend istream& operator>>(istream& is, Complesso& c) {
            cout << "Inserisci parte reale" << endl;
            is >> c.parteReale;
            cout << "Inserisci parte immaginaria" << endl;
            is >> c.parteImmaginaria;
            return is;
        }

};

int main(void) {

    //esempio con cout
    Complesso c(3, 4);
    cout << "Il numero complesso è: " << c << endl;

    //esempio con cin
    Complesso c2;
    cin >> c2;
    cout << "Hai inserito: " << c2 << endl;
    return 0; 

}