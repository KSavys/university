#include <string.h>
#include <stdio.h>
#include <stdlib.h>

unsigned int get_random() {
    static unsigned int m_w = 424242;
    static unsigned int m_z = 242424;
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}

typedef struct parametri{
    char *simboli, *output_filename;
    int n;
    char *input_filename;
}Parametri;

Parametri decodeParameters(int argc, char*argv[]){
    Parametri p;
    if(argc!=4){
        fprintf(stderr, "ERRORE Parametri\n");
        exit(1);
    }

    p.simboli = strdup(argv[1]);
    p.n = atoi(argv[2]);
    p.output_filename = strdup(argv[3]);
    p.input_filename = NULL;

    if((strlen(p.simboli) < 10 || strlen(p.simboli) > 20) || (p.n < 8 || p.n > 18)){
        fprintf(stderr, "ERRORE lunghezze errate\n");
        exit(1);
    }

    return p;
}


int *readInput(int n){
    int *W = malloc(n * sizeof(int));
    int x=0;
    for(int i=0;i<n;i++){
        scanf("%d", &x);
        int y=0;
        for(int j=0;j<=x;j++){
            if(j==0){
                y = 1;
            }else{
                y = y * j;
            }   
        }
        W[i] = y;
    }
    return W;
}

char *sampleString(int h, char*simboli){
    int L = strlen(simboli);
    char *str = calloc((h+1), sizeof(char));
    for(int i=0;i<h;i++){
        str[i] = simboli[get_random() % L];
    }
    str[h] = '\0';
    return str;
}

char **getStringArray(char *simboli, int *W, int n){
    int L = strlen(simboli);
    char **Q = malloc(n * sizeof(char**));
    for(int i=0;i<n;i++){
        Q[i] = sampleString(W[i] % L, simboli);
    }
    return Q;
}

void arrayString(int n, char **Q){
    for(int i=0;i<n;i++){
        printf("%s\n", Q[i]);
    }
}

void array(int n, int *W){
    for(int i=0;i<n;i++){
        printf("%d ", W[i]);
    }
}

typedef struct nodo{
    char *str;
    struct nodo*nextptr;
}Nodo;

void push(Nodo**head, char*str){
    Nodo*nuovo=malloc(sizeof(Nodo));
    nuovo->str= strdup(str);
    nuovo->nextptr=*head;
    *head=nuovo;
}

char *pop(Nodo**head){
    Nodo*temp=*head;
    char *elemento = strdup(temp->str);
    *head = temp->nextptr;
    free(elemento);
    return elemento;
}

char *estrazione(char *a, char*b){
    int h=0;
    char *str = malloc(strlen(a) + 1 * sizeof(char));
    for(int i=0;i<strlen(a);i++){
        for(int j=0;j<strlen(b);j++){
            if(a[i] == b[i]){
                str[h++] = a[j];
            }
        }
    }
    str[h] = '\0';
    return str;
}

Nodo*getStack(char **Q, int n, Nodo**head){
    for(int i=0;i<n;i++){
        int h = strlen(Q[i]);
        if(h % 2 !=0){
            char *a = pop(head);
            char *b = estrazione(Q[i], a);
            free(a);
            free(b);
        }else{
            push(head, Q[i]);
        }
    }
    return *head;
}

void Stack(Nodo*head){
    Nodo*corrente=head;
    while(corrente){
        printf("%s\n", corrente->str);
        corrente=corrente->nextptr;
    }
}

void writeStackToFile(Parametri p, Nodo*head){
    FILE *fp = fopen(p.output_filename, "w");
    if(!fp){
        fprintf(stderr, "ERRORE file non aperto\n");
        exit(1);
    }

    Nodo*corrente=head;
    while(corrente){
        fprintf(fp, "%s\n", corrente->str);
        corrente=corrente->nextptr;
    }
    fclose(fp);
}

int main(int argc,char*argv[]){
    Parametri p = decodeParameters(argc, argv);
    printf("Punto A - Parametri:\n");
    printf("%s %s %d", p.simboli, p.output_filename, p.n);
    printf("\nPunto B - Contenuto di W:\n");
    int *W = readInput(p.n);
    array(p.n, W);
    printf("\nPunto C - Contenuto di Q:\n");
    char **Q = getStringArray(p.simboli, W, p.n);
    arrayString(p.n, Q);
    Nodo*head=NULL;
    head = getStack(Q, p.n, &head);
    printf("\nPunto D - Contenuto della pila:\n");
    Stack(head);
    writeStackToFile(p, head);
}