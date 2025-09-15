#include <iostream>
using namespace std;

//struttura base del nodo
template <typename T>
struct BSTNode{
    T val;
    BSTNode *left; //figlio sinistro
    BSTNode *right; //figlio destro
    BSTNode *parent; //padre

    BSTNode(T v) : val(v), left(nullptr), right(nullptr), parent(nullptr) {}
    T getVal() const {return val;}
};

template <typename T>
class BST{
private:
    BSTNode<T>*root; //radice dell'albero
public:
    BST() : root(nullptr) {}
    BSTNode<T>*getRoot() const {
        return root;
    }
    ~BST();
    BST<T>& insert(T val);
    void printInOrder(BSTNode<T>*nodo, ostream&s) const;
    void printPreOrder(BSTNode<T>*nodo, ostream&s) const;
    BSTNode<T>*ricerca(T val);
    BSTNode<T>*ricerca(T val, BSTNode<T>*nodo);
    BSTNode<T>*Min(BSTNode<T>*p = nullptr);
    BSTNode<T>*Max(BSTNode<T>*p = nullptr);
    BSTNode<T>*next(BSTNode<T>*p);
    BSTNode<T>*Trapianta(BSTNode<T>*dest, BSTNode<T>*src);
    void Rimuovi(BSTNode<T>*p);
    void Delete(BSTNode<T>*p);
};

template <typename T>
BST<T>& BST<T>::insert(T val) {
    BSTNode<T>*corrente = root;
    BSTNode<T>*precedente = NULL;

    while(corrente!=NULL) {
        precedente = corrente;
        if(val < corrente->val)
            corrente = corrente->left;
        else
            corrente = corrente->right;
    }
    BSTNode<T>*nuovo = new BSTNode<T>(val);
    nuovo->parent = precedente;
    if(precedente==NULL)
        root = nuovo;
    else if (val < precedente->val)
        precedente->left = nuovo;
    else
        precedente->right = nuovo;
    return *this;
}

template <typename T>
void BST<T>::printInOrder(BSTNode<T>* nodo, ostream&s) const {
    if(nodo == nullptr) return;
    printInOrder(nodo->left, s);
    s << nodo->val << " ";
    printInOrder(nodo->right, s);
}

template <typename T>
void BST<T>::printPreOrder(BSTNode<T>*nodo, ostream&s) const {
    if(nodo != NULL) {
        s << nodo->getVal() << " ";
        printPreOrder(nodo->left, s);
        printPreOrder(nodo->right, s);
    }
}

template <typename T>
BSTNode<T>* BST<T>::ricerca(T val) {
    return ricerca(val, root);
}

template <typename T>
BSTNode<T>* BST<T>::ricerca(T val, BSTNode<T>* nodo) {
    if(nodo == nullptr || val == nodo->val)
        return nodo;
    else if(val < nodo->val)
        return ricerca(val, nodo->left);
    else
        return ricerca(val, nodo->right);
}

template <typename T>
BSTNode<T>* BST<T>::Min(BSTNode<T>*p) {
    if(p == NULL) 
        p = root;
    if(p == NULL)
        return NULL;
    while(p->left !=NULL)
        p = p->left;
    return p;
}

template <typename T>
BSTNode<T>*BST<T>::Max(BSTNode<T>*p) {
    if(p == NULL)
        p = root;
    if(p == NULL)
        return NULL;
    while(p->right != NULL) 
        p = p->right;
        
    return p;
}

template <typename T>
BSTNode<T>* BST<T>::next(BSTNode<T>* p) {
    if (!p) return nullptr;

    // Caso 1: c’è un sottoalbero destro → minimo del sottoalbero destro
    if (p->right) 
        return Min(p->right);

    // Caso 2: risalgo finché il nodo non è figlio sinistro
    while (p->parent && p == p->parent->right) 
        p = p->parent;

    return p->parent;  // può essere nullptr se p era il massimo
}

