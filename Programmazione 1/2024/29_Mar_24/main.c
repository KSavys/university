#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX 100

typedef struct parametri{
    char input_filename [MAX];
}Parametri;

Parametri decodeParameters(int argc, char*argv[]){
    Parametri p;
    if(argc!=2){
        fprintf(stderr, "Errore: Parametri errati\n");
        exit(1);
    }
    strcpy(p.input_filename, argv[1]);
    if(strcmp(p.input_filename + strlen(p.input_filename) - 4, ".txt") !=0){
        fprintf(stderr, "Errore: Estensione .txt errata\n");
        exit(1);
    }

    return p;
}

typedef struct nodo{
    int num;
    struct nodo*nextptr;
}Nodo;

void push(Nodo**head, int num){
    Nodo*nuovo=calloc(1, sizeof(Nodo));
    nuovo->num = num;
    nuovo->nextptr= *head;
    *head=nuovo;
}

char pop(Nodo**head){
    Nodo*temp=*head;
    int numero = temp->num;
    *head=temp->nextptr;
    free(temp);
    return numero;
}

Nodo*readFile(Nodo**head, FILE *fp){
    int numero;
    while(fscanf(fp, "%d", &numero) == 1){
        push(head, numero);
    }
    fclose(fp);
    return *head;
}

float getMean(Nodo**head){
    int c=0;
    float s=0;
    while(*head){
        s+=pop(head);
        c++;
    }
    return s / c;
}

void Stack(Nodo*head){
    Nodo*corrente=head;
    while(corrente){
        printf("%d\n", corrente->num);
        corrente=corrente->nextptr;
    }
}

void fillP(Nodo**head, Parametri p, float m){
    int x=0;
    FILE *fp = fopen(p.input_filename, "r");
    if(fp == NULL){
        fprintf(stderr, "Errore: file non aperto\n");
        exit(1);
    }

    fscanf(fp, "%d", &x);
    push(head, x);

    while(fscanf(fp, "%d", &x) == 1){
        if(x > m){
            push(head, x);
        }else{
            int y = pop(head);
            push(head, ((x + y) / 2));
        }
    }
}

int len (Nodo**head){
    int n=0;
    Nodo*corrente=*head;
    while(corrente){
        ++n;
        corrente=corrente->nextptr;
    }
    return n;
}

int *transferP(int n, Nodo**head){
    int *A = malloc(n * sizeof(int));
    int i=0;
    Nodo*corrente=*head;
    while(corrente){
        A[i++] = corrente->num;
        corrente = corrente-> nextptr;
    }
    return A;
}

void sort(int n, int * A){
    for(int i=1;i<n;i++){
        int temp = A[i];
        int j = i-1;
        while(j>=0 && A[j] > temp){
            A[j+1] = A[j];
            j--;
        }
        A[j+1] = temp;
    }
}

void array(int n, int *A){
    for(int i=0;i<n;i++){
        printf("%d\n", A[i]);
    }
}

int main(int argc, char*argv[]){
    Parametri p = decodeParameters(argc, argv);
    printf("==========PUNTO A==========\nNome del file: %s\n", p.input_filename);
    printf("==========PUNTO B==========\nContenuto della pila:\n");
    Nodo*head=NULL;
    FILE *fp = fopen(p.input_filename, "r");
    if(fp == NULL){
        fprintf(stderr, "Errore: file non aperto\n");
        exit(1);
    }
    head = readFile(&head, fp);
    Stack(head);
    printf("==========PUNTO C==========\n");
    float m = getMean(&head);
    printf("Media dei valori di P: %.2f\n", m);
    printf("==========PUNTO D==========\nContenuto della pila:\n");
    fillP(&head, p, m);
    Stack(head);
    int n = len(&head);
    int * A = transferP(n, &head);
    printf("==========PUNTO E==========\n");
    sort(n, A);
    array(n, A);




}