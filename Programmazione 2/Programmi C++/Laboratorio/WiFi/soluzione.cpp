/* PC devono potersi connettere ad un wifi.

Il wifi deve salvare tutti i PC che sono connessi a lui.

Subito dopo devi creare un protocollo SMS che consente ai PC di mandarsi messaggi tra loro. Questi messaggi devono essere immagazzinati in un buffer che, una volta raggiunti i 5 messaggi, li invia tutti in una volta e si prepara a riceverne degli altri.

Le specifiche per le classi sono:
PC:
id proprio
id di rete
nome
wifi:
id rete
array o lista di dispositivi connessi (max 10 non ricordo il numero ma ci siamo capiti)
buffer messaggi*/

#include <iostream>
#include <string>
using namespace std;

class PC{
private:
    int id_proprio;
    int id_rete;
    string nome;
public:
    PC(int id_proprio = 0, int id_rete = 0, const string &nome = "") : id_proprio(id_proprio), id_rete(id_rete), nome(nome) {}
    virtual ~PC() {};
    int getIdProprio() const {return id_proprio;}
    int getIdRete() const {return id_rete;}
    string getNome() const {return nome;}
};

class Wifi{
private:
    int id_rete;
    int n_pc;
    int n_msg;
    PC**dispositivi;
    static const int n_oggetti_dispositivi = 10;
    static const int n_buffer = 5;
    string Buffer[n_buffer];
public:
    Wifi(int id_rete) : id_rete(id_rete), n_pc(0), n_msg(0) {
        dispositivi = new PC*[n_oggetti_dispositivi];
    }
    ~Wifi();
    void connettiPC(PC*pc);
    void inviaMessaggio(PC*mittente, PC*destinatario, string testo);
};

Wifi::~Wifi(){
    delete [] dispositivi;
}

void Wifi::connettiPC(PC *pc){
    if(n_pc >= n_oggetti_dispositivi){
        cout << "Limite massimo di PC connessi raggiunto (MAX 10)" << endl;
        return;
    }
    dispositivi[n_pc++] = pc;
    cout << "PC " << pc->getNome() << " connesso alla rete " << id_rete  << endl;
}

void Wifi::inviaMessaggio(PC*mittente, PC*destinatario, string testo){
    if(mittente->getIdRete() != id_rete || destinatario->getIdRete() != id_rete){
        cout << "I pc non sono collegati nella stessa rete" << endl;
        return;
    }

    string msg = "Da " + mittente->getNome() + " a " + destinatario->getNome() + ": " + testo;
    Buffer[n_msg++] = msg;

    if(n_msg == n_buffer){
        cout << "Invio " << n_buffer << " messaggi in corso" << endl;
        for(int i=0;i<n_buffer;i++){
            cout << Buffer[i] << endl;
        }
        n_msg = 0;
        cout << "Buffer svuotato" << endl;

    } 
}

int main() {
    Wifi wifi(101);

    PC pc1(1, 101, "Alice");
    PC pc2(2, 101, "Bob");

    wifi.connettiPC(&pc1);
    wifi.connettiPC(&pc2);

    wifi.inviaMessaggio(&pc1, &pc2, "Ciao Bob!");
    wifi.inviaMessaggio(&pc2, &pc1, "Ciao Alice!");
    wifi.inviaMessaggio(&pc1, &pc2, "Come stai?");
    wifi.inviaMessaggio(&pc2, &pc1, "Tutto bene, tu?");
    wifi.inviaMessaggio(&pc1, &pc2, "Ottimo!");

    wifi.inviaMessaggio(&pc2, &pc1, "Ci vediamo più tardi!");

    return 0;
}