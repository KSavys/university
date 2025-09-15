#include <iostream>
#include <fstream>
using namespace std;

typedef struct libro{
    string titolo;
    string autore;
    int annoPubblicazione;
    float prezzo;
    char genere[21];

    void stampa() {
        cout << "-----------------------";
        cout << "Titolo: " << titolo << endl;
        cout << "Autore: " << autore << endl;
        cout << "Anno di pubblicazione: " << annoPubblicazione << endl;
        cout << "Prezzo: " << prezzo << endl;
        cout << "Genere: " << genere << endl;
        cout << "-----------------------";
    }
}Libro;

void printBooks(Libro archivio[], int numerolibri) {
    for(int i=0;i<numerolibri;i++) {
        archivio[i].stampa();
    }
}

void ricercaLibro(Libro archivio[], int numerolibri, string titolo2) {
    bool trovato = false;
    for(int i=0;i<numerolibri;i++) {
        if(archivio[i].titolo == titolo2) {
            cout << "Libro trovato\n";
            archivio[i].stampa();
            trovato = true;
        }
    }

    if(!trovato)
        cout << "\nLibro non trovato\n";
}

void memorizzaArchivio(const char* nomefile, Libro archivio[], int numerolibri) {
    fstream file(nomefile, ios::out);
    if(file.fail()) {
        cout << "File non aperto" << endl;
        return;
    }

    file << numerolibri << endl;
    if(numerolibri == 0) {
        cout << "Non ci sono libri nell'archivio\n" << endl;
        return;
    } else {
        for(int i=0;i<numerolibri;i++) {
            file << archivio[i].titolo << endl;
            file << archivio[i].autore << endl;
            file << archivio[i].annoPubblicazione << endl;
            file << archivio[i].prezzo << endl;
            file << archivio[i].genere << endl;
        }
        cout << "Archivio memorizzato\n" << endl;
    }
    
    file.close();
    
}

bool caricaArchivio(const char* nomefile, Libro archivio[], int &numerolibri) {
    ifstream file(nomefile, ios::in);
    if(file.fail()) {
        cout << "Errore nel file\n" << endl;
        return false;
    }

    file >> numerolibri;
    file.get();

    for(int i=0;i<numerolibri;i++) {
        getline(file, archivio[i].titolo);
        getline(file, archivio[i].autore);
        file >> archivio[i].annoPubblicazione;
        file.get();
        file >> archivio[i].prezzo;
        file.get();
        file.getline(archivio[i].genere, 21);
    }
    file.close();
    return true;
}

int main(int argc, char*argv[]) {
    int x = 0;
    const int max_libri = 100;
    int numerolibri = 0;
    Libro archivio[max_libri];

    if(!caricaArchivio("archivio.txt", archivio, numerolibri))
        cout << "Nessun archivio caricato\n" << endl;
    else
        cout << "Archivio caricato\n" << endl;

    do{
        cout<<("\nMenù:\n1. Inserisci un libro\n2. Stampa tutti i libri\n3. Cerca un libro mediante titolo\n4. Memorizza l'archivio nel file\n5. Carica l'archivio\n0. Terminazione programma\n") << endl;
        cin >> x;
        cin.get();

        switch(x) {
            case 1:
                {
                    if (numerolibri>=max_libri) {
                        cout << "Archivio pieno, impossibile aggiungere altri libri.\n";
                        break;
                    }
                    cout << "Inserisci il titolo\n";
                    getline(cin, archivio[numerolibri].titolo);
                    cout << "Inserisci l'autore\n";
                    getline(cin, archivio[numerolibri].autore);
                    cout << "Inserisci l'anno di pubblicazione\n";
                    cin >> archivio[numerolibri].annoPubblicazione;
                    cin.get();
                    cout << "Inserisci il prezzo\n";
                    cin >> archivio[numerolibri].prezzo;
                    cin.get();
                    cout << "Inserisci il genere\n";
                    cin.getline(archivio[numerolibri].genere, 21);
                    numerolibri++;
                    break;
                }
            case 2:
                {
                    printBooks(archivio, numerolibri);
                    break;
                }
            case 3:
                {
                    string titolo2;
                    if(!numerolibri) {
                        cout << "Non ci sono libri nell'archivio\n" << endl;
                        break;
                    }
                    cout << "Inserisci un titolo per la ricerca\n";
                    getline(cin, titolo2);
                    ricercaLibro(archivio, numerolibri, titolo2);
                    break;

                }
            case 4:
                {
                    memorizzaArchivio("archivio.txt", archivio, numerolibri);
                    break;
                }
            case 5:
                {
                    caricaArchivio("archivio.txt", archivio, numerolibri);
                    break;
                }
            case 0:
                cout << "Arrivderci\n";
                break;
                
        }
    }while(x!=0);
    return 0;
}