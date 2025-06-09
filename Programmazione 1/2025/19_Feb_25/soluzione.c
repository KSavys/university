#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct parametri{
    char *output_filename;
    int n;
    char *alfabeto;
}Parametri;

unsigned int get_random() { 
    static unsigned int m_w = 424242; 
    static unsigned int m_z = 242424; 
    m_z = 36969 * (m_z & 65535) + (m_z >> 16); 
    m_w = 18000 * (m_w & 65535) + (m_w >> 16); 
    return (m_z << 16) + m_w; 
}

Parametri decodeInput(int argc, char*argv[]) {
    Parametri p;

    if (argc!=2) {
        fprintf(stderr, "Errore: numero di argomenti errato\n");
        exit(1);
    }

    p.output_filename = strdup(argv[1]);

    if (strcmp(p.output_filename + strlen(p.output_filename) - 4, ".txt") != 0) {
        fprintf(stderr, "Errore: il file di output deve terminare con .txt\n");
        exit(1);
    }

    char buffer[255];

   
    if (fscanf(stdin, "%s", buffer) != 1) {
        fprintf(stderr, "Errore nella lettura dell'alfabeto\n");
        exit(1);
    }
    p.alfabeto = strdup(buffer);

    if (strlen(p.alfabeto) < 8 || strlen(p.alfabeto) > 12) {
        fprintf(stderr, "Errore: lunghezza alfabeto non valida\n");
        exit(1);
    }

    if (fscanf(stdin, "%d", &p.n) != 1) {
        fprintf(stderr, "Errore nella lettura di n\n");
        exit(1);
    }

    if (p.n < 3 || p.n > 12) {
        fprintf(stderr, "Errore: valore di n non valido\n");
        exit(1);
    }

    return p;
}

int *factorialModArray(int n){
    int *A = calloc(n, sizeof(int));
    int valore = 0;
    for(int i=0;i<n;i++){
        if(i==0){
            valore = 1;
        }else{
            valore = valore * i;
        }
        A[i] = valore % 101;
    }
    return A;
}

void Array(int n, int *A){
    for(int i=0;i<n;i++){
        printf("A[%d] = %d\n", i, A[i]);
    }
}

char *sampleString(int h, char*alfabeto){
    int L = strlen(alfabeto);
    char * str = calloc((h+1), sizeof(char));
    for(int i=0;i<h;i++){
        str[i] = alfabeto[get_random()%L];
    }
    str[h] = '\0';
    return str;
}

char **getStringArray(int *A, int n, char *alfabeto){
    char **B = malloc(n * sizeof(char*));
    for(int i=0;i<n;i++){
        B[i] = sampleString(A[i], alfabeto);
    }
    return B;

}

void stringArray(int n, char **B){
    for(int i=0;i<n;i++){
        printf("B[%d] = %s\n", i, B[i]);
    }
}

float computeAverageLength(int n, char **B){
    int s=0;
    for(int i=0;i<n;i++){
        s+=strlen(B[i]);
    }
    return (float)s/n;
}

typedef struct nodo{
    char *stringa;
    struct nodo*nextptr;
}Nodo;

void push(Nodo**head, char *stringa){
    Nodo*nuovo=malloc(sizeof(Nodo));
    nuovo->stringa = strdup(stringa);
    nuovo->nextptr = *head;
    *head = nuovo;
}

char *pop(Nodo**head){
    Nodo*temp=*head;
    char *elemento = strdup(temp->stringa);
    *head = temp->nextptr;
    free(temp);
    return elemento;
}

Nodo*getStack(Nodo**head, int n, char **B, float m){
    push(head, B[0]);
    for(int i=1;i<n;i++){
        if(strlen(B[i]) > m){
            char *str = pop(head);
            char *newstr = malloc((strlen((B[i]) + 1)) + strlen(str) * sizeof(char));
            strcpy(newstr, str);
            strcat(newstr, B[i]);
            push(head, newstr);
            free(str);
            free(newstr);
        }else{
            push(head, B[i]);
        }
    }
    return *head;
}

void Stack(Nodo*head){
    Nodo*corrente=head;
    while(corrente){
        printf("%s\n", corrente->stringa);
        corrente=corrente->nextptr;
    }
}

void writeToFile(Parametri p, Nodo**head){
    FILE *fp = fopen(p.output_filename, "w");
    if(!fp){
        fprintf(stderr, "Errore: File non aperto\n");
        exit(1);
    }

    
    while((*head)){
        char *str = pop(head);
        fprintf(fp, "%s\n", str);
        free(str);
    }
    printf("File scritto correttamente.\n");
}



int main(int argc, char*argv[]){
    Parametri p = decodeInput(argc, argv);
    printf("=========A=======\nFile di output: %s\nStringa alfabeto: %s, Intero n: %d\n", p.output_filename, p.alfabeto, p.n);
    int *A = factorialModArray(p.n);
    printf("=========B=======\n");
    Array(p.n, A);
    printf("=========C=======\n");
    char ** B = getStringArray(A, p.n, p.alfabeto);
    stringArray(p.n, B);
    float m = computeAverageLength(p.n, B);
    printf("Lunghezza media: %.2f\n", m);
    printf("=========D=======\n");
    Nodo*head=NULL;
    head = getStack(&head, p.n, B, m);
    Stack(head);
    printf("=========E=======\n");
    writeToFile(p, &head);
    
}