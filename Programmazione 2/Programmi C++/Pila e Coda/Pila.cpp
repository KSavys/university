#include <iostream>

using namespace std;

class Stack;

ostream& operator<<(ostream&s, const Stack&stack);

class Nodo{
    private:
        Nodo*nextptr;
        int dato;
    public:
        Nodo(Nodo* p = nullptr, int d = 0) : nextptr(p), dato(d) {}
        friend class Stack;
        friend ostream& operator<<(ostream&s, const Stack&stack);
};

class Stack{
    private:
        Nodo*top;
    public:
        Stack() : top(nullptr) {}
        ~Stack();
        void push(int d);
        void pop();
        bool isEmpty() const;
        int Top() const;
        friend ostream& operator<<(ostream&s, const Stack&stack);
};

Stack::~Stack() {
    while(!isEmpty()) {
        pop();
    }
}

int Stack::Top() const {
    if (isEmpty()) {
        cout << "Pila vuota" << endl;
        return -1;
    }
    return top->dato;
}


void Stack::push(int d) {
    top = new Nodo(top, d);
}

bool Stack::isEmpty() const {
    return top == nullptr;
}

void Stack::pop() {
    if(isEmpty()) {
        cout << "Pila vuota" << endl;
        return;
    }
    Nodo*temp = top;
    top = top->nextptr;
    delete temp;
}

ostream& operator<<(ostream&s, const Stack&stack) {
    if(stack.isEmpty()) {
        s << "Pila vuota" << endl;
        return s;
    }
    s << "Stack:" << endl;
    Nodo*corrente=stack.top;
    while(corrente!=nullptr) {
        s << corrente->dato << endl;
        corrente=corrente->nextptr;
    }
    return s;
}


int main(void) {
    Stack pila;
    pila.push(90);
    pila.push(20);
    pila.push(35);
    cout << pila;
    pila.pop();
    cout << pila;
    cout << "Il valore in cima è: " << pila.Top() << endl;
    return 0;
}