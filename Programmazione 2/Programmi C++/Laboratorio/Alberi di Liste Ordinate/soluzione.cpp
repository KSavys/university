#include <iostream>
#include <string>

using namespace std;

class Prodotto{
private:
    string nome;
    string id;
    double prezzo;
    string categoria;
public:
    Prodotto(const string &nome = "", const string &id = "", double prezzo = 0.0, const string &categoria = "") : nome(nome), id(id), prezzo(prezzo), categoria(categoria) {}
    virtual ~Prodotto() {}
    string getNome() const {return nome;}
    string getId() const {return id;}
    double getPrezzo() const {return prezzo;}
    string getCategoria() const {return categoria;}
};

struct Nodo{
    Prodotto*prodotto;
    Nodo*nextptr;
    Nodo(Prodotto*prodotto) : prodotto(prodotto), nextptr(nullptr) {}
};

class List{
private:
    Nodo*head;
public:
    List() : head(nullptr) {}
    ~List();
    void insert(Prodotto*prodotto);
    void stampa();
};

void List::stampa(){
    Nodo*curr = head;
    while(curr) {
        cout << "  - " << curr->prodotto->getNome() << " [ID=" << curr->prodotto->getId() << ", Prezzo=" << curr->prodotto->getPrezzo() << ", Categoria=" << curr->prodotto->getCategoria() << "]" << endl;
        curr = curr->nextptr;
    }
}

List::~List(){
    Nodo*corrente=head;
    while(corrente!=nullptr){
        Nodo*temp = corrente;
        corrente=corrente->nextptr;
        delete temp->prodotto;
        delete temp;
    }
}

void List::insert(Prodotto*prodotto){
    Nodo*nuovo = new Nodo(prodotto);
    if(!head || prodotto->getId() < head->prodotto->getId()){
        nuovo->nextptr = head;
        head = nuovo;
        return;
    }

    Nodo*corrente=head;
    while(corrente->nextptr && corrente->nextptr->prodotto->getId() < prodotto->getId()){
        corrente=corrente->nextptr;
    }
    nuovo->nextptr = corrente->nextptr;
    corrente->nextptr = nuovo;
}

struct BSTNode{
    List prodotto;
    double prezzo;
    BSTNode*left;
    BSTNode*right;
    BSTNode*parent;
    BSTNode(double prezzo) : prezzo(prezzo), left(nullptr), right(nullptr), parent(nullptr) {}
};

class BST{
private:
    BSTNode*root;
public:
    BST() : root(nullptr) {}
    ~BST();
    void distruttore(BSTNode*nodo);
    void inserisci(Prodotto*prodotto);
    void stampa();
    void inOrder(BSTNode*nodo);
};

BST::~BST(){
    distruttore(root);
}

void BST::distruttore(BSTNode*nodo){
    if(!nodo) return;
    distruttore(nodo->left);
    distruttore(nodo->right);
    delete nodo;
}

void BST::inserisci(Prodotto*prodotto) {
    BSTNode*nuovo = new BSTNode(prodotto->getPrezzo());
    nuovo->prodotto.insert(prodotto);
    if(!root){
        root = nuovo;
        return;
    }

    BSTNode*corrente=root;
    BSTNode*precedente=nullptr;
    while(corrente!=nullptr){
        precedente=corrente;
        if(prodotto->getPrezzo() == corrente->prezzo){
            corrente->prodotto.insert(prodotto);
            return;
        }
        else if(prodotto->getPrezzo() < corrente->prezzo)
            corrente=corrente->left;
        else
            corrente=corrente->right;
    }

    nuovo->parent = precedente;
    if(prodotto->getPrezzo() < precedente->prezzo)
        precedente->left = nuovo;
    else
        precedente->right = nuovo;
}

void BST::inOrder(BSTNode*nodo){
    if(!nodo) return;
    inOrder(nodo->left);
    cout << "Prodotti con prezzo = " << nodo->prezzo << ":" << endl;
    nodo->prodotto.stampa();
    cout << endl;
    inOrder(nodo->right);
}

void BST::stampa(){
    inOrder(root);
}
int main(void){
    BST tree;
    tree.inserisci(new Prodotto("Prod1", "A1", 10.0, "CategoriaX"));
    tree.inserisci(new Prodotto("Prod2", "A3", 10.0, "CategoriaX"));
    tree.inserisci(new Prodotto("Prod3", "B2", 5.0, "CategoriaY"));
    tree.inserisci(new Prodotto("Prod4", "C1", 20.0, "CategoriaZ"));
    tree.stampa();
    return 0;
}