#include <iostream>
#include <string>
using namespace std;

class Elemento{
private:
    string titolo;
    string autore;
public:
    Elemento(const string &titolo = "", const string &autore = "") : titolo(titolo), autore(autore) {}
    virtual void stampa(ostream&s) const = 0;
    virtual ~Elemento() {}
    void setTitolo(string titolo) {this->titolo = titolo;}
    void setAutore(string autore) {this->autore = autore;}
    string getTitolo() const {return titolo;}
    string getAutore() const {return autore;}
};

class Libro : public Elemento{
private:
    int nPagine;
public:
    Libro(const string &titolo = "", const string &autore = "", int nPagine = 0) : Elemento(titolo, autore), nPagine(nPagine) {}
    void stampa(ostream&s) const override{
        s << "Libro:" << endl << "Titolo: " << getTitolo() << endl << "Autore: " << getAutore() << endl << "Numero di pagine: " << nPagine << endl;
    }
};

class DVD : public Elemento{
private:
    double durata;
public:
    DVD(const string &titolo = "", const string &autore = "", double durata = 0.0) : Elemento(titolo, autore), durata(durata) {}
    void stampa(ostream&s) const override{
        s << "DVD: " << endl << "Titolo: " << getTitolo() << endl << "Autore: " << getAutore() << endl << "Durata in ore: " << durata << endl;
    }
};

class Libreria{
private:
    int dim;
    static const int n_elementi = 10;
    Elemento **array;
public:
    Libreria() : dim(0) {
        array = new Elemento*[n_elementi];
    } 
    ~Libreria();
    void inserisci(Elemento*elemento);
    Elemento*ricerca(string titolo);
    friend ostream& operator<<(ostream&s, const Libreria&libreria);
};

Libreria::~Libreria(){
    for(int i=0;i<dim;i++) delete array[i];
    delete [] array;
}

Elemento*Libreria::ricerca(string titolo){
    for(int i=0;i<dim;i++){
        if(array[i]->getTitolo() == titolo) return array[i];
    }
    return nullptr;
}

void Libreria::inserisci(Elemento*elemento){
    if(dim >= n_elementi){
        cout << "Limite raggiungo di elementi (MAX 10)" << endl;
        return;
    } else {
        array[dim] = elemento;
        dim++;
    }
}

ostream& operator<<(ostream&s, const Libreria&libreria) {
    for(int i=0;i<libreria.dim;i++){
        libreria.array[i]->stampa(s);
    }
    return s;
}


int main(void) {
    Libreria libreria;
    libreria.inserisci(new Libro("Harry Potter e la pietra filosofale", "J.K Rowling", 304));
    libreria.inserisci(new DVD("Billie Jean", "Michael Jackson", 4.18));
    libreria.inserisci(new DVD("F**k school!", "404vincent", 2));
    libreria.inserisci(new Libro("Wiimmfi - La resurrezione della Nintendo WiFi Connection", "Wiimm e Leseratte", 100));
    cout << libreria;
    string titolo = "Billie Jean";
    Elemento*trovato = libreria.ricerca(titolo);

    if(trovato)
        cout << "Elemento trovato" << endl;
    else
        cout << "Elemento non trovato" << endl;
    
    titolo = "Nintendo WFC";
    trovato = libreria.ricerca(titolo);

    if(trovato)
        cout << "Elemento trovato" << endl;
    else
        cout << "Elemento non trovato" << endl;

    return 0;
}