template <typename T>
BSTNode<T>*BST<T>::Trapianta(BSTNode<T>* dest, BSTNode<T>* src) {
    if(dest->parent == NULL)
        root = src;
    else if (dest == dest->parent->left)
        dest->parent->left = src;
    else
        dest->parent->right = src;
    if(src!=NULL)
        src->parent = dest->parent;
    return dest;
}

template <typename T>
void BST<T>::Rimuovi(BSTNode<T>*p) {
    if(p->left == NULL && p->right == NULL)
        if(p->parent == NULL)
            root = NULL;
        else if(p->parent->left == p)
            p->parent->left = NULL;
        else
            p->parent->right = NULL;
    else if(p->left == NULL)
        Trapianta(p, p->right);
    else if(p->right == NULL)
        Trapianta(p, p->left);
    else {
        BSTNode<T>*next = Min(p->right);
        if(p->right != NULL){
            Trapianta(next, next->right);
            next->right = p->right;
            p->right->parent=next;
        }
        Trapianta(p, next);
        next->left = p->left;
        next->left->parent = next;
    }
    delete p;
}

template <typename T>
void BST<T>::Delete(BSTNode<T>* p) {
    if(p != nullptr) {
        Delete(p->left);
        Delete(p->right);
        delete p;
    }
}

template <typename T>
BST<T>::~BST() {
    Delete(root);
}

int main(void) {
    BST<int> tree;
    tree.insert(6);
    tree.insert(10);
    tree.insert(1);
    tree.insert(11);
    tree.insert(55);
    tree.insert(103);
    tree.insert(19);
    cout << "Albero inorder: ";
    tree.printInOrder(tree.getRoot(), cout);
    cout << endl;
    cout << "Albero preorder: ";
    tree.printPreOrder(tree.getRoot(), cout);
    cout << endl;
    int valoreRicerca = 55;
    BSTNode<int> * valoreR = tree.ricerca(valoreRicerca);
    if(valoreR == nullptr)
        cout << "Valore " << valoreRicerca << " non trovato" << endl;
    else
        cout << "Valore "<< valoreR->getVal() << " trovato" << endl;

    valoreRicerca = 111;
    valoreR = tree.ricerca(valoreRicerca);
    if(valoreR == nullptr)
        cout << "Valore " << valoreRicerca << " non trovato" << endl;
    else
        cout << "Valore "<< valoreR->getVal() << " trovato" << endl;
    
    BSTNode<int>*max = tree.Max(NULL);
    BSTNode<int>*min = tree.Min(NULL);

    cout << "Il valore massimo è: " << max->getVal() << endl << "Il valore minimo è: " << min->getVal() << endl;

    BSTNode<int>* nodo = tree.ricerca(10);
    if(nodo!=nullptr) {
        BSTNode<int>*successivo = tree.next(nodo);
        if(successivo != nullptr) {
            cout << "Il successivo del nodo " << nodo->getVal() << " è: " << successivo->getVal() << endl;
        } else {
            cout << "Il nodo " << nodo->getVal() << " non ha successore" << endl;
        }
    }

    int valore = 10;
    BSTNode<int>*nodoRemove = tree.ricerca(valore);
    if(nodoRemove != nullptr) {
        tree.Rimuovi(nodoRemove);
        cout << "Albero inorder dopo la rimozione del nodo " << valore << ": ";
        tree.printInOrder(tree.getRoot(), cout);
        cout << endl;
    }
    valore = 103;
    nodoRemove = tree.ricerca(valore);
    
    if(nodoRemove != nullptr) {
        tree.Rimuovi(nodoRemove);
        cout << "Albero inorder dopo la rimozione del nodo " << valore << ": ";
        tree.printInOrder(tree.getRoot(), cout);
        cout << endl;
    }

    valore = 6;
    nodoRemove = tree.ricerca(valore);
    
    if(nodoRemove != nullptr) {
        tree.Rimuovi(nodoRemove);
        cout << "Albero inorder dopo la rimozione del nodo " << valore << ": ";
        tree.printInOrder(tree.getRoot(), cout);
        cout << endl;
    }
    
    return 0;
}