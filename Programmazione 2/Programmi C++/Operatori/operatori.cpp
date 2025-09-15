#include <iostream>

using namespace std;

class vettore{
    public:
        vettore(float xx = 0, float yy = 0) : x(xx), y(yy) {}
        void stampa() const;
        //Sovraccaricamento
        vettore operator +(const vettore &b) const;
        //14.2 Operatori unari
        vettore operator -();
        vettore operator -(vettore &b) const;
    private:
        float x, y;

};

void vettore::stampa() const {
    cout << x << " ' ' " << y << endl;
}

vettore vettore::operator+(const vettore&b) const {
    return vettore (x + b.x, y + b.y);
}

vettore vettore::operator-() {
    return vettore(-x, -y);
}

vettore vettore::operator-(vettore &b) const {
    return *this + -b;
}

int main(void) {
    vettore u(3, 1), v(1, 2), somma, neg, differ;

    somma = u + v;
    somma.stampa();
    neg = -somma;
    neg.stampa();
    differ = u-v;

    differ.stampa();
    return 0;
}