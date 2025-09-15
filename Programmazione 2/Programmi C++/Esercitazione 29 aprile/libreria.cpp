#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Elemento {
    private:
        string titolo;
        string autore;
    public:
        Elemento (const char *t, const char*a) : titolo(t), autore(a) {}

        string getTitolo() const {
            return titolo;
        }

        string getAutore() const {
            return autore;
        }

        virtual void stampa(ostream& s=cout) const {
            s << "Titolo: " << titolo << endl;
            s << "Autore: " << autore << endl;
        }
};

class Libro : public Elemento {
    private:
        int numPag;
    public:
        Libro(const char* t, const char* a, int num) : Elemento(t, a), numPag(num) {}

        int getPagine() {
            return numPag;
        }

        virtual void stampa(ostream& s=cout) const {
            s << "L'elemento è un libro:" << endl;
            Elemento::stampa(s);
            s << "Il numero di pagine sono: " << numPag << endl;
        }
};

class DVD : public Elemento {
    private:
        float durata;
    public:
        DVD(const char* t, const char* a, float d) : Elemento(t, a), durata(d) {}

        float getDurata() {
            return durata;
        }

        virtual void stampa(ostream& s=cout) const {
            s << "L'elemento è un DVD:" << endl;
            Elemento::stampa(s);
            s << "La durata del DVD è: " << durata << " ore" << endl;
        }
};

class Libreria{
    private:
        Elemento **array;
        int n;
        int n_max;
    public:
        Libreria(int max) : n(0), n_max(max) {
            array = new Elemento*[max];
        }

        ~Libreria() {
            delete [] array;
        } 
        
        //oppure si potrebbe fare così
        /*
        ~Libreria() {
            for(int i=0;i<n;i++) {
                delete array[i]
            }
            delete [] array;
        }
        */
        
        void inserisci(Elemento *e) {
            if(n >= n_max) {
                cout << "Hai raggiunto il limite di inserimento degli elementi" << endl;
                return;
            } else {
                array[n] = e;
                n++;
            }
        }

        void Stampa() {
            if(n == 0) {
                cout << "Non ci sono elementi nella libreria" << endl;
                return;
            } else {
                cout << "Ci sono " << n << " elementi disponibili nella libreria" << endl;
                for(int i=0;i<n;i++) {
                    array[i]->stampa();
                }
            }
        }

        Elemento*ricerca(const char* titolo2) {
            if(n == 0) {
                cout << "Non ci sono elementi nella libreria" << endl;
            } else {
                for(int i=0;i<n;i++) {
                    if(array[i]->getTitolo() == titolo2) {
                        return array[i];
                    }
                }
            }
            return nullptr;
        }

};

ostream& operator<<(ostream& s, const Elemento*e) {
    if(e != nullptr) {
        cout << "Elemento trovato" << endl;
        e->stampa(s);
    } else {
        cout << "Elemento non trovato" << endl;
    }
    return s;
}

int main(void) {
    Libreria libreria(10);

    libreria.inserisci(new DVD("The Introduction", "Rockstar Games", 1.5));
    libreria.inserisci(new DVD("Il Signore degli Anelli", "Peter Jackson", 3));
    libreria.inserisci(new Libro("Matrix", "Mastrolindo", 140));
    libreria.Stampa();

    const char*titolo2 = "The Introduction";

    Elemento *p = libreria.ricerca(titolo2);
    cout << p;

    titolo2 = "Cal Kestis";

    p = libreria.ricerca(titolo2);
    cout << p;

    titolo2 = "Il Signore degli Anelli";
    p = libreria.ricerca(titolo2);
    cout << p;

    return 0;
}