#include <iostream>
using namespace std;

class Shape{
public:
    virtual double getArea() const = 0;
    virtual void stampa() const = 0;
    virtual ~Shape() = default;
};


class Rettangolo : public Shape{
private:
    double base, altezza;
public:
    Rettangolo(double base = 0.0, double altezza = 0.0) : base(base), altezza(altezza) {}
    double getArea() const override{
        return base * altezza;
    }
    void stampa() const override{
        cout << "Base: " << base << ", Altezza: " << altezza <<", Area: " << getArea() << endl;
    }
};

class Triangolo : public Shape{
private:
    double base, altezza;
public:
    Triangolo(double base = 0.0, double altezza = 0.0) : base(base), altezza(altezza) {}
    double getArea() const override{
        return (base * altezza) / 2;
    }
    void stampa() const override{
        cout << "Base: " << base << ", Altezza: " << altezza <<", Area: " << getArea() << endl;
    }
};

class Cerchio : public Shape{
private:
    double raggio;
public:
    Cerchio(double raggio = 0.0) : raggio(raggio) {}
    double getArea() const override{
        return 3.14 * raggio * raggio;
    }
    void stampa() const override{
        cout << "Raggio: " << raggio << ", Area: " << getArea() << endl;
    }
};

template <typename T>
struct BSTNode{
    T valore;
    BSTNode<T>*left;
    BSTNode<T>*right;
    BSTNode<T>*parent;
    BSTNode(T val) : valore(val), left(nullptr), right(nullptr), parent(nullptr) {}
    
};

template <typename T>
class BST{
private:
    BSTNode<T>*root;
public:
    BST() : root(nullptr) {}
    ~BST();
    void distruttore(BSTNode<T>*nodo);    
    void inserisci(T val);
    void stampa();
    void inOrder(BSTNode<T>*nodo);
    BSTNode<T>*Min(BSTNode<T>*nodo);
    BSTNode<T>*Trapianta(BSTNode<T>*dest, BSTNode<T>*src);
    void rimuovi(BSTNode<T>*p);
    BSTNode<T>*getRoot(){return root;}
    void rimuoviArea(BSTNode<T>*nodo, double area_min);
    template <typename U>
    void unisciBST(BSTNode<U>*nodo, BST<Shape*>*dest);
    
    
};

template <typename T>
template <typename U>
void BST<T>::unisciBST(BSTNode<U>*nodo, BST<Shape*>*dest){
    if(!nodo) return;
    unisciBST(nodo->left, dest);
    dest->inserisci(nodo->valore);
    unisciBST(nodo->right, dest);
}

template <typename T>
void BST<T>::rimuoviArea(BSTNode<T>* nodo, double area_min){
    if(!nodo) return;

    BSTNode<T>* left = nodo->left;    
    BSTNode<T>* right = nodo->right;

    if(nodo->valore->getArea() < area_min)
        rimuovi(nodo);

    rimuoviArea(left, area_min);
    rimuoviArea(right, area_min);
}
template <typename T>
void BST<T>::rimuovi(BSTNode<T>*p) {
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
        BSTNode<T>*next = Min(p->right);
        if(next->parent!=p) {
            Trapianta(next, next->right);
            next->right = p->right;
            if(next->right) next->right->parent = next;
        }
        Trapianta(p, next);
        next->left = p->left;
        if(next->left) next->left->parent = next;
    }
    delete p->valore;
    delete p;
}

template <typename T>
BSTNode<T>*BST<T>::Trapianta(BSTNode<T>*dest, BSTNode<T>*src){
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

template <typename T>
BSTNode<T>*BST<T>::Min(BSTNode<T>*nodo) {
    while(nodo && nodo->left) nodo = nodo->left;
    return nodo;
}

template <typename T>
BST<T>::~BST() {
    distruttore(root);
}

template <typename T>
void BST<T>::distruttore(BSTNode<T>*nodo) {
    if(!nodo) return;
    distruttore(nodo->left);
    distruttore(nodo->right);
    delete nodo;
}

template <typename T>
void BST<T>::inserisci(T val) {
    BSTNode<T>*nuovo = new BSTNode<T>(val);
    if(!root) {
        root = nuovo;
        return;
    }
    BSTNode<T>*corrente=root;
    BSTNode<T>*precedente=nullptr;
    while(corrente!=nullptr){
        precedente = corrente;
        if(val->getArea() < corrente->valore->getArea())
            corrente=corrente->left;
        else
            corrente=corrente->right;
    }

    if(val->getArea() < precedente->valore->getArea())
        precedente->left = nuovo;
    else
        precedente->right = nuovo;
}

template <typename T>
void BST<T>::inOrder(BSTNode<T>*nodo) {
    if(!nodo) return;
    inOrder(nodo->left);
    nodo->valore->stampa();
    inOrder(nodo->right);
}

template <typename T>
void BST<T>::stampa(){
    inOrder(root);
}

int main(void) {
    BST<Rettangolo*>rettangolo;
    BST<Triangolo*>triangolo;
    BST<Cerchio*>cerchio;
    int n=0, scelta=0;
    cout << "Insersci n Shape: ";
    cin >> n;
    for(int i=0;i<n;i++) {
        double base = 0.0, altezza = 0.0, raggio = 0.0;
        cout << "Menù: selezionare la figura (1. Rettangolo, 2. Triangolo, 3. Cerchio) [Iterazione N: "<< i + 1 <<"]: ";
        cin >> scelta;
        switch(scelta){
            case 1:{
                cout << "Inserisci la base del rettangolo: ";
                cin >> base;
                cout << "Inserisci l'altezza del rettangolo: ";
                cin >> altezza;
                rettangolo.inserisci(new Rettangolo(base, altezza));
                break;
            }
            case 2:{
                cout << "Inserisci la base del triangolo: ";
                cin >> base;
                cout << "Inserisci l'altezza del triangolo: ";
                cin >> altezza;
                triangolo.inserisci(new Triangolo(base, altezza));
                break;
            }
            case 3:{
                cout << "Inserisci il raggio del cerchio: ";
                cin >> raggio;
                cerchio.inserisci(new Cerchio(raggio));
                break;
            }
        }
    }
    cout << endl;
    cout << "Albero di oggetti rettangoli:" << endl;
    rettangolo.stampa();
    cout << endl;
    cout << "Albero di oggetti triangoli:" << endl;
    triangolo.stampa();
    cout << endl;
    cout << "Albero di oggetti cerchi:" << endl;
    cerchio.stampa();
    cout << endl;

    double area_min = 0.0;
    cout << "Inserisci un valore di un'area inferiore: ";
    cin >> area_min;

    rettangolo.rimuoviArea(rettangolo.getRoot(), area_min);
    triangolo.rimuoviArea(triangolo.getRoot(), area_min);
    cerchio.rimuoviArea(cerchio.getRoot(), area_min);
    cout << endl;
    cout << "Dopo la rimozione:" << endl;

    cout << endl;
    cout << "Albero di oggetti rettangoli:" << endl;
    rettangolo.stampa();
    cout << endl;
    cout << "Albero di oggetti triangoli:" << endl;
    triangolo.stampa();
    cout << endl;
    cout << "Albero di oggetti cerchi:" << endl;
    cerchio.stampa();
    cout << endl;

    BST<Shape*>shape;
    shape.unisciBST(rettangolo.getRoot(), &shape);
    shape.unisciBST(triangolo.getRoot(), &shape);
    shape.unisciBST(cerchio.getRoot(), &shape);

    cout << endl << "Albero unificato di tutte le Shape:" << endl;
    shape.stampa();
    return 0;
}