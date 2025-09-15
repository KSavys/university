#include <iostream>
#include <string>
using namespace std;

class Edge{
private:
    size_t target;
    Edge*next;
public:
    Edge(size_t t, Edge*nx) : target(t), next(nx) {}
    Edge*getNext() { return next; }
    size_t getTarget() { return target; }
    void setNext(Edge*nx) {
        next = nx;
    }
};

class Nodo{
private:
    Edge*head;
public:
    Nodo() : head(nullptr) {}
    ~Nodo();
    Edge*addEdge(size_t target);
    Edge*getHead() {return head;}
    void removeEdgesTo(size_t target);
    void distruggi();
};

struct Citta{
    string nome;
    string provincia;
    int abitanti;
};

enum NodeColor{white=0, gray=1, black=2};

class Graph{
private:
    Nodo*nodi;
    size_t num_nodi;
    Citta*citta;
    size_t*d;
    size_t*f;
    NodeColor*color;
    int *pred;
    size_t time;
    
public:
    Graph(size_t n) : num_nodi(n), color(nullptr), d(nullptr), f(nullptr), pred(nullptr) {
        nodi = new Nodo[n];
        citta = new Citta[n];
    }
    
    ~Graph() {
        delete [] nodi;
        delete [] citta;
    }

    size_t getNumNodes() {return num_nodi;}
    size_t getNumEdges();

    Graph& addEdge(size_t source, size_t target) {
        nodi[source].addEdge(target);
        return *this;
    }

    void print();
    void DFS();
    void DFS_Visit(size_t u);
    void Print_DFS_results();

    void setCitta(size_t i, string nome, string prov, int abitanti) {
        citta[i].nome=nome;
        citta[i].provincia=prov;
        citta[i].abitanti=abitanti;
    }

    int getDiametro();
    void rimuoviVertice(size_t v);
    void rimuoviProvincia(string prov);
    void rimuoviAbitanti(int min);
    bool ciclo();
    bool cicloVisitato(size_t u, NodeColor*c);
    int contaComponentiConnessi();

};

Edge*Nodo::addEdge(size_t target){
    Edge*nuovo = new Edge(target, head);
    head = nuovo;
    return nuovo;
}

void Nodo::removeEdgesTo(size_t target){
    Edge*e = head;
    Edge*precedente = nullptr;
    while(e) {
        if(e->getTarget() == target) {
            if(precedente) {
                precedente->setNext(e->getNext());
            } else {
                head = e->getNext();
            }
            Edge*temp = e;
            e = e->getNext();
            delete temp;
        } else {
            precedente = e;
            e = e->getNext();

        }
    }
}

Nodo::~Nodo() {
    distruggi();
}

void Nodo::distruggi() {
    Edge*e = head;
    while(e) {
        Edge*successivo = e->getNext();
        delete e;
        e = successivo;
    }
    head=nullptr;
}

void Graph::print() {
    cout << "Il grafo ha " << num_nodi << " nodi" << endl;
    for(size_t i=0;i<num_nodi;i++) {
        cout << i << " ("<<citta[i].nome<<","<<citta[i].provincia<<","<<citta[i].abitanti<<") -> ";
        Edge*e = nodi[i].getHead();
        while(e) {
            cout << e->getTarget() << " ";
            e = e->getNext();
        }
        cout << endl;
    }
}

size_t Graph::getNumEdges() {
    size_t c = 0;
    for(size_t i=0;i<num_nodi;i++) {
        Edge*e = nodi[i].getHead();
        while(e) {
            c++;
            e = e->getNext();
        }
    }
    return c;
}

//per il diaemetro, userò l'algoritmo BFS
int Graph::getDiametro() {
    int diametro = 0;
    for(size_t j=0;j<num_nodi;j++) {
        int *distanza = new int[num_nodi];
        for(size_t i=0;i<num_nodi;i++) {
            distanza[i] = -1;
        }
        //BFS
        size_t*q = new size_t[num_nodi];
        size_t front=0;
        size_t rear=0;
        distanza[j] = 0;
        q[rear++] = j;

        while(front<rear) {
            size_t u = q[front++];
            Edge*e = nodi[u].getHead();
            while(e) {
                size_t v = e->getTarget();
                if(distanza[v] == -1) {
                    distanza[v] = distanza[u] + 1;
                    q[rear++] = v;
                }
                e = e->getNext();
            }
        }

        for(size_t i=0;i<num_nodi;i++) {
            if(distanza[i] > diametro)
                diametro = distanza[i];
            
        }
        delete [] distanza;
        delete [] q;
    }
    return diametro;
}

