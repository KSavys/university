#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

unsigned int get_random() {
    static unsigned int m_w = 424242;
    static unsigned int m_z = 242424;
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}

typedef struct parametri{
    char *input_filename, *output_filename;
    int n;
}Parametri;

typedef struct record{
    int numeroConto;
    char nome[255];
    char cognome[255];
    float saldo;
}Record;

typedef struct nodo{
    struct record valore;
    struct nodo*nextptr;
}Nodo;

Parametri decodeParameters(int argc, char* argv[]) {
    Parametri p;

    if (argc != 3) {
        fprintf(stderr, "Errore: Parametri errati\n");
        exit(1);
    }

    p.output_filename = argv[1];
    p.n = atoi(argv[2]);
    p.input_filename = NULL;

    if (p.n < 3 || p.n > 5) {
        fprintf(stderr, "Errore: n deve essere tra 3 e 5\n");
        exit(1);
    }

    if (strcmp(p.output_filename + strlen(p.output_filename) - 4, ".bin") != 0) {
        fprintf(stderr, "Errore: il file output deve avere estensione .bin\n");
        exit(1);
    }

    return p;
}

Record readRecord(){
    Record r;
    scanf("%d %s %s %f", &r.numeroConto, r.nome, r.cognome, &r.saldo);
    return r;
}

Nodo*inserisciNodo(Nodo**head, Record record){
    Nodo*nuovo=malloc(sizeof(Nodo));
    nuovo->nextptr=NULL;
    nuovo->valore = record;
    if(*head == NULL){
        *head=nuovo;
    }else{
        Nodo*corrente=*head;
        while(corrente->nextptr != NULL){
            corrente=corrente->nextptr;
        }
        corrente->nextptr=nuovo;
    }

    return *head;
}

Nodo*loadRecords(Nodo**head, Record r){
    while(scanf("%d %s %s %f", &r.numeroConto, r.nome, r.cognome, &r.saldo)==4){
        *head = inserisciNodo(head, r);
    }
    return *head;
}

void printRecord(Record r){
    printf("%d %s %s %.2f\n", r.numeroConto, r.nome, r.cognome, r.saldo);
}

void Records(Nodo*head){
    Nodo*corrente=head;
    while(corrente){
        Record r = corrente->valore;
        printRecord(r);
        corrente=corrente->nextptr;
    }
}

int len(Nodo**head){
    int n=0;
    Nodo*corrente=*head;
    while(corrente){
        ++n;
        corrente=corrente->nextptr;
    }
    return n;
}

Record *getArray(Nodo**head){
    int n = len(head);
    Record*X = malloc(n * sizeof(Record));

    Nodo*corrente=*head;
    int i=0;
    while(corrente){
        X[i++] = corrente->valore;
        corrente=corrente->nextptr;
        
    }
    return X;

}

void sort(Record *X, int n){
    float m=0;
    int s=0;
    for(int i=0;i<n;i++){
        s+=X[i].saldo;
    }
    m = (float)s / n;

    for(int i=0;i<n-1;i++){
        int min = i;
        for(int j=i+1;j<n;j++){
            if((X[j].saldo - m) * (X[j].saldo - m) < (X[min].saldo - m) * (X[min].saldo - m)){
                min = j;
            }
        }

        if(min != i){
            Record temp = X[i];
            X[i] = X[min];
            X[min] = temp;
        }
    }
}

void Array(Record *X, int n){
    for(int i=0;i<n;i++){
        printRecord(X[i]);
    }
}

void saveToFile(Parametri p, Record *X, int n) {
    FILE *fp = fopen(p.output_filename, "wb");
    if (!fp) {
        fprintf(stderr, "Errore nell'apertura del file binario per scrittura.\n");
        exit(1);
    }

    fwrite(X, sizeof(Record), n, fp);
    fclose(fp);
}

int* getRandomOrder(int n) {
    int* order = malloc(n * sizeof(int));
    if (!order) {
        fprintf(stderr, "Errore: Memoria non allocata\n");
        exit(1);
    }

    for (int i = 0; i < n; i++){
        order[i] = i;
    }

    for (int i = 0; i < n; i++) {
        int j = get_random() % n;
        int tmp = order[i];
        order[i] = order[j];
        order[j] = tmp;
    }

    return order;
}

void showFileContent(Parametri p, int n) {
    FILE *fp = fopen(p.output_filename, "rb");
    if (!fp) {
        fprintf(stderr, "Errore nell'apertura del file binario per lettura.\n");
        exit(1);
    }

    Record *buffer = malloc(n * sizeof(Record));
    if (!buffer) {
        fprintf(stderr, "Errore: Memoria non allocata\n");
        exit(1);
    }

    fread(buffer, sizeof(Record), n, fp);
    fclose(fp);

    int *ordine = getRandomOrder(n);

    int max;
    if (n < 5) {
        max = n;
    } else {
        max = 5;
    }

    for (int i = 0; i < max; i++) {
        printRecord(buffer[ordine[i]]);
    }
}
int main(int argc, char*argv[]){
    printf("Punto A:\n");
    Parametri p = decodeParameters(argc, argv);
    printf("%s\n%d\n", p.output_filename, p.n);
    Nodo*L = NULL;
    printf("Punto B:\n");
    Record r;
    L = loadRecords(&L, r);
    Records(L);
    printf("Punto C:\n");
    Record*X = NULL;
    int n = len(&L);
    X = getArray(&L);
    sort(X, n);
    Array(X, n);
    printf("Punto D:\n");
    saveToFile(p, X, p.n);
    showFileContent(p, p.n);

}