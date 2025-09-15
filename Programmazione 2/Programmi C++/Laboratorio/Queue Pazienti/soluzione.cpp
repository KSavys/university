#include <iostream>
#include <string>
using namespace std;

class Patient{
private:
    int id;
    string name;
    string condition;
public:
    Patient(int id = 0, const string &name = "", const string &condition = "") : id(id), name(name), condition(condition) {}
    void setId(int id) {
        this->id = id;
    }
    void setName(string name) {
        this->name = name;
    }
    void setCondition(string condition) {
        this->condition = condition;
    }

    int getId() const {
        return id;
    }

    string getName() const {
        return name;
    }

    string getCondition() const {
        return condition;
    }

    void stampa(ostream&s) {
        s << "Paziente: " << name << "" << endl << "ID: " << id << endl << "Condizione: " << condition << endl;
    }
};

template <typename T>
class Queue;

template <typename T>
ostream &operator<<(ostream&s, const Queue<T>&queue);

template <typename T>
struct Nodo{
    T valore;
    Nodo<T>*nextptr;
    Nodo(T valore) : valore(valore), nextptr(nullptr) {}
};

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
    void enqueuePriority(T valore);
    template <typename U>
    friend ostream& operator<<(ostream&s, const Queue<U>&queue);
};

template <typename T>
void Queue<T>::enqueuePriority(T valore) {
    int n = 0;
    T temp[3];
    while(!isEmpty() && n < 3) {
        temp[n++] = dequeue();
    }
    enqueue(valore);
    for(int i=0;i<n;++i) {
        enqueue(temp[i]);
    }
    
}

template <typename T>
Queue<T>::~Queue() {
    while(!isEmpty()) dequeue();
}

template <typename T>
void Queue<T>::enqueue(T valore) {
    Nodo<T>*nuovo = new Nodo<T>(valore);
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
        s << endl;
        corrente=corrente->nextptr;
    }
    return s;
}


int main(void) {
    Queue<Patient*>queue;
    queue.enqueue(new Patient(104, "Light Yagami", "Arresto Cardiaco"));
    queue.enqueue(new Patient(105, "Miriam Magistro", "Braccio fratturato"));
    queue.enqueue(new Patient(106, "IlNoizTV", "Arresto Cardiaco"));
    queue.enqueue(new Patient(107, "Lukey Side", "Diarrea"));
    cout << "Coda iniziale dei pazienti:" << endl;
    cout << queue;
    queue.dequeue();

    cout << "Coda dei pazienti dopo dequeue" << endl;
    cout << queue;

    queue.enqueuePriority(new Patient(108, "Alessia Tarantino", "Alopecia"));
    cout << "Coda dei pazienti dopo l'inserimento del paziente raccomandato:" << endl;
    cout << queue;
    return 0;
}