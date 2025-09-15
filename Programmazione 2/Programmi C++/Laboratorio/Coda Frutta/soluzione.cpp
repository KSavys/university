z#include <iostream>
#include <string>
using namespace std;

class Frutto{
private:
    string nome, colore, stagione;
public:
    Frutto(const string &nome = "", const string &colore = "", const string &stagione = "") : nome(nome), colore(colore), stagione(stagione){}
    string getNome() const {return nome;}
    string getColore() const {return colore;}
    string getStagione() const {return stagione;}
    virtual void stampa(ostream&s) const = 0;
    virtual string sapore() const = 0;
    virtual string getTipo() const = 0;
};

class Mela : public Frutto{
public:
    Mela(const string &nome = "", const string &colore = "", const string &stagione = "", const string &gusto = "") : Frutto(nome, colore, stagione), gusto(gusto) {}
    string sapore() const {return gusto;}
    void stampa(ostream&s) const override {
        s << getNome() << " - " << getColore() << " - " << getStagione() << " - " << gusto << endl;
    }
    string getTipo() const {return "Mela";}
private:
    string gusto;
};

class Arancia : public Frutto{
public:
    Arancia(const string &nome = "", const string &colore = "", const string &stagione = "", const string &gusto = "") : Frutto(nome, colore, stagione), gusto(gusto) {}
    string sapore() const {return gusto;}
    void stampa(ostream&s) const override {
        s << getNome() << " - " << getColore() << " - " << getStagione() << " - " << gusto << endl;
    }
    string getTipo() const {return "Arancia";}
private:
    string gusto;
};

template <typename T>
class Queue;

template <typename T>
ostream& operator<<(ostream&s, const Queue<T>&queue);

template <typename T>
struct Nodo{
    T valore;
    Nodo<T>*nextptr;
    Nodo(T&v) : valore(v), nextptr(nullptr) {}
    template <typename U>
    friend class Queue;
    template <typename U>
    friend ostream& operator<<(ostream&s, const Queue<U>&queue);
};

template <typename T>
class Queue{
private:
    Nodo<T>*head;
    Nodo<T>*tail;
    int dim;
public:
    Queue() : head(nullptr), tail(nullptr) , dim(0) {}
    ~Queue();
    void enqueue(T val);
    void dequeue();
    Nodo<T>*getHead() {return head;}
    bool isEmpty() const;
    T*front() const;
    int Eliminazione(string tipo);
    template <typename U>
    friend class Queue;
    template <typename U>
    friend ostream& operator<<(ostream&s, const Queue<U>&queue);
};

template <typename T>
Queue<T>::~Queue<T>(){
    while(!isEmpty()) dequeue();
}

template <typename T>
int Queue<T>::Eliminazione(string tipo) {
    int contatore = 0;
    Nodo<T>*corrente=head;
    Nodo<T>*precedente=nullptr;
    while(corrente!=nullptr) {
        if(tipo == corrente->valore->getTipo()) {
            Nodo<T>*temp = corrente;
            if(precedente == nullptr) {
                head = corrente->nextptr;
            } else {
                precedente->nextptr = corrente->nextptr;
            }
            corrente=corrente->nextptr;
            contatore++;
            dim--;
            delete temp->valore;
            delete temp;
        } else {
            precedente=corrente;
            corrente=corrente->nextptr;
        }
    }
    return contatore;
} 

template <typename T>
void Queue<T>::enqueue(T val) {
    Nodo<T>*nuovo = new Nodo<T>(val);
    if(tail == nullptr) {
        head = tail = nuovo;
    } else {
        tail->nextptr = nuovo;
        tail = nuovo;
    }
    dim++;
}

template <typename T>
void Queue<T>::dequeue() {
    if(isEmpty()) return;
    Nodo<T>*temp = head;
    T val = temp->valore;
    head = head->nextptr;
    if(head == nullptr) tail = nullptr;
    dim--;
    delete val;
    delete temp;
}

template <typename T>
T*Queue<T>::front() const {
    if(!isEmpty())
        return head->valore;
    else
        return nullptr;
}

template <typename T>
bool Queue<T>::isEmpty() const {
    return head == nullptr;
}

template <typename T>
ostream& operator<<(ostream&s, const Queue<T>&queue){
    if(queue.isEmpty()) return s;
    Nodo<T>*corrente=queue.head;
    while(corrente!=nullptr) {
        corrente->valore->stampa(s);
        corrente=corrente->nextptr;
    }
    return s;
}



int main(void) {
    Queue<Frutto*>queue;
    cout << "Coda dei frutti:" << endl;
    queue.enqueue(new Mela("Granny Smith", "Verde", "Autunno", "Aspro"));
    queue.enqueue(new Arancia("Tarocco", "Arancione", "Inverno", "Dolce"));
    queue.enqueue(new Mela("Golden Delicious", "Giallo", "Autunno", "Dolce"));
    queue.enqueue(new Arancia("Navel", "Arancione", "Inverno", "Dolce-Acido"));
    queue.enqueue(new Mela("Fuji", "Rosso", "Autunno", "Dolce"));
    queue.enqueue(new Arancia("Valencia", "Arancione", "Estate", "Acido"));
    cout << queue;

    string tipo;
    cout << "Inserisci il tipo di frutti da rimuovere (Arancia-Mela): ";
    cin >> tipo;
    int dim = queue.Eliminazione(tipo);
    cout << "Sono stati rimossi " << dim << " frutti dalla coda." << endl;
    cout << queue;
    return 0;
}