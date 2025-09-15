#include <iostream>
#include <string>

using namespace std;

class Animale{
private:
    string nome;
    string razza;
    int eta;
public:
    Animale(const string&nome = "", const string&razza = "", int eta = 0) : nome(nome), razza(razza), eta(eta) {}
    string getNome() const {return nome;}
    string getRazza() const {return razza;}
    int getEta() const {return eta;}
    virtual void print() const = 0;
    virtual void verso() const = 0;
};

class Cane : public Animale{
public:
    Cane(const string &nome = "", const string &razza = "", int eta = 0) : Animale(nome, razza, eta) {}
    void print() const override {
        cout << getNome() << " è un cane di razza " << getRazza() << " di " << getEta() << " anni" << endl;
    }
    void verso() const override {
        cout << "Il verso di " << getNome() << " è bau!" << endl;
    }
};

class Gatto : public Animale{
public:
    Gatto(const string &nome = "", const string &razza = "", int eta = 0) : Animale(nome, razza, eta) {}
    void print() const override {
        cout << getNome() << " è un gatto di razza " << getRazza() << " di " << getEta() << " anni" << endl;
    }
    void verso() const override {
        cout << "Il verso di " << getNome() << " è miao!" << endl;
    }
};


struct BSTNode{
    Animale*animale;
    BSTNode*left;
    BSTNode*right;
    BSTNode*parent;
    BSTNode(Animale*a) : animale(a), left(nullptr), right(nullptr), parent(nullptr) {}
};

class BST{
private:
    BSTNode*root;
    int dimensione;
    static const int max_nodi = 10;
public:
    BST() : root(nullptr), dimensione(0) {}
    ~BST();
    void distruttore(BSTNode*nodo);
    void inserisci(Animale*a);
    void print();
    void inOrder(BSTNode*nodo);
    BSTNode*cerca(const string&nome);
};




void BST::distruttore(BSTNode*nodo) {
    if(!nodo) return;
    distruttore(nodo->left);
    distruttore(nodo->right);
    delete nodo->animale;
    delete nodo;
}

BST::~BST() {
    distruttore(root);
}

void BST::inOrder(BSTNode*nodo) {
    if(!nodo) return;
    inOrder(nodo->left);
    nodo->animale->print();
    inOrder(nodo->right);
}

void BST::print() {
    inOrder(root);
}

BSTNode*BST::cerca(const string &nome) {
    BSTNode*corrente=root;
    while(corrente!=nullptr) {
        if(corrente->animale->getNome() == nome) 
            return corrente;
        else if(nome < corrente->animale->getNome())
            corrente=corrente->left;
        else
            corrente=corrente->right;
    }
    return nullptr;
}

void BST::inserisci(Animale*a) {
    if(dimensione>=max_nodi){
        cout << "Limite raggiunti max 10" << endl;
        return;
    }

    BSTNode*nuovo = new BSTNode(a);
    if(!root){
        root = nuovo;
        return;
    }

    BSTNode*corrente=root;
    BSTNode*precedente=nullptr;

    while(corrente!=nullptr) {
        precedente = corrente;
        if(a->getNome() < corrente->animale->getNome()){
            corrente=corrente->left;
        } else {
            corrente=corrente->right;
        }
    }

    nuovo->parent = precedente;
    if(a->getNome() < precedente->animale->getNome())
        precedente->left = nuovo;
    else
        precedente->right = nuovo;
    dimensione++;
}
 
int main(void) {
    BST tree;
    tree.inserisci(new Cane("Fido", "Labrador", 3));
    tree.inserisci(new Gatto("Luna", "Siamese", 2));
    tree.inserisci(new Cane("Rex", "Pastore Tedesco", 5));
    tree.inserisci(new Gatto("Leo", "Persiano", 4));
    tree.inserisci(new Cane("Milo", "Beagle", 1));
    tree.inserisci(new Gatto("Nala", "Maine Coon", 3));

    cout << "Inserisci il nome di un animale da cercare: ";
    string nome;
    cin >> nome;

    BSTNode*trovato = tree.cerca(nome);
    if(trovato) {
        trovato->animale->print();
        trovato->animale->verso();
    } else {
        cout << "Nessun animale con questo nome trovato nell'albero. " << endl;
    }
    return 0;
}