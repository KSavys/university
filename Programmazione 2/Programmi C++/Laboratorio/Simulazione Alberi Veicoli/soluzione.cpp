#include <iostream>
#include <string>

using namespace std;

class Veicolo{
private:
    string targa;
    string nome;
    int anno;
    string marca;
public:
    Veicolo(const string &targa = "", const string &nome = "", int anno = 0, const string &marca = "") : targa(targa), nome(nome), anno(anno), marca(marca) {}
    string getTarga() const {return targa;}
    string getNome() const {return nome;}
    int getAnno() const {return anno;}
    string getMarca() const {return marca;}
    virtual void stampa() const = 0;
};

class Auto : public Veicolo{
private:
    int numero_porte;
    int cilindrata;
public:
    Auto(const string &targa = "", const string &nome = "", int anno = 0, const string &marca = "", int numero_porte = 0, int cilindrata = 0) : Veicolo(targa, nome, anno, marca), numero_porte(numero_porte), cilindrata(cilindrata) {}
    void stampa() const override{
        cout << "Auto: " << endl << "Targa: " << getTarga() << endl << "Marca: " << getMarca() << endl << "Cilindrata: " << cilindrata << endl << "Nome modello: " << getNome() << endl << "Anno di fabbricazione: " << getAnno() << endl << "Numero di porte: " << numero_porte << endl;
    }
};

class Moto : public Veicolo{
private:
    string tipo_moto;
    int cilindrata;
public:
    Moto(const string &targa = "", const string &nome = "", int anno = 0, const string &marca = "", const string &tipo_moto = "", int cilindrata = 0) : Veicolo(targa, nome, anno, marca), tipo_moto(tipo_moto), cilindrata(cilindrata) {}
    void stampa() const override{
        cout << "Moto: " << endl << "Targa: " << getTarga() << endl << "Marca: " << getMarca() << endl << "Cilindrata: " << cilindrata << endl << "Nome modello: " << getNome() << endl << "Anno di fabbricazione: " << getAnno() << endl << "Tipo di moto: " << tipo_moto << endl;
    }
};

struct BSTNode{
    Veicolo*veicolo;
    BSTNode*left;
    BSTNode*right;
    BSTNode*parent;
    BSTNode(Veicolo*veicolo) : veicolo(veicolo), left(nullptr), right(nullptr), parent(nullptr) {}
};

class BST{
private:
    BSTNode*root;
public:
    BST() : root(nullptr) {}
    ~BST();
    void distruttore(BSTNode*nodo);
    void inserisci(Veicolo*veicolo);
    void elimina(BSTNode*p);
    BSTNode*Trapianta(BSTNode*dest, BSTNode*src);
    BSTNode*cerca(string targa);
    void stampa();
    void inOrder(BSTNode*nodo);
    void preOrder(BSTNode*nodo);
    void verifica_stampa();
    BSTNode*Min(BSTNode*nodo);
    BSTNode*getRoot() {return root;}
};

BSTNode*BST::Min(BSTNode*nodo) {
    while(nodo && nodo->left) nodo = nodo->left;
    return nodo;
}

void BST::verifica_stampa(){
    preOrder(root);
}

BSTNode*BST::cerca(string targa) {
    BSTNode*corrente=root;
    while(corrente!=nullptr) {
        if(corrente->veicolo->getTarga() == targa)
            return corrente;
        else if(targa < corrente->veicolo->getTarga())
            corrente=corrente->left;
        else
            corrente=corrente->right;
    }
    return nullptr;
}

BSTNode*BST::Trapianta(BSTNode*dest, BSTNode*src){
    if(dest->parent == nullptr)
        root = src;
    else if(dest == dest->parent->left)
        dest->parent->left = src;
    else
        dest->parent->right = src;
    if(src!=nullptr)
        src->parent = dest->parent;
    return dest;
}

void BST::elimina(BSTNode*p){
    if(!p) return;
    if(p->left == nullptr && p->right == nullptr){
        if(p->parent == nullptr)
            root = nullptr;
        else if(p == p->parent->left)
            p->parent->left = nullptr;
        else
            p->parent->right = nullptr;
    }
    else if(p->left == nullptr)
        Trapianta(p, p->right);
    else if(p->right == nullptr)
        Trapianta(p, p->left);
    
    else{
        BSTNode*next = Min(p->right);
        if(next->parent != p) {
            Trapianta(next, next->right);
            next->right = p->right;
            if(next->right) next->right->parent = next;
        }
        Trapianta(p, next);
        next->left = p->left;
        if(next->left) next->left->parent = next;
    }
    delete p->veicolo;
    delete p;
}

void BST::preOrder(BSTNode*nodo) {
    if(!nodo) return;
    nodo->veicolo->stampa();
    preOrder(nodo->left);
    preOrder(nodo->right);
}

BST::~BST(){
    distruttore(root);
}

void BST::distruttore(BSTNode*nodo) {
    if(!nodo) return;
    distruttore(nodo->left);
    distruttore(nodo->right);
    delete nodo->veicolo;
    delete nodo;
}

void BST::stampa() {
    inOrder(root);
}

void BST::inOrder(BSTNode*nodo){
    if(!nodo) return;
    inOrder(nodo->left);
    nodo->veicolo->stampa();
    inOrder(nodo->right);
}

void BST::inserisci(Veicolo*veicolo){
    BSTNode*nuovo = new BSTNode(veicolo);
    if(!root){
        root = nuovo;
        return;
    }
    BSTNode*corrente=root;
    BSTNode*precedente=nullptr;
    while(corrente!=nullptr) {
        precedente = corrente;
        if(veicolo->getTarga() < corrente->veicolo->getTarga())
            corrente=corrente->left;
        else
            corrente=corrente->right;
    }

    nuovo->parent = precedente;
    if(veicolo->getTarga() < precedente->veicolo->getTarga())
        precedente->left = nuovo;
    else
        precedente->right = nuovo;
}



int main(void) {
    BST tree;
    tree.inserisci(new Auto("3", "Ferrari Testarossa", 1984, "Ferrari", 3, 4943));
    tree.inserisci(new Auto("1", "Panda FIRE", 1986, "Fiat", 3, 769));
    tree.inserisci(new Auto("5", "Peugeot 208", 2019, "Peugeot", 5, 1199));
    tree.inserisci(new Moto("4", "YZF-R3", 2014, "Yamaha", "Sportiva", 249));
    tree.inserisci(new Moto("6", "Honda Africa Twin 650", 1983, "Honda", "Enduro", 749));
    BSTNode*trovato = tree.cerca("3");
    if(trovato){
        cout << "Veicolo trovato" << endl;
        tree.elimina(trovato);
    } else {
        cout << "Nessun veicolo trovato per l'eliminazione" << endl;
    }

    trovato = tree.cerca("5");
    if(trovato){
        cout << "Veicolo trovato" << endl;
        tree.elimina(trovato);
    } else {
        cout << "Nessun veicolo trovato per l'eliminazione" << endl;
    }
    tree.verifica_stampa();


    return 0;
}