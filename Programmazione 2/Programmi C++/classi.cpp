#include <iostream>
using namespace std;

class Persona{
    public:
        string nome;
        int eta;

        void saluta() {
            cout << "Ciao mi chiamo " << nome << " e ho " << eta << endl;
        }

        ~Persona(){
            cout << "Distruttore chiamato per Persona: " << nome << endl;
        }
};

class Persona2 {
    private:
        const string nome;
        int &eta;
    public:
        Persona2(const string& name, int &age) : nome(name), eta(age) {}

        void mostraNome() {
            cout << "Ciao sono " << nome << " e ho " << eta << endl;
        }

        ~Persona2() {
            cout << "Distruttore chiamato per Persona2: " << nome << endl;
        }

};

class Rettangolo{
    public:
        int base;
        int altezza;

        Rettangolo(int b, int a) : base(b), altezza (a) {}

        int area() {
            return base * altezza;
        }

        ~Rettangolo() {
            cout << "Distruttore chiamato per Rettangolo di base " << base << " e altezza " << altezza << endl;
        }
};

class radio {
    private:
        int frequenza;
        int volume;

    public:
        void Accende();
        void AumentaFrequenza();
        void DiminuisciFrequenza();

        radio(int f, int v) : frequenza(f), volume(v) {}

        int getVolume() {
            return volume;
        }

        int getFrequenza() {
            return frequenza;
        }

        

};

void radio::Accende() {
    frequenza = 49;
    volume = 49;
}

void radio::AumentaFrequenza() {
    frequenza++;
}

void radio::DiminuisciFrequenza() {
    frequenza--;
}

int main(void) {
    Persona p;
    p.nome = "Alex";
    p.eta = 18;
    p.saluta();
    int eta_near = 19;
    Persona2 p2("Near", eta_near);
    p2.mostraNome();
    eta_near = 20;
    p2.mostraNome();
    Rettangolo r (10, 10);
    cout << "Base: " << r.base << endl;
    cout << "Altezza: " << r.altezza << endl;
    cout << "L'area del rettangolo è: " << r.area() << endl;

    radio rr(0, 0);

    rr.Accende();
    rr.AumentaFrequenza();
    rr.DiminuisciFrequenza();

    cout << "Frequenza attuale: " << rr.getFrequenza() << endl;
    cout << "Volume: " << rr.getVolume() << endl;
    return 0;
}