void Graph::rimuoviVertice(size_t v) {
    // rimuovo tutti gli archi entranti
    for(size_t i=0;i<num_nodi;i++) {
        if(i!=v)
            nodi[i].removeEdgesTo(v);
    }
    // rimuovo tutti gli archi uscenti
    nodi[v].distruggi();
    citta[v].nome = "";
    citta[v].provincia = "";
    citta[v].abitanti = 0;
}

void Graph::rimuoviProvincia(string prov){
    for(size_t i=0;i<num_nodi;i++) {
        if(citta[i].provincia == prov)
            rimuoviVertice(i);
    }
}

void Graph::rimuoviAbitanti(int min) {
    for(size_t i=0;i<num_nodi;i++) {
        if(citta[i].abitanti < min)
            rimuoviVertice(i);
    }
}

bool Graph::cicloVisitato(size_t u, NodeColor*c) {
    c[u] = gray;
    Edge*e = nodi[u].getHead();
    while(e) {
        size_t v = e->getTarget();
        if(c[v] == gray) {   
            return true;
        }
        if(c[v] == white && cicloVisitato(v,c)) {
            return true;
        }
        e = e->getNext();
    }
    c[u] = black;
    return false;
}

bool Graph::ciclo() {
    NodeColor*c = new NodeColor[num_nodi];
    for(size_t i=0;i<num_nodi;i++) {
        c[i] = white;
    }

    for(size_t i=0;i<num_nodi;i++) {
        if(c[i] == white && cicloVisitato(i, c)){
            delete [] c;
            return true;
        }
    }

    delete [] c;
    return false;
}

int Graph::contaComponentiConnessi() {
    bool*visitato = new bool[num_nodi];
    for(size_t i=0;i<num_nodi;i++) {
        visitato[i] = false;
    }

    int count=0;

    for(size_t i=0;i<num_nodi;i++) {
        if(!visitato[i]) {
            count++;
            //BFS
            size_t*q = new size_t[num_nodi];
            size_t front = 0;
            size_t rear = 0;
            q[rear++] = i;
            visitato[i] = true;
            while(front < rear) {
                size_t u = q[front++];
                Edge*e = nodi[u].getHead();
                while(e) {
                    size_t v = e->getTarget();
                    if(!visitato[v]) {
                        visitato[v] = true;
                        q[rear++] = v;
                    }
                    e = e->getNext();

                }
            }
            delete [] q;
        }
    }

    delete[] visitato;
    return count;
}

void Graph::DFS() {
    if(color) {
        delete [] color;
        delete [] d;
        delete [] f;
        delete [] pred;
    }

    color = new NodeColor[num_nodi];
    d = new size_t[num_nodi];
    f = new size_t[num_nodi];
    pred = new int[num_nodi];
    for(size_t i=0;i<num_nodi;i++) {
        color[i] = white;
        pred[i] = -1;
    }
    time = 0;
    for(size_t i=0;i<num_nodi;i++) {
        if(color[i] == white) {
            DFS_Visit(i);
        }
    }
}

void Graph::DFS_Visit(size_t u) {
    color[u] = gray;   
    d[u] = time++;
    Edge*e = nodi[u].getHead();
    while(e) {
        size_t v = e->getTarget();
        if(color[v] == white) {
            pred[v] = u;
            DFS_Visit(v);
        }
        e = e->getNext();
    }
    color[u] = black;
    f[u] = time++;
}

void Graph::Print_DFS_results() {
    for(size_t i=0;i<num_nodi;i++)
        cout<<"Node "<<i<<": color="<<color[i]<<"; d="<<d[i]<<"; f="<<f[i]<<"; pred="<<pred[i]<<endl;
}


int main() {
    Graph g(5);
    g.setCitta(0,"A","CC",1000);
    g.setCitta(1,"B","CC",2300);
    g.setCitta(2,"C","TT",1200);
    g.setCitta(3,"D","CC",2990);
    g.setCitta(4,"E","CC",990);

    g.addEdge(0,1).addEdge(1,2).addEdge(2,3).addEdge(3,4).addEdge(4,0);
    g.print();

    cout<<"Numero archi: "<<g.getNumEdges()<<endl;
    cout<<"Diametro: "<<g.getDiametro()<<endl;
    cout<<"Ha ciclo? "<<(g.ciclo()?"Si":"No")<<endl;
    cout<<"Componenti connesse: "<<g.contaComponentiConnessi()<<endl;

    cout<<"\nElimino città in provincia TT\n";
    g.rimuoviProvincia("TT");
    g.print();

    cout<<"\nElimino città con meno di 1000 abitanti...\n";
    g.rimuoviAbitanti(1000);
    g.print();
}