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
    char *input_filename, *output_filename, *alfabeto;
    int n;
}Parametri;

Parametri decodeParameters(int argc, char*argv[]){
    Parametri p;
    if(argc!=4){
        fprintf(stderr, "Parametri errati\n");
        exit(1);
    }

    p.input_filename = strdup(argv[1]);
    p.n = atoi(argv[2]);
    p.output_filename = strdup(argv[3]);

    FILE *fp = fopen(p.input_filename, "r");
    if(!fp){
        fprintf(stderr, "Errore: File non aperto\n");
        exit(1);
    }

    char buffer[255];

    if(fscanf(fp, "%s", buffer) != 0){
        p.alfabeto = strdup(buffer);
    }else{
        fprintf(stderr, "Errore di lettura da File\n");
        exit(1);
    }

    if(strlen(p.alfabeto) < 8 || strlen(p.alfabeto) > 12){
        fprintf(stderr, "Lunghezza non valida della stringa\n");
        exit(1);
    }
    
    if(p.n < 3 || p.n > 12){
        fprintf(stderr, "N non valido\n");
        exit(1);
    }


    return p;
}

int *fibonacci(int n){
    int *A = calloc(n, sizeof(int));
    A[0] = 0;
    A[1] = 1;
    for(int i=2;i<n;i++){
        A[i] = A[i-1] + A[i-2];
    }
    return A;
}

void array(int n, int *A){
    for(int i=0;i<n;i++){
        printf("%d ", A[i]);
    }
}

char *sampleString(int h, char*alfabeto){
    char *str = malloc((h+1) * sizeof(char));
    int L = strlen(alfabeto);
    for(int i=0;i<h;i++){
        str[i] = alfabeto[get_random() % L];
    }
    str[h] = '\0';
    return str;
}

char **getStringArray(int n, char *alfabeto, int *A){
    char **B = malloc(n * sizeof(char*));
    for(int i=0;i<n;i++){
        B[i] = sampleString(A[i], alfabeto);
    }
    return B;
}

void arrayString(int n, char **B){
    for(int i=0;i<n;i++){
        printf("%s\n", B[i]);
    }
}

typedef struct nodo{
    char *stringa;
    struct nodo*nextptr;
}Nodo;

void enqueue(Nodo**head, Nodo**tail, char *stringa){
    Nodo*nuovo = malloc(sizeof(Nodo));
    nuovo->stringa = strdup(stringa);
    nuovo->nextptr = NULL;

    if(*head == NULL){
        *head = nuovo;
    }else{
        (*tail)->nextptr=nuovo;
    }
    *tail=nuovo;
}

char *dequeue(Nodo**head, Nodo**tail){
    if(*head == NULL){
        return NULL;
    }

    Nodo*temp = *head;
    char *elemento = strdup(temp->stringa);
    *head=(*head)->nextptr;

    if(*head == NULL){
        *tail = NULL;
    }
    free(temp);
    return elemento;
}

Nodo*getQueue(Nodo**head, Nodo**tail, int n, char**B){
    enqueue(head, tail, B[0]);
    for(int i=1;i<n;i++){
        if(strlen(B[i]) % 2 !=0){
            char *str = dequeue(head, tail);
            char *newstr = malloc((strlen(B[i]) + strlen(str) + 1) * sizeof(char));
            strcpy(newstr, B[i]);
            strcat(newstr, str);
            enqueue(head, tail, newstr);
            free(str);
            free(newstr);
        }else{
            enqueue(head, tail, B[i]);
        }
    }
    return *head;
}

void Queue(Nodo*head){
    Nodo*corrente=head;
    while(corrente){
        printf("%s\n", corrente->stringa);
        corrente=corrente->nextptr;
    }
}

void writeToFile(Parametri p, Nodo**head, Nodo**tail){
    FILE *fp = fopen(p.input_filename, "r");
    if(!fp){
        fprintf(stderr, "Errore: File non aperto\n");
        exit(1);
    }

    if(*head == NULL){
        char *str = dequeue(head, tail);
        fprintf(fp, "%s\n", str);
        free(str);
    }
    fclose(fp);
}

int main(int argc, char*argv[]){
    Parametri p = decodeParameters(argc, argv);
    printf("========================A========================\n");
    printf("Parameters: inputFile=%s, n=%d, outputFile=%s\nInput string: %s\n", p.input_filename, p.n, p.output_filename, p.alfabeto);
    int *A = fibonacci(p.n);
    printf("========================B========================\n");
    printf("Fibonacci array: ");
    array(p.n, A);
    char ** B = getStringArray(p.n, p.alfabeto, A);
    printf("\n========================C========================\nString array B:\n");
    arrayString(p.n, B);
    Nodo*head=NULL;
    Nodo*tail=NULL;
    head = getQueue(&head, &tail, p.n, B);
    printf("========================D========================\n");
    printf("Queue:\n");
    Queue(head);
    



}