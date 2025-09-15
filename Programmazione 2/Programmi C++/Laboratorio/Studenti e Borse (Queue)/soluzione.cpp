#include <iostream>
#include <string>
using namespace std;

class Studente{
private:
    int matricola;
    string nome;
    string cognome;
    double media;
public:
    Studente(int matricola = 0, const string &nome = "", const string &cognome = "", double media = 0.0) : matricola(matricola), nome(nome), cognome(cognome), media(media) {}
    void setMatricola(int matricola) {
        this->matricola = matricola;
    }
    void setNome(string nome) {
        this->nome = nome;
    }
    void setCognome(string cognome) {
        this->cognome = cognome;
    }
    void setMedia(double media) {
        this->media = media;
    }
    int getMatricola() const {return matricola;}
    string getNome() const {return nome;}
    string getCognome() const {return cognome;}
    double getMedia() const {return media;}
    virtual void stampa(ostream&s) const {
        s << matricola << ": " << nome << " " << cognome << " - " << media;
    }
};

class BorsaDiStudio{
private:
    int importo;
    int durata;
public:
    BorsaDiStudio(int importo = 0, int durata = 0) : importo(importo), durata(durata) {}
    int getImporto() const {return importo;}
    int getDurata() const {return durata;}
};

class StudenteBorsista : public Studente{
private:
    BorsaDiStudio*borsa;
public:
    StudenteBorsista(int matricola = 0, const string &nome = "", const string &cognome = "", double media = 0.0, BorsaDiStudio*borsa = nullptr) : Studente(matricola, nome, cognome, media), borsa(borsa) {}
    double get_importo_borsa() {
        if(borsa)
            return borsa->getImporto();
        else
            return 0.0;
    }
    void stampa(ostream&s) const override{
        Studente::stampa(s);
        if(borsa) s << " [borsa di " << borsa->getImporto() << " euro]";
    }

    ~StudenteBorsista(){
        delete borsa;
    }
};

struct Nodo{
    Studente*studente;
    Nodo*nextptr;
    Nodo(Studente*studente) : studente(studente), nextptr(nullptr) {}
};

class Queue{
private:
    Nodo*head;
    Nodo*tail;
    int dimensione;
    static const int max_nodi = 10;
public:
    Queue() : head(nullptr), tail(nullptr), dimensione(0) {}
    ~Queue();
    void enqueue(Studente*studente);
    void dequeue();
    bool isEmpty() const;
    void rimuovi();
    double somma();
    friend ostream& operator<<(ostream&s, const Queue&queue);
};

Queue::~Queue(){
    while(!isEmpty()) dequeue();
}

double Queue::somma() {
    double s = 0.0;
    Nodo*corrente=head;
    while(corrente!=nullptr){
        StudenteBorsista*borsista = dynamic_cast<StudenteBorsista*>(corrente->studente);
        if(borsista) s+=borsista->get_importo_borsa();
        corrente=corrente->nextptr;
    }
    return s;
}

void Queue::rimuovi(){
    Nodo*corrente=head;
    Nodo*precedente = nullptr;
    while(corrente!=nullptr){
        if(corrente->studente->getMedia() < 25){
            Nodo*temp = corrente;
            if(!precedente){
                head = corrente->nextptr;
            } else {
                precedente->nextptr = corrente->nextptr;
            }
            if(corrente == tail)
                tail = precedente;
            corrente=corrente->nextptr;
            delete temp->studente;
            delete temp;
            dimensione--;
        } else {
            precedente = corrente;
            corrente=corrente->nextptr;
        }
    }
}

void Queue::enqueue(Studente*studente){
    if(dimensione>=max_nodi){
        cout << "Limite raggiunto max 10 nodi" << endl;
        return;
    }

    Nodo*nuovo = new Nodo(studente);
    if(!tail){
        head = tail = nuovo;
    } else {
        tail->nextptr = nuovo;
        tail = nuovo;
    }
    dimensione++;
}

bool Queue::isEmpty() const {
    return head == nullptr;
}

void Queue::dequeue() {
    if(isEmpty()) return;
    Nodo*temp = head;
    head = head->nextptr;
    if(head == nullptr) tail = nullptr;
    delete temp;
    dimensione--;
}

ostream& operator<<(ostream&s, const Queue&queue){
    if(queue.isEmpty()) return s;
    Nodo*corrente=queue.head;
    while(corrente!=nullptr) {
        corrente->studente->stampa(s);
        s << endl;
        corrente=corrente->nextptr;
    }
    return s;
}

int main(void) {
    Queue queue;
    queue.enqueue(new Studente(1001, "Mario", "Rossi", 25.5));
    queue.enqueue(new StudenteBorsista(1002, "Anna", "Verdi", 28.0, new BorsaDiStudio(880)));
    queue.enqueue(new Studente(1003, "Luca", "Bianchi", 26.0));
    queue.enqueue(new Studente(1004, "Sara", "Neri", 27.5));
    queue.enqueue(new StudenteBorsista(1005, "Marco", "Gialli", 24.0, new BorsaDiStudio(500)));
    queue.enqueue(new StudenteBorsista(1006, "Laura", "Marroni", 29.0, new BorsaDiStudio(600)));

    cout << "Contenuto della coda:" << endl;
    queue.rimuovi();
    cout << queue;

    cout << "Totale degli importi delle borse di studio: " << queue.somma() << " euro" << endl;
    return 0;
}