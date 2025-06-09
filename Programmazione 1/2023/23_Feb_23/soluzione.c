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
    char *alfabeto;
    int n;
    char *output_filename;
    char *input_filename;
}Parametri;

typedef struct nodo{
    char *stringa;
    struct nodo*nextptr;
}Nodo;

Parametri decodeParameters(int argc, char*argv[]){
    Parametri p;
    if(argc!=4){
        fprintf(stderr, "Errore: Parametri errati\n");
        exit(1);
    }

    p.alfabeto = strdup(argv[1]);
    p.n = atoi(argv[2]);
    p.output_filename = strdup(argv[3]);
    p.input_filename = NULL;

    if(strlen(p.alfabeto) < 5 || strlen(p.alfabeto) > 15){
        fprintf(stderr, "Errore: Lunghezza alfabeto non valida");
        exit(1);
    }

    if(p.n < 5 || p.n > 20){
        fprintf(stderr, "Errore: Lunghezza n non valida\n");
        exit(1);
    }
    return p;
}

int *readInput(int n, char*alfabeto){
    int L = strlen(alfabeto);
    int *W = malloc(n * sizeof(int));
    int x=0;
    for(int i=0;i<n;i++){
        scanf("%d", &x);
        if(x>L){
            x = L;
        }else{
            if(x<1){
                x = 1;
            }
        }
        W[i] = x;
    }

    return W;
}

void Array(int n, int *W){
    for(int i=0;i<n;++i){
        printf("%d\n", W[i]);
    }
}

char *sampleString(int h, char*alfabeto){
    int L = strlen(alfabeto);
    char *str = malloc((h + 1) * sizeof(char));
    for(int i=0;i<h;i++){
        str[i] = alfabeto[get_random() % L];
    }
    str[h] = '\0';
    return str;
}

char **getStringArray(char *alfabeto, int *W, int n){
    char ** Q = malloc(n * sizeof(char*));
    for(int i=0;i<n;i++){
        Q[i] = sampleString(W[i], alfabeto);
    }
    return Q;
}

void StringArray(int n, char **Q){
    for(int i=0;i<n;i++){
        printf("%s\n", Q[i]);
    }
}

void push(Nodo**head, char *stringa){
    Nodo*nuovo=calloc(1, sizeof(Nodo));
    nuovo->stringa = strdup(stringa);
    nuovo->nextptr = *head;
    *head=nuovo;
}

char *pop (Nodo**head){
    Nodo*temp = *head;
    char * elemento = strdup(temp->stringa);
    *head = temp->nextptr;
    free(temp);
    return elemento;
}

Nodo*getStack(Nodo**head, char **Q, int n){
    push(head, Q[0]);
    for(int i=1;i<n;i++){
        if(strlen(Q[i]) % 2 !=0){
            char *str = pop(head);
            char *newstr = malloc(strlen(Q[i] + 1) + strlen(str) * sizeof(char));
            strcpy(newstr, str);
            strcat(newstr, Q[i]);
            push(head, newstr);
            free(str);
            free(newstr);
        }else{
            push(head, Q[i]);
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

void writeStackToFile(Parametri p, Nodo*head){
    printf("Scrittura file\n");
    FILE *fp = fopen(p.output_filename, "w");
    if(!fp){
        fprintf(stderr, "Errore: FILE non aperto\n");
        exit(1);
    }

    Nodo*corrente=head;
    while(corrente){
        fprintf(fp, "%s\n", corrente->stringa);
        corrente=corrente->nextptr;
    }
}

int main(int argc, char*argv[]){
    Parametri p = decodeParameters(argc, argv);
    printf("Punto A:\nAlfabeto: %s\nn = %d\noutput = %s", p.alfabeto, p.n, p.output_filename);
    printf("\nPunto B:\n");
    int *W = NULL;
    W = readInput(p.n, p.alfabeto);
    Array(p.n, W);
    char ** Q = NULL;
    Q = getStringArray(p.alfabeto, W, p.n);
    printf("\nPunto C:\n");
    StringArray(p.n, Q);
    printf("\nPunto D:\n");
    Nodo*head = NULL;
    head = getStack(&head, Q, p.n);
    Stack(head);
    printf("\nPunto E:\n");
    writeStackToFile(p, head);
}

