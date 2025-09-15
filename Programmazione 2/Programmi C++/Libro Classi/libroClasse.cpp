#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

class Libro {
private:
    string titolo;
    string autore;
    int annoPubblicazione;
    float prezzo;
    char genere[21];

public:
    Libro() {}

    Libro (string t, string a, int anno, int p, const char* g) {
        titolo = t;
        autore = a;
        annoPubblicazione = anno;
        prezzo = p;
        strncpy(genere, g, 20);
        genere[20] = '\0';
    }

    void stampa() {
        cout << "-----------------------" << endl;
        cout << "Titolo: " << titolo << endl;
        cout << "Autore: " << autore << endl;
        cout << "Anno di pubblicazione: " << annoPubblicazione << endl;
        cout << "Prezzo: " << prezzo << endl;
        cout << "Genere: " << genere << endl;
        cout << "-----------------------" << endl;
    }

    void memorizzaArchivio(fstream &file) {
        file << titolo << endl;
        file << autore << endl;
        file << annoPubblicazione << endl;
        file << prezzo << endl;
        file << genere << endl;
    }

    void caricaArchivio(ifstream &file) {
        getline(file, titolo);
        getline(file, autore);
        file >> annoPubblicazione;
        file.get();
        file >> prezzo;
        file.get();
        file.getline(genere, 21);
    }

    string getTitolo() {
        return titolo;
    }
};

class Archivio {
private:
    static const int maxLibri = 100;
    Libro archivio[maxLibri];
    int numeroLibri;

public:
    Archivio() : numeroLibri(0) {}

    void aggiungiLibro(const Libro &libro);
    void stampaLibri();
    void ricercaLibro(const string &titoloR);
    void salvaArchivio(const char *nomeFile);
    void caricaArchivio(const char *nomeFile);
};


void Archivio::aggiungiLibro(const Libro &libro) {
    if (numeroLibri >= maxLibri) {
        cout << "Hai raggiunto il limite di 100 libri." << endl;
        return;
    }
    archivio[numeroLibri] = libro;
    numeroLibri++;
}

void Archivio::stampaLibri() {
    if (numeroLibri == 0) {
        cout << "Nessun libro inserito." << endl;
    } else {
        for (int i = 0; i < numeroLibri; i++) {
            archivio[i].stampa();
        }
    }
}

void Archivio::ricercaLibro(const string &titoloR) {
    bool trovato = false;

    if (numeroLibri == 0) {
        cout << "Non c'è nessun libro inserito nell'archivio." << endl;
        return;
    }

    for (int i = 0; i < numeroLibri; i++) {
        if (archivio[i].getTitolo() == titoloR) {
            cout << "Libro trovato!" << endl;
            cout << "Risultati dei libri trovati:" << endl;
            archivio[i].stampa();
            trovato = true;
        }
    }

    if (!trovato) {
        cout << "Nessun libro trovato." << endl;
    }
}

void Archivio::salvaArchivio(const char *nomeFile) {
    fstream file(nomeFile, ios::out);
    if (!file) {
        cout << "Errore: file non aperto." << endl;
        return;
    }

    file << numeroLibri << endl;

    for (int i = 0; i < numeroLibri; i++) {
        archivio[i].memorizzaArchivio(file);
    }

    cout << "Archivio salvato." << endl;
    file.close();
}

void Archivio::caricaArchivio(const char *nomeFile) {
    ifstream file(nomeFile, ios::in);
    if (!file) {
        cout << "Errore: file non aperto." << endl;
        return;
    }

    file >> numeroLibri;
    file.get(); 

    for (int i = 0; i < numeroLibri; i++) {
        archivio[i].caricaArchivio(file);
    }

    cout << "Archivio caricato." << endl;
    file.close();
}

int main() {
    Archivio archivio;
    int scelta = 0;
    archivio.caricaArchivio("archivio.txt");

    do {
        cout << "\nMenù:\n";
        cout << "1. Inserisci un libro\n";
        cout << "2. Visualizza tutti i libri\n";
        cout << "3. Cerca un libro mediante titolo\n";
        cout << "4. Salva archivio su file\n";
        cout << "0. Esci\n";
        cout << "Scelta: ";
        cin >> scelta;
        cin.get(); 

        switch (scelta) {
            case 1: {
                int anno;
                float prezzo;
                string autore, titolo;
                char genere[21];

                cout << "Inserisci il titolo: ";
                getline(cin, titolo);
                cout << "Inserisci l'autore: ";
                getline(cin, autore);
                cout << "Inserisci l'anno: ";
                cin >> anno;
                cin.get();
                cout << "Inserisci il prezzo: ";
                cin >> prezzo;
                cin.get();
                cout << "Inserisci il genere: ";
                cin.getline(genere, 21);
                Libro nuovoLibro(titolo, autore, anno, prezzo, genere);
                archivio.aggiungiLibro(nuovoLibro);
                break;
            }
            case 2:
                archivio.stampaLibri();
                break;
            case 3: {
                string titoloR;
                cout << "Inserisci un titolo da cercare: ";
                getline(cin, titoloR);
                archivio.ricercaLibro(titoloR);
                break;
            }
            case 4:
                archivio.salvaArchivio("archivio.txt");
                break;
            case 0:
                archivio.salvaArchivio("archivio.txt");
                cout << "Saluti!" << endl;
                break;
            default:
                cout << "Scelta non valida." << endl;
        }

    } while (scelta != 0);

    return 0;
}
