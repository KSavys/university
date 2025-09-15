#include <iostream>
using namespace std;

class List;
ostream& operator<<(ostream&s, const List& list);

class Nodo{
    private:
        int valore;
        Nodo*nextptr;
    public:
        Nodo(Nodo*p = nullptr, int v = 0) : nextptr(p), valore(v) {}
        friend class List;
        friend ostream& operator<<(ostream &s, const List& list);
};

class List{
    private:
        Nodo*head;
    public:
        List() : head(nullptr) {}
        void rimuovi(int d);
        Nodo* ricerca(int d);
        void inserisciOrdinato(int d);

        friend ostream& operator<<(ostream& s, const List& list);
};

void List::inserisciOrdinato(int d) {
    if(head == nullptr || d <= head->valore) {
        head = new Nodo(head, d);
        return;
    }

    Nodo*corrente=head;
    while(corrente->nextptr != nullptr && corrente->nextptr->valore < d) {
        corrente=corrente->nextptr;
    }

    Nodo*nuovo = new Nodo(corrente->nextptr, d);
    corrente->nextptr = nuovo;
}

Nodo* List::ricerca(int d) {
    Nodo*corrente=head;
    while(corrente != nullptr) {
        if(corrente->valore == d) {
            cout << "Trovato il numero: " << corrente->valore << endl;
            return corrente;
        }
        corrente=corrente->nextptr;
    }
    cout << "Numero " << d << " non trovato." << endl;
    return nullptr;
}

void List::rimuovi(int d) {
    Nodo*corrente = head;
    Nodo*precedente = nullptr;

    if(corrente!=nullptr && corrente->valore == d) {
        head = corrente->nextptr;
        cout << "Nodo " << corrente->valore << " cancellato" << endl;
        delete corrente;
        return;
    }

    while(corrente!=nullptr && corrente->valore != d) {
        precedente = corrente;
        corrente=corrente->nextptr;
    }

    if(corrente == nullptr) {
        cout << "Nodo con valore " << d << " non trovato, niente da rimuovere." << endl;
        return;
    } 

    precedente->nextptr = corrente->nextptr;
    cout << "Nodo " << corrente->valore << " cancellato" << endl;
    delete corrente;
}

ostream& operator<<(ostream&s, const List&list) {
    s << "Lista Ordinata" << endl;
    Nodo*corrente = list.head;
    while(corrente != nullptr) {
        s << corrente->valore << endl;
        corrente=corrente->nextptr;
    }
    return s;

}

int main(void) {
    List lista;
    lista.inserisciOrdinato(90);
    lista.inserisciOrdinato(60);
    lista.inserisciOrdinato(110);
    cout << lista;
    lista.ricerca(90);
    lista.rimuovi(90);
    cout << lista;
    lista.rimuovi(71);
    lista.ricerca(111);
}