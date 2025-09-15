#include <iostream>
using namespace std;

class List;
ostream& operator<<(ostream &s, const List& list);

class Nodo {
private:
    Nodo* nextptr;
    int numero;

public:
    Nodo(Nodo* p = nullptr, int n = 0) : nextptr(p), numero(n) {}
    friend class List;
    friend ostream& operator<<(ostream& s, const List& list);
};

class List {
private:
    Nodo* head;

public:
    List() : head(nullptr) {}
    List& inserisciTesta(int d);
    void inserisci(int d, Nodo* p);
    Nodo* ricerca(int d);
    void rimuovi(int d);

    friend ostream& operator<<(ostream& s, const List& list);
};

List& List::inserisciTesta(int d) {
    head = new Nodo(head, d); 
    return *this;
}

void List::inserisci(int d, Nodo* p) {
    if(p == nullptr) {
        inserisciTesta(d);
    } else {
        Nodo* nuovo = new Nodo(p->nextptr, d);
        p->nextptr = nuovo;
    }
}

Nodo* List::ricerca(int d) {
    Nodo* corrente = head;
    while (corrente != nullptr) {
        if (corrente->numero == d)
            return corrente;
        corrente = corrente->nextptr;
    }
    return nullptr;
}

void List::rimuovi(int d) {
    Nodo* corrente = head;
    Nodo* precedente = nullptr;

    if (corrente != nullptr && corrente->numero == d) {
        head = corrente->nextptr;
        delete corrente;
        return;
    }

    while (corrente != nullptr && corrente->numero != d) { 
        precedente = corrente;
        corrente = corrente->nextptr;
    }

    if (corrente == nullptr)
        return;

    precedente->nextptr = corrente->nextptr;
    delete corrente;
}

ostream &operator<<(ostream &s, const List& list) {
    s << "Ci sono questi elementi nella lista:" << endl;
    Nodo* corrente = list.head; 
    while (corrente != nullptr) {
        s << corrente->numero << endl;
        corrente = corrente->nextptr;
    }
    return s;
}

int main() {
    List lista;
    lista.inserisciTesta(10);
    lista.inserisciTesta(20);
    lista.inserisciTesta(30);
    cout << lista;

    Nodo* nodo20 = lista.ricerca(20);
    lista.inserisci(25, nodo20);  // inserisce 25 dopo il nodo con valore 20

    cout << lista;

    lista.rimuovi(20);
    cout << lista;
    
    return 0;
}
