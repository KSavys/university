#include <iostream>

using namespace std;

class List;
ostream&operator<<(ostream&s, const List&list);

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
        Nodo*sentinella;
    public:
        List();
        void inserisci(int d);
        Nodo*ricerca(int d);
        void rimuovi(int d);
        friend ostream& operator<<(ostream&s, const List&list);
};

List::List() {
    sentinella = new Nodo();
    sentinella->nextptr = sentinella;
    sentinella->prevptr = sentinella;
}

void List::inserisci(int d) {
    Nodo*nuovo = new Nodo(sentinella, sentinella->prevptr, d);
    sentinella->prevptr->nextptr = nuovo;
    sentinella->prevptr = nuovo;
}

Nodo*List::ricerca(int d) {
    Nodo*corrente = sentinella->nextptr;
    while(corrente != sentinella) {
        if(corrente->dato == d){
            return corrente;
        }   
        corrente=corrente->nextptr;
    }
    return nullptr;
}

void List::rimuovi(int d) {
    Nodo*corrente = ricerca(d);
    if(!corrente) {
        cout << "Nessun valore trovato" << endl;
        return;
    }
    corrente->prevptr->nextptr = corrente->nextptr;
    corrente->nextptr->prevptr = corrente->prevptr;
    delete corrente;
}

ostream& operator<<(ostream&s, const List&list) {
    s << "Lista avanti" << endl;

    Nodo*corrente = list.sentinella->nextptr;
    while(corrente != list.sentinella) {
        s << corrente->dato << endl;
        corrente=corrente->nextptr;
    }

    s << "Lista indietro" << endl;
    corrente = list.sentinella->prevptr;
    while(corrente != list.sentinella) {
        s << corrente->dato << endl;
        corrente=corrente->prevptr;
    }
    return s;

}

int main(void) {
    List lista;
    lista.inserisci(10);
    lista.inserisci(50);
    lista.inserisci(70);
    lista.inserisci(110);
    cout << lista;
    lista.ricerca(110);
    lista.rimuovi(110);
    cout << lista;
    return 0;
}