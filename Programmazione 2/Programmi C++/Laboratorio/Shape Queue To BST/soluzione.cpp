#include <iostream>
#include <string>

using namespace std;

class Shape{
public:
    virtual double getArea() const = 0;
    virtual void stampa(ostream&s) const = 0;
};

class Rettangolo : public Shape{
private:
    double base;
    double altezza;
public:
    Rettangolo(double base = 0.0, double altezza = 0.0) : base(base), altezza(altezza) {}
    double getArea() const override{
        return base * altezza;
    }
    void stampa(ostream&s) const override{
        s << "Base: " << base << ", Altezza: " << altezza << ", Area: " << getArea() << endl;
    }
};

class Triangolo : public Shape{
private:
    double base;
    double altezza;
public:
    Triangolo(double base = 0.0, double altezza = 0.0) : base(base), altezza(altezza) {}
    double getArea() const override{
        return (base * altezza) / 2;
    }
    void stampa(ostream&s) const override{
        s << "Base: " << base << ", Altezza: " << altezza << ", Area: " << getArea() << endl;
    }
};

class Cerchio : public Shape{
private:
    double raggio;
public:
    Cerchio(double raggio = 0.0) : raggio(raggio) {}
    double getArea() const override{
        return raggio * raggio * 3.14;
    }
    void stampa(ostream&s) const override{
        s << "Raggio: " << raggio << ", Area: " << getArea() << endl;
    }
};

template <typename T>
class Queue;

template <typename T>
ostream& operator<<(ostream&s, const Queue<T>&queue);

template <typename T>
struct Nodo{
    T valore;
    Nodo<T>*nextptr;
    Nodo(T val) : valore(val), nextptr(nullptr) {}
    template <typename U>
    friend ostream& operator<<(ostream&s, const Queue<U>&queue);
};

template <typename T>
class Queue{
private:
    Nodo<T>*head;
    Nodo<T>*tail;
public:
    Queue() : head(nullptr), tail(nullptr) {}
    ~Queue();
    void enqueue(T val);
    bool isEmpty() const;
    T dequeue();
    template <typename U>
    friend ostream& operator<<(ostream&s, const Queue<U>&queue);
};

template <typename T>
Queue<T>::~Queue() {
    while(!isEmpty()) dequeue();
}

template <typename T>
void Queue<T>::enqueue(T val) {
    Nodo<T>*nuovo = new Nodo(val);
    if(!tail) {
        head = tail = nuovo;
    } else {
        tail->nextptr = nuovo;
        tail = nuovo;
    }
}

template <typename T>
T Queue<T>::dequeue() {
    Nodo<T>*temp = head;
    T val = temp->valore;
    head = head->nextptr;
    if(head == nullptr) tail = nullptr;
    delete temp;
    return val;
}

template <typename T>
bool Queue<T>::isEmpty() const {
    return head == nullptr;
}

template <typename T>
ostream& operator<<(ostream&s, const Queue<T>&queue) {
    if(queue.isEmpty()) return s;
    Nodo<T>*corrente=queue.head;
    while(corrente!=nullptr) {
        corrente->valore->stampa(s);
        corrente=corrente->nextptr;
    }
    return s;
}

template <typename T>
struct BSTNode{
    T valore;
    BSTNode*left;
    BSTNode*right;
    BSTNode*parent;
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
    BSTNode<T>*getRoot() {return root;}
    void inserisci(T val);
    template <typename U>
    void estraiInBST(Queue<U>&queue);
    void inOrder(BSTNode<T>*nodo, ostream&s);
    void stampa(ostream&s);
    BSTNode<T>*Trapianta(BSTNode<T>*dest, BSTNode<T>*src);
    void rimuovi(BSTNode<T>*p);
    BSTNode<T>*min(BSTNode<T>*nodo);
    void rimuoviArea(BSTNode<T>*nodo, double area_min);
};

template <typename T>
BST<T>::~BST() {
    distruttore(root);
}

template <typename T>
void BST<T>::distruttore(BSTNode<T>*nodo) {
    if(!nodo) return;
    distruttore(nodo->left);
    distruttore(nodo->right);
    delete nodo->valore;
    delete nodo;
}

