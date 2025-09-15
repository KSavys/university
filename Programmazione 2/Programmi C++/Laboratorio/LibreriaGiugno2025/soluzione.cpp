/*Il programma deve gestire una libreria con:
classe item che contiene titolo, data, id
classe Book sottoclasse item con autore
classe DVD derivata di item con durata
classe studente che può prendere un max di 5 item
classe professore che può prendere in max di 10 item
classe libreria con almeno attributo name e metodi borrowItem() e returnItem()
I due metodi devono essere in grado di gestire la logica in modo autonomo
Le stampe degli item devono essere:
"Book - autore - id"
"DVD - durata - id"
Crea un main in grado di mostrare il funzionamento del programma senza output esterno*/

#include <iostream>
using namespace std;

class Item{
private:
    string titolo;
    string data;
    int id;
public:
    Item(const string &titolo = "", const string &data = "", int id = 0) : titolo(titolo), data(data), id(id) {}
    virtual ~Item() {}
    virtual void stampa() const = 0;
    string getTitolo() const {return titolo;}
    string getData() const {return data;}
    int getId() const {return id;}
};

class Book : public Item{
private:
    string autore;
public:
    Book(const string &titolo = "", const string &data = "", int id = 0, const string &autore = "") : Item(titolo, data, id), autore(autore) {}
    void stampa() const override {
        cout << "Book - " << autore << " - " << getId() << endl;
    }
};

class DVD : public Item{
private:
    double durata;
public:
    DVD(const string &titolo = "", const string &data = "", int id = 0, double durata = 0.0) : Item(titolo, data, id), durata(durata) {}
    void stampa() const {
        cout << "DVD - " << durata << " - " << getId() << endl;
    }
};

class Studente{
private:
    string nome;
    static const int n_oggetti = 5;
    Item**item;
    int n;
public:
    Studente(const string &nome = "") : nome(nome), n(0) {
        item = new Item*[n_oggetti];
    } 
    ~Studente();
    void borrowItem(Item*it);
    void returnItem(int id);
    void stampa();
};

void Studente::borrowItem(Item*it){
    if(n>=n_oggetti) {
        cout << "Limite raggiunto per gli studenti MAX 5" << endl;
        return;
    }
    item[n] = it;
    n++; 
    
}

void Studente::returnItem(int id){
    for(int i=0;i<n;i++){
        if(item[i]->getId() == id){
            cout << nome << " restituisce l'item" << endl;
            for(int j=i;j<n-1;j++){
                item[j] = item[j+1];
            }
            n--;
            return;
        }
    }
}

void Studente::stampa(){
    cout << "Gli item dello studente " << nome << endl;
    for(int i=0;i<n;i++){
        item[i]->stampa();
    }
}

class Professore{
private:
    string nome;
    static const int n_oggetti = 10;
    Item**item;
    int n;
public:
    Professore(const string &nome = "") : nome(nome), n(0) {
        item = new Item*[n_oggetti];
    } 
    ~Professore();
    void borrowItem(Item*it);
    void returnItem(int id);
    void stampa();
};

void Professore::borrowItem(Item*it){
    if(n>=n_oggetti) {
        cout << "Limite raggiunto per i professori MAX 10" << endl;
        return;
    }
    item[n] = it;
    n++; 
}

void Professore::returnItem(int id){
    for(int i=0;i<n;i++){
        if(item[i]->getId() == id){
            cout << nome << " restituisce l'item" << endl;
            for(int j=i;j<n-1;j++){
                item[j] = item[j+1];
            }
            n--;
            return;
        }
    }
}

void Professore::stampa(){
    cout << "Gli item del professore " << nome << endl;
    for(int i=0;i<n;i++){
        item[i]->stampa();
    }
}

Professore::~Professore(){ 
    delete [] item;
}

Studente::~Studente(){
    delete [] item;
}

class Libreria{
private:
    string name;
public:
    Libreria(const string &name = "") : name(name) {}
    void borrowItem(Studente&s, Item*item);
    void returnItem(Studente&s, int id);
    void borrowItem(Professore&p, Item*item);
    void returnItem(Professore&p, int id);
};

void Libreria::borrowItem(Studente&s, Item*item){
    s.borrowItem(item);
}

void Libreria::returnItem(Studente&s, int id){
    s.returnItem(id);
}

void Libreria::borrowItem(Professore&p, Item*item){
    p.borrowItem(item);
}

void Libreria::returnItem(Professore&p, int id){
    p.returnItem(id);
}

int main() {
    Libreria lib("Biblioteca Centrale");
    
    Book b1("Il Signore degli Anelli", "1954", 1, "Tolkien");
    Book b2("Harry Potter", "1997", 2, "Rowling");
    DVD d1("Inception", "2010", 3, 2.5);
    DVD d2("Matrix", "1999", 4, 2.3);

    
    Studente s("Alice");
    Professore p("Bob");

   
    lib.borrowItem(s, &b1);
    lib.borrowItem(s, &d1);
    lib.borrowItem(p, &b2);
    lib.borrowItem(p, &d2);

    
    s.stampa();
    p.stampa();

   
    lib.returnItem(s, 1);
    lib.returnItem(p, 4);

    s.stampa();
    p.stampa();

    return 0;
}