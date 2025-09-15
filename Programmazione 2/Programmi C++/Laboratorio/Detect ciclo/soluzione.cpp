#include <iostream>
using namespace std;

struct Nodo{
    int val;
    Nodo*nextptr;
    Nodo(int val) : val(val), nextptr(nullptr) {}
};

class Lista{
private:
    Nodo*head;
public:
    Lista() : head(nullptr) {}
    ~Lista();
    void inserisci(int val);
    void stampa();
    bool detectAndRemoveLoop();
};

bool Lista::detectAndRemoveLoop(){
    if(head == nullptr || head->nextptr == nullptr)
        return false;
    Nodo*slow = head;
    Nodo*fast = head;

    while(fast != nullptr && fast->nextptr != nullptr){
        slow = slow->nextptr;
        fast = fast->nextptr->nextptr;
        if(slow == fast)
            break;
    }

    if(slow!=fast)
        return false;
    slow = fast;

    if(slow == fast){
        while(fast->nextptr != slow){
            fast = fast->nextptr;
        } 
    } else {
            while(slow->nextptr != fast->nextptr){
                fast = fast->nextptr;
                slow = slow->nextptr;
            }
        }
    
    fast->nextptr=nullptr;
    return true;
}

Lista::~Lista(){
    Nodo*corrente=head;
    while(corrente!=nullptr){
        Nodo*temp = corrente;
        corrente=corrente->nextptr;
        delete temp;
    }
}

void Lista::inserisci(int val) {
    Nodo*nuovo = new Nodo(val);
    if(!head){
        head = nuovo;
    } else{
        Nodo*corrente=head;
        while(corrente->nextptr !=nullptr) {
            corrente=corrente->nextptr;
        }
        corrente->nextptr = nuovo;
    }
}

void Lista::stampa(){
    Nodo*corrente=head;
    while(corrente!=nullptr){
        cout << corrente->val << " ";
        corrente=corrente->nextptr;
    }
}

int main(void) {
    Lista l;
    l.inserisci(50);
    l.inserisci(20);
    l.inserisci(15);
    l.inserisci(4);
    l.inserisci(10);
    l.detectAndRemoveLoop();
    cout << "Lista linkata dopo la rimozione del ciclo" << endl;
    l.stampa();
    return 0;
}