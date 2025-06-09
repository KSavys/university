#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

typedef struct parametri{
    int n;
    char *input_filename;
}Parametri;

typedef struct nodo{
    float val;
    struct nodo*nextptr;
}Nodo;

typedef struct valori{
    float max, min, media;
}Valori;

Parametri decodeParameters(int argc, char*argv[]){
    Parametri p;
    if(argc!=3){
        fprintf(stderr, "Errore: Parametri errati\n");
        exit(1);
    }

    p.n = atoi(argv[1]);
    p.input_filename = strdup(argv[2]);

    if(p.n < 5 || p.n > 20){
        fprintf(stderr, "Errore: Lunghezza n non valida\n");
        exit(1);
    }

    if(strcmp(p.input_filename + strlen(p.input_filename) - 4, ".dat") !=0){
        fprintf(stderr, "Errore: Estensione .dat errata\n");
        exit(1);
    }

    return p;
}

int len(FILE *fp){
    int n=0, buffer=0;
    while(fscanf(fp, "%d", &buffer)==1){
        n++;
    }
    rewind(fp);
    return n;
}

int *readInput(FILE *fp, int n){
    int * A = malloc(n * sizeof(int));
    for(int i=0;i<n;i++){
        fscanf(fp, "%d", &A[i]);
    }
    fclose(fp);
    return A;
}

void Array(int n, int *A){
    for(int i=0;i<n;i++){
        printf("%d\n", A[i]);
    }
}

void push(Nodo**head, float val){
    Nodo*nuovo=calloc(1, sizeof(float));
    nuovo->val = val;
    nuovo->nextptr=*head;
    *head=nuovo;
}

float pop (Nodo**head){
    Nodo*temp=*head;
    float elemento = temp->val;
    *head=temp->nextptr;
    free(temp);
    return elemento;
}

Nodo*createStack(Nodo**head, int param_n, int *A, int n){
    push(head, A[0]);
    for(int i=1;i<n;i++){
        if(A[i] % param_n == 0){
            push(head, A[i]);
        }else{
            float x = pop(head);
            push(head, (int)(A[i] + x) / 2);
        }
    }
    return *head;
}

void Stack(Nodo*head){
    Nodo*corrente=head;
    while(corrente){
        printf("%.2f\n", corrente->val);
        corrente=corrente->nextptr;
    }
}

Valori findMinMaxMean(Nodo *head) {
    Valori v;

    v.max = head->val;
    v.min = head->val;
    float s=0;
    int k=0;
    Nodo*corrente=head;

    while(corrente){
        float valore = corrente->val;
        if(valore > v.max){
            v.max = valore;
        }else{
            if(valore < v.min){
                v.min = valore;
            }
        }
        s+=valore;
        k++;
        corrente=corrente->nextptr;
    }
    v.media = s / k;
    return v;
}

int main(int argc, char*argv[]){
    Parametri p = decodeParameters(argc, argv);
    printf("Punto A - Parametri inseriti: n=%d, inputFileName=%s\n", p.n, p.input_filename);
    printf("Punto B - Contenuto di A:\n");
    int *A = NULL;
    FILE *fp = fopen(p.input_filename, "r");
    if(!fp){
        fprintf(stderr, "Errore: FILE non aperto\n");
        exit(1);
    }
    int n = len(fp);
    A = readInput(fp, n);
    Array(n, A);
    printf("Punto C - Contenuto di S:\n");
    Nodo*head=NULL;
    head = createStack(&head, p.n, A, n);
    Stack(head);
    printf("Punto D:\n");
    Valori v = findMinMaxMean(head);
    printf("Valore minimo: %.2f\nValore massimo: %.2f\nValore medio: %.2f", v.min, v.max, v.media);
}