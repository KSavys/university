#include <iostream>
using namespace std;

class Edge {
private:
    Edge* next;
    size_t target;
public:
    Edge(size_t target, Edge* next) : target(target), next(next) {}
    Edge* getNext() { return next; }
    size_t getTarget() { return target; }
};

class Node {
private:
    Edge* head;
public:
    Node() : head(nullptr) {}
    ~Node();
    Edge* getHead() { return head; }
    Edge* AddEdge(size_t target);
};

enum NodeColor { white = 0, gray = 1, black = 2 };

class Graph {
private:
    size_t* d;
    size_t* f;
    int* pred;
    size_t time;
    NodeColor* color;
    Node* nodes;
    size_t num_nodes;
public:
    Graph(size_t num_nodes) : num_nodes(num_nodes), color(nullptr), d(nullptr), f(nullptr), pred(nullptr) {
        nodes = new Node[num_nodes];
    }
    ~Graph() {
        delete[] nodes;
        delete[] color;
        delete[] d;
        delete[] f;
        delete[] pred;
    }

    size_t getNumNodes() { return num_nodes; }
    size_t getNumEdges();
    Graph& AddEdge(size_t source, size_t target) {
        nodes[source].AddEdge(target);
        return *this;
    }
    void Print();
    void DFS();
    void DFS_Visit(size_t u);
    void Print_DFS_results();
};

Node::~Node() {
    Edge* corrente = head;
    while (corrente != nullptr) {
        Edge* temp = corrente->getNext();
        delete corrente;
        corrente = temp;
    }
}

Edge* Node::AddEdge(size_t target) {
    Edge* nuovo = new Edge(target, head);
    head = nuovo;
    return nuovo;
}

void Graph::Print() {
    cout << "Il grafo ha " << num_nodes << " nodi" << endl;
    cout << "Gli archi sono: " << endl;
    for (int i = 0; i < num_nodes; i++) {
        Edge* corrente = nodes[i].getHead();
        while (corrente != nullptr) {
            cout << "(" << i << ", " << corrente->getTarget() << ")" << endl;
            corrente = corrente->getNext();
        }
    }
}

size_t Graph::getNumEdges() {
    size_t c = 0;
    for (int i = 0; i < num_nodes; i++) {
        Edge* corrente = nodes[i].getHead();
        while (corrente != nullptr) {
            c++;
            corrente = corrente->getNext();
        }
    }
    return c;
}

void Graph::DFS() {
    if (color) {
        delete[] color;
        delete[] d;
        delete[] f;
        delete[] pred;
    }

    color = new NodeColor[num_nodes];
    d = new size_t[num_nodes];
    f = new size_t[num_nodes];
    pred = new int[num_nodes];

    for (int i = 0; i < num_nodes; i++) {
        color[i] = white;
        pred[i] = -1;
    }
    time = 0;
    for (int i = 0; i < num_nodes; i++) {
        if (color[i] == white) DFS_Visit(i);
    }
}

void Graph::DFS_Visit(size_t u) {
    color[u] = gray;
    d[u] = ++time;
    Edge* corrente = nodes[u].getHead();
    while (corrente != nullptr) {
        size_t v = corrente->getTarget();
        if (color[v] == white) {
            pred[v] = u;
            DFS_Visit(v);
        }
        corrente = corrente->getNext();
    }
    color[u] = black;
    f[u] = ++time;
}

void Graph::Print_DFS_results() {
    for (int i = 0; i < num_nodes; i++)
        cout << "Node " << i << ": color=" << color[i]
             << "; d=" << d[i] << "; f=" << f[i] << "; pred=" << pred[i] << endl;
}

int main() {
    int n = 7;
    Graph g(n);

    // Aggiungiamo gli archi
    g.AddEdge(0, 1).AddEdge(0, 2);
    g.AddEdge(1, 3).AddEdge(1, 4);
    g.AddEdge(2, 5);
    g.AddEdge(3, 5);
    g.AddEdge(4, 6);
    g.AddEdge(5, 6);
    g.AddEdge(6, 6); // loop sul nodo 6

    g.Print();
    cout << "Il numero di archi è: " << g.getNumEdges() << endl;

    g.DFS();
    g.Print_DFS_results();

    return 0;
}
