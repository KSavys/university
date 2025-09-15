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
    Studente(const Studente&s) : matricola(s.matricola), nome(s.nome), cognome(s.cognome), media(s.media) {}
    int getMatricola() const {return matricola;}
    string getNome() const {return nome;}
    string getCognome() const {return cognome;}
    double getMedia() const {return media;}
    void stampa() {
        cout << matricola << ": " << nome << " " << cognome << " - " << "media " << media << endl;
    } 
};

struct BSTNode{
    Studente*studente;
    BSTNode*left;
    BSTNode*right;
    BSTNode*parent;
    BSTNode(Studente*s) : studente(s), left(nullptr), right(nullptr), parent(nullptr) {}
};

class BST{
private:
    BSTNode*root;
public:
    BST() : root(nullptr) {}
    void inserisci(Studente*s);
    ~BST();
    void stampa();
    BSTNode*getRoot() {return root;}
    void inOrder(BSTNode*nodo);
    BSTNode*Search(int matricola);
    void distruttore(BSTNode*nodo);
};

void BST::distruttore(BSTNode*nodo) {
    if(!nodo) return;
    distruttore(nodo->left);
    distruttore(nodo->right);
    delete nodo->studente;
    delete nodo;
}


BST::~BST() {
    distruttore(root);
}

BSTNode*BST::Search(int matricola) {
    BSTNode*corrente=root;
    while(corrente!=nullptr) {
        if(matricola == corrente->studente->getMatricola()){
            return corrente;
        } else if(matricola < corrente->studente->getMatricola()) {
            corrente=corrente->left;
        } else {
            corrente=corrente->right;
        }
    }
    return nullptr;
}

void BST::inOrder(BSTNode*nodo) {
    if(!nodo) return;
    inOrder(nodo->left);
    nodo->studente->stampa();
    inOrder(nodo->right);
}

void BST::stampa() {
    inOrder(root);
}

void BST::inserisci(Studente*s) {
    BSTNode*nuovo = new BSTNode(s);
    if(!root) {
        root = nuovo;
        return;
    }

    BSTNode*corrente=root;
    BSTNode*precedente=nullptr;

    while(corrente!=nullptr) {
        precedente = corrente;
        if(s->getMatricola() < corrente->studente->getMatricola())
            corrente=corrente->left;
        else
            corrente=corrente->right;
    }

    if(s->getMatricola() < precedente->studente->getMatricola())
        precedente->left = nuovo;
    else
        precedente->right = nuovo;
}

int main(void) {
    BST tree;
    string nome, cognome;
    double media;
    int matricola;
    ifstream file("input.txt");
    if(file.fail()){
        cout << "Errore nell'apertura del file" << endl;
        return -1;
    }
    while(file >> matricola) {
        file.ignore();
        getline(file, nome, ',');
        getline(file, cognome, ',');
        file >> media;
        file.ignore();
        tree.inserisci(new Studente(matricola, nome, cognome, media));
    }
    int mat = 0;
    cout << "Inserisci una matricola: ";
    cin >> mat;

    BSTNode*trovato = tree.Search(mat);
    if(trovato){
        trovato->studente->stampa();
    } else {
        cout << "Nessuna matricola trovata" << endl;
    }
    cout << endl;

    cout << "Albero di oggetti studenti" << endl;
    tree.stampa();

    return 0;
}