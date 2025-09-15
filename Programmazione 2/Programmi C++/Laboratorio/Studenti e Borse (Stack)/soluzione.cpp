#include <iostream>
#include <fstream>
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
    int getMatricola() const {
        return matricola;
    } 
    string getNome() const {
        return nome;
    }
    string getCognome() const {
        return cognome;
    }
    double getMedia() const {
        return media;
    }
    virtual void stampa(ostream &s) const {
        s << matricola << ": " << nome << " " << cognome << " - " << "media " << media;
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
    void setImporto(int importo){
        this->importo = importo;
    } 
    void setDurata(int durata){
        this->durata = durata;
    }
};

class StudenteBorsista : public Studente{
private:
    BorsaDiStudio*borsa;
public:
    StudenteBorsista(int matricola = 0, const string &nome = "", const string &cognome = "", double media = 0.0, BorsaDiStudio*borsa = nullptr) : Studente(matricola, nome, cognome, media), borsa(borsa) {}
    double get_importo_borsa() const {
        if(borsa)
            return borsa->getImporto();
        else
            return 0.0;
    }

    void stampa(ostream&s) const override{
        Studente::stampa(s);
        if(borsa) s << " [borsa di " << borsa->getImporto() << " euro]";
    }
};

struct Nodo{
    Studente*studente;
    Nodo*nextptr;
    Nodo(Studente*studente) : studente(studente), nextptr(nullptr) {}
};

class Stack{
private:
    Nodo*head;
public:
    Stack() : head(nullptr) {}
    ~Stack();
    bool isEmpty() const;
    void push(Studente*studente);
    void pop();
    double somma();
    void rimuovi();
    friend ostream& operator<<(ostream&s, const Stack&stack);
};

void Stack::rimuovi(){
    Nodo*corrente=head;
    Nodo*precedente=nullptr;
    while(corrente!=nullptr){
        if(corrente->studente->getMedia() < 25){
            cout << "Studente insufficiente rimosso: " << corrente->studente->getNome() << " " << corrente->studente->getCognome() << " - " << "Matricola: " << corrente->studente->getMatricola() << endl;
            Nodo*temp = corrente;
            if(precedente == nullptr){
                head = corrente->nextptr;
            } else {
                precedente->nextptr = corrente->nextptr;
            }
            corrente=corrente->nextptr;
            delete temp->studente;
            delete temp;
        } else {
            precedente = corrente;
            corrente=corrente->nextptr;
        }
    }
}

double Stack::somma(){
    Nodo*temp = head;
    double s = 0.0;
    while(temp!=nullptr){
        StudenteBorsista*borsista = dynamic_cast<StudenteBorsista*>(temp->studente);
        if(borsista) s+=borsista->get_importo_borsa();
        temp=temp->nextptr;
    }
    return s;
}

Stack::~Stack(){
    while(!isEmpty()) pop();
}

void Stack::push(Studente*studente){
    Nodo*nuovo = new Nodo(studente);
    nuovo->nextptr = head;
    head = nuovo;
}

bool Stack::isEmpty() const {
    return head == nullptr;
}

void Stack::pop(){
    if(isEmpty()) return;
    Nodo*temp = head;
    head = head->nextptr;
    delete temp->studente;
    delete temp;
}

ostream& operator<<(ostream&s, const Stack&stack){
    if(stack.isEmpty()) return s;
    Nodo*corrente=stack.head;
    s << "La pila contiene i seguenti studenti:" << endl;
    while(corrente!=nullptr){
        corrente->studente->stampa(s);
        s << endl;
        corrente=corrente->nextptr;
    }
    return s;
}

int main(void) {
    Stack stack;
    int matricola;
    string nome, cognome;
    double media;
    int durata, importo;
    ifstream file("input.txt");
    if(file.fail()){
        cout << "Errore nell'apertura del file" << endl;
        return -1;
    }

    while(file >> matricola >> nome >> cognome >> media >> importo >> durata){
        if(importo == 0.0)
            stack.push(new Studente(matricola, nome, cognome, media));
        else
            stack.push(new StudenteBorsista(matricola, nome, cognome, media, new BorsaDiStudio(importo, durata)));
    }

    stack.rimuovi();
    cout << stack;
    cout << "Totale importi borse di studio: " << stack.somma() << " euro" << endl;
    return 0;
}