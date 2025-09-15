#include <iostream>
using namespace std;

template <typename T>
class List; 

template <typename T>
class Nodo {
private:
    Nodo* nextptr;
    T valore;
public:
    Nodo(Nodo* p = nullptr, T v = T()) : nextptr(p), valore(v) {}
    friend class List<T>;
    template <typename U>
    friend ostream& operator<<(ostream& s, const List<U>& list);
};

template <typename T>
class List {
private:
    Nodo<T>* head;
public:
    List() : head(nullptr) {}
    void inserisciTesta(T d);
    List& inserisci(T d, Nodo<T>* p);
    Nodo<T>* ricerca(T d);
    void rimuovi(T d);
    template <typename U>
    friend ostream& operator<<(ostream& s, const List<U>& list);
};

template <typename T>
void List<T>::inserisciTesta(T d) {
    head = new Nodo<T>(head, d);
}

template <typename T>
List<T>& List<T>::inserisci(T d, Nodo<T>* p) {
    if(p == nullptr) {
        inserisciTesta(d);
    }else {
        Nodo<T>* nuovo = new Nodo<T>(p->nextptr, d); 
        p->nextptr = nuovo;
    }
    return *this;
}

template <typename T>
Nodo<T>* List<T>::ricerca(T d) {
    Nodo<T>* corrente = head;
    while(corrente != nullptr) {
        if(corrente->valore == d) {
            cout << "Valore trovato" << endl;
            return corrente;
        }
        corrente = corrente->nextptr;
    }
    return nullptr;
}

template <typename T>
void List<T>::rimuovi(T d) {
    Nodo<T>* corrente = head;
    Nodo<T>* precedente = nullptr;

    if(corrente != nullptr && corrente->valore == d) {
        head = corrente->nextptr;
        delete corrente;
        return;
    }

    while(corrente != nullptr && corrente->valore != d) {
        precedente = corrente;
        corrente = corrente->nextptr;
    }

    if(corrente == nullptr)
        return;

    precedente->nextptr = corrente->nextptr;
    delete corrente;
}

template <typename T>
ostream& operator<<(ostream& s, const List<T>& list) {
    s << "Ci sono questi elementi nella lista:" << endl;
    Nodo<T>* corrente = list.head;
    while (corrente != nullptr) {
        s << corrente->valore << endl;
        corrente = corrente->nextptr;
    }
    return s;
}

int main() {
    List<int> listaInt;
    listaInt.inserisciTesta(10);
    listaInt.inserisciTesta(20);
    listaInt.inserisciTesta(30);

    cout << listaInt;

    // Cerca nodo con valore 20
    Nodo<int>* nodo20 = listaInt.ricerca(20);

    // Inserisci 25 dopo 20
    listaInt.inserisci(25, nodo20);

    cout << listaInt;

    List<string> listaString;
    listaString.inserisciTesta("Wiimmfi");
    listaString.inserisciTesta("Leseratte");
    cout << listaString;

   
    return 0;
}
