#include <iostream>
#include <string>
using namespace std;

class Prodotto{
private:
    int codice;
    double prezzo;
public:
    Prodotto() : codice(0), prezzo(0.0) {}
    Prodotto(int codice, double prezzo) : codice(codice), prezzo(prezzo) {}
    int getCodice() const { return codice; }
    double getPrezzo() const { return prezzo; }
    void setCodice(int c) { codice = c; }
    void setPrezzo(double p) { prezzo = p; }

    friend ostream& operator<<(ostream& s, const Prodotto& prodotto) { 
        s << "Prodotti" << endl << "ID: " << prodotto.codice  << " Prezzo: " << prodotto.prezzo << " €" << endl;
        return s;
    }

    virtual bool verifica() const = 0;
    virtual ~Prodotto() {}
};

class ProdottoAlimentare : public Prodotto{
private:
    int giornoScad, meseScad, annoScad;
public:
    ProdottoAlimentare(int codice=0, double prezzo=0.0, int g=0, int m=0, int a=0) : Prodotto(codice, prezzo), giornoScad(g), meseScad(m), annoScad(a) {}

    bool verifica() const override {
        int annoCorrente=2025, meseCorrente=9, giornoCorrente=4;
        if(annoScad < annoCorrente) return false;
        if(annoScad == annoCorrente && meseScad < meseCorrente) return false;
        if(annoScad == annoCorrente && meseScad == meseCorrente && giornoScad < giornoCorrente) return false;
        return true;
    }

    friend ostream& operator<<(ostream& s, const ProdottoAlimentare& p) {
        s << "Prodotti" << endl << "ID: " << p.getCodice() << " Prezzo: " << p.getPrezzo() << " €" << endl << "Data di scadenza: " << p.giornoScad << " / " << p.meseScad << " / " << p.annoScad << endl;
        return s;
    }

};

class ProdottoPerBambini : public Prodotto{
private:
    string fascia;
public:
    ProdottoPerBambini(int codice=0, double prezzo=0.0, const string &f="") : Prodotto(codice, prezzo), fascia(f) {}

    friend ostream& operator<<(ostream& s, const ProdottoPerBambini& p) {
        s << "Prodotti" << endl << "ID: " << p.getCodice() << " Prezzo: " << p.getPrezzo() << " €" << endl << "Fascia d'età: " << p.fascia << endl;
        return s;
    }

    bool verifica() const override { return true; }
};

class Venditore{
private:
    Prodotto** prodotto;
    int n;
    int id_venditore;
public:
    Venditore() : prodotto(nullptr), n(0), id_venditore(0) {}
    Venditore(int id) : prodotto(nullptr), n(0), id_venditore(id) {}

    ~Venditore() {
        for(int i=0;i<n;i++) delete prodotto[i];
        delete[] prodotto;
    }

    void aggiungiProdotto(Prodotto* p) {
        Prodotto** nuovo = new Prodotto*[n+1];
        for(int i=0;i<n;i++) nuovo[i]=prodotto[i];
        nuovo[n]=p;
        delete[] prodotto;
        prodotto=nuovo;
        n++;
    }

    double calcolaPrezzoTotale() const {
        double s=0.0;
        for(int i=0;i<n;i++) s+=prodotto[i]->getPrezzo();
        return s;
    }

    double calcolaValoreMagazzino() const {
        double s=0.0;
        for(int i=0;i<n;i++)
            if(prodotto[i]->verifica()) s+=prodotto[i]->getPrezzo();
        return s;
    }

    friend ostream& operator<<(ostream& s, const Venditore& v) {
        s << "ID Venditore: " << v.id_venditore << " N prodotti venduti: " << v.n << endl;
        for(int i=0;i<v.n;i++) {
            if(auto pa = dynamic_cast<ProdottoAlimentare*>(v.prodotto[i]))
                s << *pa << endl;
            else if(auto pb = dynamic_cast<ProdottoPerBambini*>(v.prodotto[i]))
                s << *pb << endl;
        }
        s << "Prezzo totale: " << v.calcolaPrezzoTotale() << " €" << endl;
        return s;
    }
};

void bubbleSortCrescente(Venditore** venditori, int n) {
    for(int i=0; i<n-1; i++) {
        for(int j=0; j<n-i-1; j++) {
            if(venditori[j]->calcolaPrezzoTotale() > venditori[j+1]->calcolaPrezzoTotale()) {
                Venditore* temp = venditori[j];
                venditori[j] = venditori[j+1];
                venditori[j+1] = temp;
            }
        }
    }
}

void bubbleSortDecrescente(Venditore** venditori, int n) {
    for(int i=0; i<n-1; i++) {
        for(int j=0; j<n-i-1; j++) {
            if(venditori[j]->calcolaPrezzoTotale() < venditori[j+1]->calcolaPrezzoTotale()) {
                Venditore* temp = venditori[j];
                venditori[j] = venditori[j+1];
                venditori[j+1] = temp;
            }
        }
    }
}

int main() {
    int n_v = 3;
    Venditore** venditori = new Venditore*[n_v];
    for(int i=0;i<n_v;i++) venditori[i] = new Venditore(i+1);

    venditori[0]->aggiungiProdotto(new ProdottoAlimentare(101,3.5,10,9,2025));
    venditori[0]->aggiungiProdotto(new ProdottoAlimentare(102,5.2,1,1,2026));
    venditori[0]->aggiungiProdotto(new ProdottoPerBambini(201,15.9,"0-3"));
    venditori[0]->aggiungiProdotto(new ProdottoPerBambini(202,22.0,"3-6"));
    venditori[0]->aggiungiProdotto(new ProdottoAlimentare(103,7.5,20,10,2025));

    venditori[1]->aggiungiProdotto(new ProdottoPerBambini(203,25,"3-6"));
    venditori[1]->aggiungiProdotto(new ProdottoAlimentare(104,7,12,12,2025));
    venditori[1]->aggiungiProdotto(new ProdottoAlimentare(105,4.0,1,11,2025));
    venditori[1]->aggiungiProdotto(new ProdottoPerBambini(204,30,"6-9"));
    venditori[1]->aggiungiProdotto(new ProdottoAlimentare(106,9.9,15,8,2026));

    venditori[2]->aggiungiProdotto(new ProdottoAlimentare(107,4.5,5,5,2025));
    venditori[2]->aggiungiProdotto(new ProdottoPerBambini(205,18,"6-9"));
    venditori[2]->aggiungiProdotto(new ProdottoPerBambini(206,28,"9-12"));
    venditori[2]->aggiungiProdotto(new ProdottoAlimentare(108,6.3,30,9,2025));
    venditori[2]->aggiungiProdotto(new ProdottoAlimentare(109,8.1,1,1,2026));

    int scelta;
    cout << "Ordine prezzo totale: 1-Crescente 2-Decrescente\n";
    cin >> scelta;

    if(scelta==1) bubbleSortCrescente(venditori,n_v);
    else bubbleSortDecrescente(venditori,n_v);

    for(int i=0;i<n_v;i++) cout << *venditori[i] << "----------------------\n";
    return 0;
}
