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
        void inserisciOrdinato(int d);
        Nodo*ricerca(int d);
        void rimuovi(int d);
        friend ostream& operator<<(ostream&s, const List&list);
};

void List::inserisciOrdinato(int d) {
    Nodo* nuovo = new Nodo(nullptr, nullptr, d); 
    if (!head || d <= head->dato) {
        if (!head) {
            head = tail = nuovo;
        } else {
            nuovo->nextptr = head;
            head->prevptr = nuovo;
            head = nuovo;
        }
        return;
    }

    Nodo*corrente=head;
    while(corrente->nextptr && corrente->nextptr->dato < d) {
        corrente=corrente->nextptr;
    }

    nuovo->nextptr = corrente->nextptr;
    nuovo->prevptr = corrente;
    corrente->nextptr = nuovo;

    if(nuovo->nextptr)
        nuovo->nextptr->prevptr = nuovo;
    else
        tail = nuovo;
}

Nodo*List::ricerca(int d) {
    Nodo*corrente=head;
    while(corrente!=nullptr) {
        if(corrente->dato == d)
            return corrente;
        corrente=corrente->nextptr;
    }
    return nullptr;
}

void List::rimuovi(int d) {
    Nodo* corrente = ricerca(d);
    if (!corrente) return;
    
    if (!corrente->prevptr) // primo nodo
        head = corrente->nextptr;
    else
        corrente->prevptr->nextptr = corrente->nextptr;

    if (!corrente->nextptr) // ultimo nodo
        tail = corrente->prevptr;
    else
        corrente->nextptr->prevptr = corrente->prevptr;
    
    cout << "Nodo " << corrente->dato << " cancellato" << endl;
    delete corrente;
}

ostream& operator<<(ostream&s, const List&list) {
    Nodo*corrente=list.head;
    s << "Lista ordinata (davanti)" << endl;
    while(corrente != nullptr) {
        s << corrente->dato << endl;
        corrente=corrente->nextptr;
    }

    corrente=list.tail;
    s << "Lista ordinata (indietro)" << endl;
    while(corrente != nullptr) {
        s << corrente->dato << endl;
        corrente=corrente->prevptr;
    }

    return s;
    
}

int main(void) {
    List lista;
    lista.inserisciOrdinato(100);
    lista.inserisciOrdinato(50);
    lista.inserisciOrdinato(10);
    lista.inserisciOrdinato(20);
    lista.inserisciOrdinato(10);
    lista.inserisciOrdinato(550);
    lista.inserisciOrdinato(102);
    lista.inserisciOrdinato(751);
    cout << lista;
    lista.rimuovi(751);
    lista.rimuovi(100);
    cout << lista;
}