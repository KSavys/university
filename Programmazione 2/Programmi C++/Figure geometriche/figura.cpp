#include <iostream>

using namespace std;

class Figura{
    private:
        int x;
        int y;

    public:
        Figura(int val_x, int val_y) : x(val_x), y(val_y) {}
        virtual void stampa() {
            
            cout << "x = " << x << endl;
            cout << "y = " << y << endl;
        }
        virtual float calcoloArea() = 0;
};

class Cerchio: public Figura{
    private:
        int r;
        const float PI;

    public:
        Cerchio(int val_x, int val_y, int r_r) : Figura(val_x, val_y), r(r_r), PI(3.145f) {}

        virtual void stampa() {
            Figura::stampa();
            cout << "Raggio = " << r << endl;
        }

        virtual float calcoloArea() {
            return r * r * PI;
        }
};

class Rettangolo : public Figura {
    private:
        int base;
        int altezza;
    public:

        Rettangolo(int val_x, int val_y, int val_base, int val_altezza) : Figura(val_x, val_y), base(val_base), altezza(val_altezza) {} 
        virtual void stampa() {
            Figura::stampa();
            cout << "Base = " << base << endl;
            cout << "Altezza = " << altezza << endl;
        }
        virtual float calcoloArea() {
            return base * altezza;
        }
        

};

int main(void) {
    Rettangolo fig(7, 5, 10, 5);
    fig.stampa();
    Cerchio cer(10, 15, 5);
    cer.stampa();
    Rettangolo r(14, 35, 10, 20);
    r.stampa();

    Figura *figure[] = {&fig, &cer, &r};
    float areaTot = 0;

    for(int i=0;i<sizeof(figure) / sizeof(figure[0]); i++) {
        figure[i] -> stampa();
        float area = figure[i] -> calcoloArea();
        cout << "Area = " << area << endl;
        areaTot+= area;
    }

    cout << "Area totale = " << areaTot << endl;

}