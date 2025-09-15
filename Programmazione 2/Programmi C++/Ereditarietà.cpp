#include <iostream>
using namespace std;

class Animale {
public:
    void mangia() {
        cout << "L'animale mangia" << endl;
    }
};

class Cane : public Animale {
public:
    void abbaia() {
        cout << "Il cane abbaia" << endl;
    }
};

class Pubblicazione {
public:
    void inserisciEditore(const char* e) {
        editore = e;
    }

    void inserisciData(int d) {
        data = d;
    }

    string getEditore() {
        return editore;
    }

    int getData() {
        return data;
    }

private:
    string editore;
    int data;
};

class Rivista : public Pubblicazione {
public:
    void inserisciTiratura(int t) {
        tiratura = t;
    }

    int getTiratura() {
        return tiratura;
    }

private:
    int tiratura;
};

class Volante {
    public:
        void vola() {
            cout << "Sto volando" << endl;
        }
};

class Nuotante {
    public:
        void nuota() {
            cout << "Sto nuotando" << endl;
        }
};

class Anatra : public Nuotante, public Volante {
    public:
        void verso() {
            cout << "Quack" << endl;
        }
};

class Animale2 {
    public:
        virtual void verso2() {
            cout << "L'animale fa il verso" << endl;
        }

};

class Serpente : public Animale2{
    public:
        void verso2() override {
            cout << "Il serpente fa il verso" << endl;
        }
};

void faiVerso(Animale2 *a2) {
    a2->verso2(); //binding dinamico
}

class Forma{
    public:
        virtual void disegna() = 0;
};

class Cerchio : public Forma{
    public:
        void disegna() override {
            cout << "Disegno un cerchio" << endl;
        }
};

class Rettangolo : public Forma{
    public:
        void disegna() override {
            cout << "Disegno un rettangolo" << endl;
        }
};

class Persona{
    public:
        Persona(string nome) {
            this->nome = nome;
            cout << "Costruttore creato di persona" << endl;
        }
        string getNome() {
            return nome;
        }
    private:
        string nome;
};

class Studente : public Persona{
    public: 
        Studente (string nome) : Persona (nome) {
            cout << "Costruttore di studente" << endl;
        }
        
          
};

int main() {
    Cane c;
    c.mangia();
    c.abbaia();

    Pubblicazione p;
    p.inserisciEditore("KSavys");
    p.inserisciData(2025);

    cout << "Editore: " << p.getEditore() << endl;
    cout << "Anno: " << p.getData() << endl;

    Rivista r;
    r.inserisciEditore("Scientific Journal");
    r.inserisciData(2024);
    r.inserisciTiratura(5000);

    cout << "Rivista - Editore: " << r.getEditore() << ", Anno: " << r.getData() << ", Tiratura: " << r.getTiratura() << endl;

    Anatra a;
    a.verso();
    a.nuota();
    a.vola();
    Animale2 a2;
    Serpente s;

    faiVerso(&a2);
    faiVerso(&s);

    Forma *f1 = new Cerchio();
    Forma *f2 = new Rettangolo();

    f1->disegna();
    f2->disegna();

    delete f1;
    delete f2;

    Studente s1("KSavys");
    cout << "Il nome dello studente: " << s1.getNome() << endl;
    return 0;
}
