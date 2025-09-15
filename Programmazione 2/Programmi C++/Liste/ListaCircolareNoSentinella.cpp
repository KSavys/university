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

void List::inserisci(int d) {
    Nodo*nuovo = new Nodo(nullptr, nullptr, d);
    if(!head) {
        head = tail = nuovo;
        head->nextptr = head;
        head->prevptr = head;
    } else {
        nuovo->nextptr = head;
        nuovo->prevptr = tail;
        tail->nextptr = nuovo;
        head->prevptr = nuovo;
        tail = nuovo;
    }
}

Nodo*List::ricerca(int d) {
    if(!head) {
        cout << "Lista vuota" << endl;
        return nullptr;
    }
    Nodo*corrente=head;

    do{
        if(corrente->dato == d){
            return corrente;
        }
        corrente=corrente->nextptr;
    } while(corrente!=head);

    return nullptr;
}

ostream& operator<<(ostream& s, const List& list) {
    if (!list.head) {
        s << "Lista vuota" << endl;
        return s;
    }

    Nodo* corrente = list.head;
    s << "Lista avanti" << endl;
    do {
        s << corrente->dato << endl;
        corrente = corrente->nextptr;
    } while (corrente != list.head);

    s << "Lista indietro" << endl;
    corrente = list.tail;
    Nodo* start = list.tail;
    do {
        s << corrente->dato << endl;
        corrente = corrente->prevptr;
    } while (corrente != start);

    return s;
}

void List::rimuovi(int d) {
    Nodo*corrente = ricerca(d);

    if(!corrente) {
        cout << "Nessun valore trovato" << endl;
        return;
    }

    if(corrente->nextptr == corrente) { 
        delete corrente;
        head = tail = nullptr;
        return;
    }

    corrente->prevptr->nextptr = corrente->nextptr;
    corrente->nextptr->prevptr = corrente->prevptr;

    if(corrente == head)
        head = corrente->nextptr;
    if(corrente == tail)
        tail = corrente->prevptr;
    delete corrente;
}

int main(void) {
    List lista;
    lista.inserisci(10);
    lista.inserisci(20);
    lista.inserisci(30);
    cout << lista;
    lista.ricerca(30);
    lista.rimuovi(30);
    cout << lista;
    return 0;
    
}