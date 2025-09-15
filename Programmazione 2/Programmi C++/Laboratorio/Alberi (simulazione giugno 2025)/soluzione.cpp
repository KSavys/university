#include <iostream>
using namespace std;

struct BSTNode{
    int valore;
    BSTNode*left;
    BSTNode*right;
    BSTNode*parent;
    BSTNode(int v = 0) : valore(v), left(nullptr), right(nullptr), parent(nullptr) {}
};

class BST{
private:
    BSTNode*root;
public:
    BST() : root(nullptr) {}
    ~BST();
    void distruggi(BSTNode*nodo);
    BSTNode*getRoot() {return root;}
    void inserisci(int v);
    void printinOrder(BSTNode*nodo);
    void print();
    BSTNode*max(BSTNode*nodo);
    BSTNode*min(BSTNode*nodo);
    BSTNode*ricerca(int v);
};

void BST::distruggi(BSTNode*nodo) {
    if(!nodo) return;
    distruggi(nodo->left);
    distruggi(nodo->right);
    delete nodo;
}

BST::~BST(){
    distruggi(root);
}

BSTNode*BST::ricerca(int valore) {
    BSTNode*corrente=root;
    while(corrente!=nullptr) {
        if(valore == corrente->valore)
            return corrente;
        else if(valore < corrente->valore)
            corrente=corrente->left;
        else
            corrente=corrente->right;
    }
    return nullptr;
}

BSTNode*BST::max(BSTNode*nodo){
    if(!nodo) return nullptr;
    while(nodo->left != nullptr) nodo=nodo->left;
    return nodo;
}

BSTNode*BST::min(BSTNode*nodo){
    if(!nodo) return nullptr;
    while(nodo->right!=nullptr) nodo=nodo->right;
    return nodo;
}

void BST::print() {
    printinOrder(root);
}

void BST::printinOrder(BSTNode*nodo) {
    if(!nodo) return;
    printinOrder(nodo->left);
    cout << nodo->valore << " ";
    printinOrder(nodo->right);
}

void BST::inserisci(int v) {
    BSTNode*nuovo = new BSTNode(v);
    if(!root){
        root = nuovo;
        return;
    }
    BSTNode*corrente=root;
    BSTNode*precedente=nullptr;

    while(corrente!=nullptr) {
        precedente = corrente;
        if(v < corrente->valore)
            corrente = corrente->left;
        else
            corrente = corrente->right;
    }

    if(v < precedente->valore)
        precedente->left = nuovo;
    else
        precedente->right = nuovo;
}


int main(void) {
    BST tree;
    int x=0;
    cout << "Inserisci un numero intero positivo da inserire nell'albero (-1 per terminare): ";
    cin >> x;
    while(x != -1){
        cout << "Inserisci un numero intero positivo da inserire nell'albero (-1 per terminare): ";
        tree.inserisci(x);
        cin >> x;
    }
    cout << "Elementi dell'albero in ordine crescente:" << endl;
    tree.print();
    cout << endl;
    BSTNode*max = tree.max(tree.getRoot());
    BSTNode*min = tree.min(tree.getRoot());
    cout << "Valore minimo nell'albero: " << max->valore << endl << "Valore massimo nell'albero: " << min->valore << endl;
    cout << endl;
    int d=0;
    cout << "Inserisci un valore da cercare nell'albero: ";
    cin >> d;
    BSTNode*search = tree.ricerca(d);
    if(search){
        cout << "Il valore " << d << " è presente nell'albero" << endl;
    } else {
        cout << "Il valore " << d << " non è presente nell'albero" << endl;
    }

    cout << "Inserisci un valore da cercare nell'albero: ";
    cin >> d;
    search = tree.ricerca(d);
    if(search){
        cout << "Il valore " << d << " è presente nell'albero" << endl;
    } else {
        cout << "Il valore " << d << " non è presente nell'albero" << endl;
    }
    return 0;
}