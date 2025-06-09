#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX 50

typedef struct parametri{
    char input_filename[MAX];
    char output_filename[MAX];
    char c;
}Parametri;

Parametri decodeParameters(int argc, char*argv[]){
    Parametri p;
    if(argc!=4){
        fprintf(stderr, "Errore: Parametri errati\n");
        exit(1);
    }
    strcpy(p.input_filename, argv[1]);
    strcpy(p.output_filename, argv[2]);
    p.c = argv[3][0];
    return p;
}

typedef struct nodo{
    char valore;
    struct nodo*nextptr;
}Nodo;

Nodo*inserisciNodo(Nodo**L, char valore){
    Nodo*nuovo=malloc(sizeof(Nodo));
    nuovo->valore = valore;
    nuovo->nextptr = NULL;

    if(*L == NULL){
        *L = nuovo;
    }else{
        Nodo*corrente=*L;
        while(corrente->nextptr !=NULL){
            corrente=corrente->nextptr;
        }
        corrente->nextptr = nuovo;
    }
    return *L;
}

Nodo*readFile(FILE *fp, Nodo**L){
    char buffer;
    while(fscanf(fp, "%c", &buffer) == 1){
        *L = inserisciNodo(L, buffer);
    }
    fclose(fp);
    return *L;
}

void List(Nodo*L){
    Nodo*corrente=L;
    while(corrente){
        printf("%c", corrente->valore);
        corrente=corrente->nextptr;
    }
}

int countOccurrences(Nodo**L, char carattere){
    Nodo*corrente=*L;
    int o=0;
    while(corrente){
        if(corrente->valore == carattere){
            ++o;
        }
        corrente=corrente->nextptr;
    }
    return o;
}

void processL(Nodo**L, int o){
    Nodo*corrente=*L;
    Nodo*precedente=NULL;
    while(corrente){
        int p = countOccurrences(L, corrente->valore);
        if(p<o){
            precedente=corrente;
            corrente=corrente->nextptr;
        }else{
            if(precedente == NULL){
                *L=corrente->nextptr;
            }else{
                precedente -> nextptr = corrente->nextptr;
            }
            corrente=corrente->nextptr;
        }
    }
}

void writeToFile(Parametri p, Nodo*L){
    FILE * fp = fopen(p.output_filename, "w");
    if(!fp){
        fprintf(stderr, "Errore: File non aperto\n");
        exit(1);
    }
    Nodo*corrente=L;
    while(corrente){
        fprintf(fp, "%c", corrente->valore);
        corrente=corrente->nextptr;
    }
}

int main(int argc, char*argv[]){
    Parametri p = decodeParameters(argc, argv);
    printf("==========PUNTO A==========\ninput_filename = %s\noutput_filename = %s\nvalore di c: %c\n", p.input_filename, p.output_filename, p.c);
    printf("==========PUNTO B==========\nContenuto della lista:\n");
    FILE * fp = fopen(p.input_filename, "r");
    if(!fp){
        fprintf(stderr, "Errore: File non aperto\n");
        exit(1);
    }
    Nodo*L = NULL;
    L = readFile(fp, &L);
    List(L);
    int o = countOccurrences(&L, p.c);
    printf("==========PUNTO C==========\n");
    printf("Occorrenze di A in L: %d\n", o);
    processL(&L, o);
    printf("==========PUNTO D==========\nContenuto della lista:\n");
    List(L);
    writeToFile(p, L);

}
