#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
using namespace std;

class OperazioneAritmetica{
private:
    double opSinistro;
    double opDestro;
public:
    OperazioneAritmetica(double opSinistro = 0.0, double opDestro = 0.0) : opSinistro(opSinistro), opDestro(opDestro) {}
    virtual double eseguiCalcolo() const = 0;
    virtual ~OperazioneAritmetica() {}
    virtual void stampa() const = 0;
    double getOpSinistro() const {return opSinistro;}
    double getOpDestro() const {return opDestro;}
    void setOpDestro(double opDestro){this->opDestro = opDestro;}
    void setOpSinistro(double opSinistro) {this->opSinistro = opSinistro;}
};

class Addizione : public OperazioneAritmetica{
public:
    Addizione(double opSinistro = 0.0, double opDestro = 0.0) : OperazioneAritmetica(opSinistro, opDestro) {}
    double eseguiCalcolo() const override{
        return getOpSinistro() + getOpDestro();
    }
    void stampa() const override {
        cout << getOpSinistro() << " + " << getOpDestro() << " = " << eseguiCalcolo() << endl;
    }
};

class Sottrazione : public OperazioneAritmetica{
public:
    Sottrazione(double opSinistro = 0.0, double opDestro = 0.0) : OperazioneAritmetica(opSinistro, opDestro) {}
    double eseguiCalcolo() const override{
        return getOpSinistro() - getOpDestro();
    }
    void stampa() const override {
        cout << getOpSinistro() << " - " << getOpDestro() << " = " << eseguiCalcolo() << endl;
    }
};

class Moltiplicazione : public OperazioneAritmetica{
public:
    Moltiplicazione(double opSinistro = 0.0, double opDestro = 0.0) : OperazioneAritmetica(opSinistro, opDestro) {}
    double eseguiCalcolo() const override{
        return getOpSinistro() * getOpDestro();
    }
    void stampa() const override {
        cout << getOpSinistro() << " * " << getOpDestro() << " = " << eseguiCalcolo() << endl;
    }
};

class Divisione : public OperazioneAritmetica{
public:
    Divisione(double opSinistro = 0.0, double opDestro = 0.0) : OperazioneAritmetica(opSinistro, opDestro) {}
    double eseguiCalcolo() const override {
        if (getOpDestro() == 0) {
            cout << "Impossibile dividere per 0" << endl;
            return NAN;
        }
        return getOpSinistro() / getOpDestro();
    }

    void stampa() const override {
        if (getOpDestro() == 0) {
            cout << getOpSinistro() << " / " << getOpDestro() << " = Impossibile dividere per 0" << endl;
        } else {
            cout << getOpSinistro() << " / " << getOpDestro() << " = " << eseguiCalcolo() << endl;
        }
}
};

template <typename T>
struct Nodo{
    T valore;
    Nodo<T>*nextptr;
    Nodo(T valore) : valore(valore), nextptr(nullptr) {}
};

template <typename T>
class Stack{
private:
    Nodo<T>*top;
public:
    Stack() : top(nullptr) {}
    ~Stack();
    void push(T valore);
    T dequeue();
    bool isEmpty() const;
    void stampa();
    T Top();
};

template <typename T>
T Stack<T>::Top(){
    return top->valore;
}

template <typename T>
void Stack<T>::stampa(){
    Nodo<T>*corrente=top;
    while(corrente!=nullptr){
        corrente->valore->stampa();
        corrente=corrente->nextptr;
    }
}

template <typename T>
void Stack<T>::push(T valore) {
    Nodo<T>*nuovo = new Nodo<T>(valore);
    nuovo->nextptr = top;
    top = nuovo;
}

template <typename T>
Stack<T>::~Stack(){
    while(!isEmpty()) {
        T val = dequeue();
        delete val;
    }
        
}

template <typename T>
bool Stack<T>::isEmpty() const {
    return top == nullptr;
}

template <typename T>
T Stack<T>::dequeue(){
    Nodo<T>*temp = top;
    T val = temp->valore;
    top = top->nextptr;
    delete temp;
    return val;
}

template <typename T>
class Queue{
private:
    Nodo<T>*head;
    Nodo<T>*tail;
public:
    Queue() : head(nullptr), tail(nullptr) {}
    ~Queue();
    void enqueue(T valore);
    T dequeue();
    bool isEmpty() const;
    T front();
    void stampa();
};

template <typename T>
Queue<T>::~Queue(){
    while(!isEmpty()) dequeue();
}

template <typename T>
void Queue<T>::stampa(){
    Nodo<T>*corrente=head;
    while(corrente!=nullptr){
        cout << corrente->valore << " ";
        corrente=corrente->nextptr;
    }
}

template <typename T>
bool Queue<T>::isEmpty() const{
    return head == nullptr;
}

template <typename T>
void Queue<T>::enqueue(T valore){
    Nodo<T>*nuovo = new Nodo<T>(valore);
    if(!tail){
        head = tail = nuovo;
    } else{
        tail->nextptr = nuovo;
        tail = nuovo;
    }
}

template <typename T>
T Queue<T>::dequeue(){
    Nodo<T>*temp = head;
    T val = temp->valore;
    head = head->nextptr;
    if(head == nullptr) tail = nullptr;
    delete temp;
    return val;
}

template <typename T>
T Queue<T>::front(){
    return head->valore;
}

int main(void) {
    srand(time(0));
    int N=0;
    cout << "Inserisci un valore intero N: ";
    cin >> N;
    Stack<OperazioneAritmetica*>stack;
    for(int i=0;i<N;i++){
        int op = (rand() % 4) + 1;
        double a = (rand() % 100) / 10.0;
        double b = (rand() % 100) / 10.0;
        switch(op){
            case 1:
                {
                    stack.push(new Addizione(a, b));
                    break;
                }
            case 2:
                {
                    stack.push(new Sottrazione(a, b));
                    break;
                }   
            case 3:
                {
                    stack.push(new Moltiplicazione(a, b));
                    break;
                }   
            case 4:
                {
                    stack.push(new Divisione(a, b));
                    break;
                }   
        }
    }

    cout << "Stack iniziale:" << endl;
    stack.stampa();
    Queue<double>queue;

    for(int i=0;i<2*N;++i){
        double val = (rand() % 100) / 10.0;
        queue.enqueue(val);
    }

    cout << endl;
    cout << "Coda double 2*N" << endl;
    queue.stampa();

    cout << endl;
    cout << "Operazione finale:" << endl;
    while(!queue.isEmpty() && !stack.isEmpty()){
        OperazioneAritmetica*op = stack.Top();
        double x = queue.front();
        queue.dequeue();
        double y = queue.front();
        queue.dequeue();
        op->setOpSinistro(x);
        op->setOpDestro(y);
        op->eseguiCalcolo();
        op->stampa();
        stack.dequeue();
    }



    return 0;
}