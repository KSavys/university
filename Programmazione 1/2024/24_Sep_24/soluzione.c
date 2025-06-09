#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct parametri{
    char *input_filename;
    char *output_filename;
}Parametri;

typedef struct nodo{
    char *str;
    struct nodo*nextptr;
}Nodo;

Parametri decodeParameters(int argc, char*argv[]){
    Parametri p;
    if(argc!=3){
        fprintf(stderr, "Errore: Parametri errati\n");
        exit(EXIT_FAILURE);
    }

    p.input_filename = strdup(argv[1]);
    p.output_filename = strdup(argv[2]);

    if(strcmp(p.input_filename + strlen(p.input_filename) - 5, ".text") !=0 || strcmp(p.output_filename + strlen(p.output_filename) - 7, ".output") !=0){
        fprintf(stderr, "Errore: Estensione errata\n");
        exit(EXIT_FAILURE);
    }

    return p;
}

Nodo*inserisciNodo(Nodo**head, char *str){
    Nodo * nuovo = malloc(sizeof(Nodo));
    if(!nuovo){
        fprintf(stderr, "Errore: Memoria non allocata\n");
        exit(EXIT_FAILURE);
    }

    nuovo->str = strdup(str);
    nuovo->nextptr = NULL;

    if((*head) == NULL || strlen(str) < strlen((*head)->str)){
        nuovo->nextptr=(*head);
        return *head=nuovo;
    }

    Nodo*corrente=(*head);

    while(corrente->nextptr && strlen(corrente->nextptr->str) <= strlen(str)){
        corrente=corrente->nextptr;
    }
    nuovo->nextptr = corrente->nextptr;
    corrente->nextptr=nuovo;
    return (*head);
}

Nodo*readFile(FILE *fp, Nodo**head){
    char buffer[255];
    while(fscanf(fp, "%s", buffer) == 1){
        *head = inserisciNodo(head, buffer);
    }
    fclose(fp);
    return (*head);
}

void printList(Nodo*head){
    Nodo*corrente=head;
    while(corrente){
        printf("%s\n", corrente->str);
        corrente=corrente->nextptr;
    }
}

int len(Nodo*head){
    Nodo*corrente=head;
    int n=0;
    while(corrente){
        ++n;
        corrente=corrente->nextptr;
    }
    return n;
}

short *getArray(Nodo*head){
    Nodo*corrente=head;
    int n = len(head), i=0;
    short *Y = malloc(n * sizeof(short));

    if(Y == NULL){
        fprintf(stderr, "Errore: Memoria non allocata\n");
        exit(EXIT_FAILURE);
    }

    while(corrente){
        int k=0;
        for(int j=0;corrente->str[j];j++){
            if(strchr("AEIOUaeiou", corrente->str[j])){
                k++;
            }
        }
        Y[i++] = k;
        corrente=corrente->nextptr;
    }
    
    return Y;
}

void printArray(short *Y, int n){
    for(int i=0;i<n;i++){
        printf("%hu ", Y[i]);
    }
}

float filterList(Nodo**head, int n, short *Y){
    Nodo*corrente=*head;
    Nodo*precedente=NULL;

    float s=0, media=0;
    int c=0;

    for(int i=0;i<n;i++){
        s+=Y[i];
        c++;
    }

    media = s/c;

    while(corrente){
        int k=0;
        for(int j=0;corrente->str[j];j++){
            if(strchr("AEIOUaeiou", corrente->str[j])){
                k++;
            }
        }
        if(k > media){
            if(precedente == NULL){
                (*head)=corrente->nextptr;
            }else{
                precedente->nextptr = corrente->nextptr;
            }
            corrente=corrente->nextptr;
            
        }else{
            precedente=corrente;
            corrente=corrente->nextptr;
        }
    }
    return media;

}

void writeToFile(Parametri p, Nodo*head){
    FILE *fp = fopen(p.output_filename, "w");
    if(!fp){
        fprintf(stderr, "Errore: File non aperto\n");
        exit(EXIT_FAILURE);
    }
    Nodo*corrente=head;
    while(corrente){
        fprintf(fp, "%s\n", corrente->str);
        corrente=corrente->nextptr;
    }
    fclose(fp);
    printf("File scritto correttamente\n");
}

int main(int argc, char*argv[]){
    //Punto A
    Parametri p = decodeParameters(argc, argv);
    printf("====== A Stampa Parametri ======\n");
    printf("input_filename = %s\noutput_filename = %s\n", p.input_filename, p.output_filename);

    //Punto B
    printf("====== B Lista ordinata per lunghezza ======\n");
    FILE *fp = fopen(p.input_filename, "r");
    if(fp == NULL){
        fprintf(stderr, "Errore: File non aperto\n");
        exit(EXIT_FAILURE);
    }
    Nodo * X = NULL;
    X = readFile(fp, &X);
    printList(X);

    //Punto C
    printf("====== C Array Y (numero di vocali) ======\n");
    int n = len(X);
    short *Y = NULL;
    Y = getArray(X);
    printArray(Y, n);

    //Punto D
    printf("\n====== D Media di Y e lista dopo filtro ======\n");
    float m = filterList(&X, n, Y);
    printf("Media di Y: %.1f\n", m);
    printf("Contenuto di X:\n");
    printList(X);

    //Punto E
    printf("====== E Scrittura File ======\n");
    writeToFile(p, X);

    return 0;

}