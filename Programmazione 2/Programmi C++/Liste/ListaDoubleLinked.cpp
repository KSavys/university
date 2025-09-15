#include <iostream>
using namespace std;

class List;
ostream& operator<<(ostream&s, const List&list);

class Nodo{
    private:
        Nodo*nextptr;
        Nodo*prevptr;
        int dato;
    public:
        Nodo(Nodo*p = nullptr, Nodo*pr = nullptr, int d = 0) : nextptr(p), prevptr(pr), dato(d) {}
        friend class List;
        friend ostream& operator<<(ostream&s, const List&list);
};

class List{
    private:
        Nodo*head;
        Nodo*tail;
    public:
        List() : head(nullptr), tail(nullptr) {}
        void inserisci(int d);
        Nodo*ricerca(int d);
        void rimuovi(int d);
        friend ostream& operator<<(ostream&s, const List&list);
};

void List::inserisci(int d){
    Nodo*nuovo = new Nodo(nullptr, nullptr, d);
    if(!head) {
        head = tail = nuovo;
        return;
    }
    tail->nextptr = nuovo;
    nuovo->prevptr = tail;
    tail=nuovo;
}

Nodo* List::ricerca(int d) {
    Nodo*corrente=head;
    while(corrente!=nullptr) {
        if(corrente->dato == d)
            return corrente;
        corrente=corrente->nextptr;
    }
    return nullptr;
}

void List::rimuovi(int d) {
    Nodo*corrente = ricerca(d);

    if(!corrente) return;
    
    if(!corrente->prevptr)
        head = corrente->nextptr;
    else 
        corrente->prevptr->nextptr = corrente->nextptr;
    
    if(!corrente->nextptr)
        tail = corrente->prevptr;
    else
        corrente->nextptr->prevptr = corrente->prevptr;
    
    cout << "Nodo " << corrente->dato << " eliminato" << endl;
    delete corrente;
    
}

ostream &operator<<(ostream&s, const List&list) {
    Nodo*corrente = list.head;
    s << "Lista davanti" << endl;
    while(corrente != nullptr) {
        s << corrente->dato << endl;
        corrente=corrente->nextptr;
    }

    corrente = list.tail;
    s << "Lista indietro" << endl;
    while(corrente!=nullptr) {
        s << corrente->dato << endl;
        corrente=corrente->prevptr;
    }
    return s;
}
int main(void) {
    List lista;

    lista.inserisci(10);
    lista.inserisci(50);
    lista.inserisci(60);
    cout << lista;
    lista.rimuovi(10);
    cout << lista;

    return 0;
}