#include <iostream>

using namespace std;

class Queue;

ostream& operator<<(ostream&s, const Queue&queue);

class Nodo{
    private:
        int dato;
        Nodo*nextptr;
    public:
        Nodo(int d = 0, Nodo*p = nullptr) : dato(d), nextptr(p) {}
        friend class Queue;
        friend ostream& operator<<(ostream&s, const Queue&queue);
};

class Queue{
    private:
        Nodo*head;
        Nodo*tail;
    public:
        Queue() : head(nullptr), tail(nullptr) {}
        void enqueue(int d);
        void dequeue();
        bool isEmpty() const;
        int valoreFrontale() const;
        ~Queue();
        friend ostream& operator<<(ostream&s, const Queue&queue);

};

void Queue::enqueue(int d) {
    Nodo*nuovo = new Nodo(d, nullptr);
    if(tail == nullptr) {
        head = tail = nuovo;
    } else {
        tail->nextptr = nuovo;
        tail=nuovo;
    }
}

void Queue::dequeue() {
    if(isEmpty()) {
        cout << "La coda è vuota" << endl;
        return;
    }
    Nodo*temp = head;
    head=head->nextptr;
    if(head == nullptr)
        tail = nullptr;
    delete temp;
}

bool Queue::isEmpty() const {
    return head == nullptr;
}

int Queue::valoreFrontale() const {
    if(isEmpty()) {
        cout << "La coda è vuota" << endl;
        return -1;
    }

    return head->dato;
}

Queue::~Queue() {
    while(!isEmpty()) {
        dequeue();
    }
}

ostream& operator<<(ostream&s, const Queue&queue) {
    if(queue.isEmpty()) {
        s << "La coda è vuota" << endl;
        return s;
    }

    Nodo*corrente = queue.head;
    s << "La coda ha questi nodi seguenti:" << endl;
    while(corrente != nullptr) {
        s << corrente->dato << endl;
        corrente=corrente->nextptr;
    }
    return s;
}

int main(void) {
    Queue queue;
    queue.enqueue(10);
    queue.enqueue(21);
    queue.enqueue(11);
    cout << queue;
    queue.dequeue();
    cout << queue;

    cout << "Il valore frontale è: " << queue.valoreFrontale() << endl;

    return 0;
}