template <typename T>
void BST<T>::rimuoviArea(BSTNode<T>*nodo, double area_min) {
    if(!nodo) return;
    rimuoviArea(nodo->left, area_min);
    rimuoviArea(nodo->right, area_min);
    if(nodo->valore->getArea() < area_min) rimuovi(nodo);
}

template <typename T>
BSTNode<T>*BST<T>::Trapianta(BSTNode<T>*dest, BSTNode<T>*src) {
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
void BST<T>::rimuovi(BSTNode<T>*p){
    if(!p) return;
    if(p->left == nullptr && p->right == nullptr){
        if(p->parent == nullptr)
            root = nullptr;
        else if(p->parent->left == p)
            p->parent->left = nullptr;
        else
            p->parent->right = nullptr;
    }
    else if(p->left == nullptr)
        Trapianta(p, p->right);
    else if(p->right == nullptr)
        Trapianta(p, p->left);
    else {
        BSTNode<T>*next = min(p->right);
        if(next->parent !=p){
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
BSTNode<T>*BST<T>::min(BSTNode<T>*nodo) {
    while(nodo && nodo->left) nodo=nodo->left;
    return nodo;
}

template <typename T>
void BST<T>::stampa(ostream&s){
    inOrder(root, s);
}

template <typename T>
void BST<T>::inOrder(BSTNode<T>*nodo, ostream&s) {
    if(!nodo) return;
    inOrder(nodo->left, s);
    nodo->valore->stampa(s);
    inOrder(nodo->right, s);
}

template <typename T>
template <typename U>
void BST<T>::estraiInBST(Queue<U>&queue){
    while(!queue.isEmpty()){
        T val = queue.dequeue();
        inserisci(val);
    }
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
    while(corrente!=nullptr) {
        precedente = corrente;
        if(val->getArea() < corrente->valore->getArea()) {
            corrente=corrente->left;
        } else {
            corrente=corrente->right;
        }
    }

    nuovo->parent = precedente;

    if(val->getArea() < precedente->valore->getArea()) {
        precedente->left = nuovo;
    } else {
        precedente->right = nuovo;
    }
}

int main(void) {
    Queue<Rettangolo*>rettangolo;
    Queue<Triangolo*>triangolo;
    Queue<Cerchio*>cerchio;
    int n = 0, scelta=0;
    cout << "Inserisci il numero di figure: ";
    cin >> n;
    for(int i=0;i<n;i++) {
        double altezza = 0.0;
        double base = 0.0;
        double raggio = 0.0;
        cout << "Menù: Seleziona la figura (1.Rettangolo, 2.Triangolo, 3.Cerchio) (iterazione N: "<< i+1 <<"): ";
        cin >> scelta;
        switch(scelta) {
            case 1:{
                cout << "Inserisci la base del rettangolo: ";
                cin >> base;
                cout << "Inserisci l'altezza del rettangolo: ";
                cin >> altezza;
                rettangolo.enqueue(new Rettangolo(base, altezza));
                break;
            }
            case 2:{
                cout << "Inserisci la base del triangolo: ";
                cin >> base;
                cout << "Inserisci l'altezza del triangolo: ";
                cin >> altezza;
                triangolo.enqueue(new Triangolo(base, altezza));
                break;
            }
            case 3:{
                cout << "Inserisci il raggio: ";
                cin >> raggio;
                cerchio.enqueue(new Cerchio(raggio));
                break;
            }
        }
    }

    cout << "Coda di Rettangoli:" << endl;
    cout << rettangolo;
    cout << "Coda di Triangolo:" << endl;
    cout << triangolo;
    cout << "Coda di Cerchi:" << endl;
    cout << cerchio;

    BST<Shape*>tree;
    tree.estraiInBST(rettangolo);
    tree.estraiInBST(triangolo);
    tree.estraiInBST(cerchio);
    cout << "Le aree estratte nel BST" << endl;
    tree.stampa(cout);

    double area_min = 0.0;
    cout << "Inserisci un'area inferiore per eliminare le figure geometriche: ";
    cin >> area_min;
    tree.rimuoviArea(tree.getRoot(), area_min);
    cout << "Dopo la rimozione" << endl;
    tree.stampa(cout);
    return 0;
}