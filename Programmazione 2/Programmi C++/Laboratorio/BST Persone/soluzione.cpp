#include <iostream>
#include <string>
using namespace std;

class Persona{
private:
    string nome;
    string cognome;
    int eta;
    string categoria;
public:
    Persona(const string& nome = "", const string &cognome = "", int eta = 0, const string &categoria = "") : nome(nome), cognome(cognome), eta(eta), categoria(categoria) {}
    string getNome() const {return nome;}
    string getCognome() const {return cognome;}
    int getEta() const {return eta;}
    virtual string getCategoria() const = 0;
    virtual void print() const = 0;
};

class Studente : public Persona {
public:
    Studente(const string& nome = "", const string &cognome = "", int eta = 0, const string &categoria = "") : Persona(nome, cognome, eta, categoria) {}
    void print() const override {
        cout << getNome() << " " << getCognome() << " (" << getEta() << ")" << " " << getCategoria() << endl; 
    }
    string getCategoria() const override{
        return "Studente";
    }
};

class Lavoratore : public Persona {
public:
    Lavoratore(const string& nome = "", const string &cognome = "", int eta = 0, const string &categoria = "") : Persona(nome, cognome, eta, categoria) {}
    void print() const override {
        cout << getNome() << " " << getCognome() << " (" << getEta() << ")" << " " << getCategoria() << endl; 
    }
    string getCategoria() const override{
        return "Lavoratore";
    }
};

class Pensionato : public Persona {
public:
    Pensionato(const string& nome = "", const string &cognome = "", int eta = 0, const string &categoria = "") : Persona(nome, cognome, eta, categoria) {}
    void print() const override {
        cout << getNome() << " " << getCognome() << " (" << getEta() << ")" << " " << getCategoria() << endl; 
    }
    string getCategoria() const override{
        return "Pensionato";
    }
};

struct BSTNode{
    Persona*persona;
    BSTNode*left;
    BSTNode*right;
    BSTNode*parent;
    BSTNode(Persona*p) : persona(p), left(nullptr), right(nullptr), parent(nullptr) {}
};

class BST{
private:
    BSTNode*root;
public:
    BST() : root(nullptr) {}
    ~BST();
    BSTNode*getRoot() {return root;}
    void distruttore(BSTNode*nodo);
    void inserisci(Persona*p);
    void print();
    void inOrder(BSTNode*nodo);
    void calcoloEta(BSTNode*nodo, double &sommaStud, int &countStud, double &sommaLav, int &countLav, double &sommaPens, int &countPens);
    void printEta(BSTNode*nodo);
}; 



void BST::calcoloEta(BSTNode*nodo, double &sommaStud, int &countStud, double &sommaLav, int &countLav, double &sommaPens, int &countPens){
    if(!nodo) return;
    if(dynamic_cast<Studente*>(nodo->persona)){
        sommaStud+=nodo->persona->getEta();
        countStud++;
    } else if(dynamic_cast<Lavoratore*>(nodo->persona)) {
        sommaLav+=nodo->persona->getEta();
        countLav++;
    } else if(dynamic_cast<Pensionato*>(nodo->persona)) {
        sommaPens+=nodo->persona->getEta();
        countPens++;
    }
    calcoloEta(nodo->left, sommaStud, countStud, sommaLav, countLav, sommaPens, countPens);
    calcoloEta(nodo->right, sommaStud, countStud, sommaLav, countLav, sommaPens, countPens);
}

void BST::printEta(BSTNode*nodo) {
    double sommaStud = 0;
    int countStud = 0;
    double sommaLav = 0;
    int countLav = 0;
    double sommaPens = 0;
    int countPens = 0;
    calcoloEta(nodo, sommaStud, countStud, sommaLav, countLav, sommaPens, countPens);
    if(countStud > 0)
        sommaStud/=countStud;
    if(countLav > 0)
        sommaLav/=countLav;
    if(countPens > 0)
        sommaPens/=countPens;
    cout << "Età media studenti: " << sommaStud << endl;
    cout << "Età media lavoratori: " << sommaLav << endl;
    cout << "Età media pensionato: " << sommaPens << endl;
}

BST::~BST() {
    distruttore(root);
}

void BST::distruttore(BSTNode*nodo) {
    if(!nodo) return;
    distruttore(nodo->left);
    distruttore(nodo->right);
    delete nodo->persona;
    delete nodo;
}

void BST::inserisci(Persona*p) {
    BSTNode*nuovo = new BSTNode(p);
    if(!root) {
        root = nuovo;
        return;
    }
    BSTNode*corrente=root;
    BSTNode*precedente=nullptr;
    while(corrente!=nullptr) {
        precedente = corrente;
        if(p->getEta() < corrente->persona->getEta()){
            corrente=corrente->left;
        } else {
            corrente=corrente->right;
        }
    }

    nuovo->parent = precedente;
    if(p->getEta() < precedente->persona->getEta()){
        precedente->left = nuovo;
    } else {
        precedente->right = nuovo;
    }
}

void BST::inOrder(BSTNode*nodo) {
    if(!nodo) return;
    inOrder(nodo->left);
    nodo->persona->print();
    inOrder(nodo->right);
}

void BST::print() {
    inOrder(root);
}

int main(void) {
    BST tree;
    int N = 6, x = 0;
    for(int i=0;i<N;i++) {
        cout << "Menù: Selezionare la categoria della persona\n(1. Studente, 2. Lavoratore, 3. Pensionato): ";
        cin >> x;
        string nome = "", cognome = "";
        int eta = 0;
        switch(x) {
            case 1: {
                cout << "Inserisci il nome dello studente: ";
                cin >> nome;
                cout << "Inserisci il cognome dello studente: ";
                cin >> cognome;
                do{
                    cout << "Inserisci l'età dello studente (5-30): ";
                    cin >> eta;
                } while(eta < 5 || eta > 30);
                tree.inserisci(new Studente(nome, cognome, eta));
                break;
            }
            case 2: {
                cout << "Inserisci il nome del lavoratore: ";
                cin >> nome;
                cout << "Inserisci il cognome del lavoratore: ";
                cin >> cognome;
                do{
                    cout << "Inserisci l'età del lavoratore (20-70): ";
                    cin >> eta;
                }while(eta < 20 || eta > 70);
                tree.inserisci(new Lavoratore(nome, cognome, eta));
                break;
            }
            case 3: {
                cout << "Inserisci il nome del pensionato: ";
                cin >> nome;
                cout << "Inserisci il cognome del pensionato: ";
                cin >> cognome;
                do{
                    cout << "Inserisci l'età del pensionato (65-95): ";
                    cin >> eta;
                }while(eta < 65 || eta > 95);
                tree.inserisci(new Pensionato(nome, cognome, eta));
                break;
            }
        }
    }
    
    cout << "Albero di oggetti Persona:" << endl;
    tree.print();
    cout << "===Medie delle età===" << endl;
    tree.printEta(tree.getRoot());
    return 0;
}