#include <iostream>
using namespace std;

class Complesso{
    private:
        float parteReale, parteImmaginaria;
    public:
        Complesso(float xx = 0, float yy = 0) : parteReale(xx), parteImmaginaria(yy) {}
        //14.5 Sovraccaricamento dell’operatore di assegnamento (=)
        Complesso& operator =(const Complesso& altro) {
            if(this != &altro) { // evita autoassegnamento
                parteReale = altro.parteReale;
                parteImmaginaria = altro.parteImmaginaria;
            }
            return *this;
        }
        void stampa() const;
};

void Complesso::stampa() const {
    cout << parteReale << " + " << parteImmaginaria << "i" << endl;
}

int main(void) {
    Complesso c1(2, 3);
    Complesso c2;

    c2 = c1;
    c2.stampa();
    return 0;
}