#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX 255

typedef struct parametri{
    char *input_filename, *output_filename;
}Parametri;

Parametri readInput(int argc, char*argv[]){
    Parametri p;
    if(argc!=3){
        fprintf(stderr, "Errore: Parametri errati\n");
        exit(1);
    }
    p.input_filename = strdup(argv[1]);
    p.output_filename = strdup(argv[2]);
    if(strcmp(p.input_filename + strlen(p.input_filename) - 4, ".txt") !=0 || strcmp(p.output_filename + strlen(p.output_filename) - 4, ".txt") !=0){
        fprintf(stderr, "Errore: Estensione .txt invalida\n");
        exit(1);
    }
    return p;

}

typedef struct nodo{
    char nome[255], cognome[255];
    int eta, peso, altezza;
    char sesso;
    struct nodo*nextptr;
}Nodo;

Nodo*inserisciPerEta(Nodo**A, char *nome, char*cognome, int eta, int peso, int altezza, char sesso){
    Nodo*nuovo=malloc(sizeof(Nodo));
    strcpy(nuovo->nome, nome);
    strcpy(nuovo->cognome, cognome);
    nuovo->eta=eta;
    nuovo->peso=peso;
    nuovo->altezza=altezza;
    nuovo->sesso=sesso;
    nuovo->nextptr=NULL;

    if(*A == NULL || nuovo->eta < (*A)->eta){
        nuovo->nextptr=*A;
        return *A=nuovo;
    }

    Nodo*corrente=*A;
    while(corrente->nextptr && corrente->nextptr->eta <= nuovo->eta){
        corrente=corrente->nextptr;
    }

    nuovo->nextptr = corrente->nextptr;
    corrente->nextptr=nuovo;
    return *A;
}

Nodo*readFile(Nodo**A, FILE *fp){
    char nome[MAX], cognome[MAX], sesso;
    int eta, peso, altezza;
    while(fscanf(fp, "%s %s %d %d %d %c", nome, cognome, &eta, &peso, &altezza, &sesso) == 6){
        *A = inserisciPerEta(A, nome, cognome, eta, peso, altezza, sesso);
    }
    fclose(fp);
    return *A;
}

void List(Nodo*A){
    Nodo*corrente=A;
    while(corrente){
        printf("%s %s %d %d %d %c\n", corrente->nome, corrente->cognome, corrente->eta, corrente->peso, corrente->altezza, corrente->sesso);
        corrente=corrente->nextptr;
    }
}

float imc(Nodo*A){
    float altezza = (float)A->altezza / 100;
    return (float)A->peso / (altezza * altezza);
}

Nodo*getMax(Nodo**A){
    Nodo*corrente=*A;
    Nodo*max = *A;
    while(corrente){
        if(imc(corrente) > imc(max)){
            max = corrente;
        }
        corrente=corrente->nextptr;
    }
    return max;
}

Nodo*inserisciInTesta(Nodo**B, char *nome, char*cognome, int eta, int peso, int altezza, char sesso){
    Nodo*nuovo=malloc(sizeof(Nodo));
    strcpy(nuovo->nome, nome);
    strcpy(nuovo->cognome, cognome);
    nuovo->eta=eta;
    nuovo->peso=peso;
    nuovo->altezza=altezza;
    nuovo->sesso=sesso;
    nuovo->nextptr=*B;
    *B=nuovo;
    return *B;
}

void rimuoviNodo(char *nome, Nodo**A){
    Nodo*corrente=*A;
    Nodo*precedente=NULL;
    while(corrente){
        if(strcmp(corrente->nome, nome) == 0){
            if(precedente == NULL){
                *A = corrente->nextptr;
            }else{
                precedente->nextptr = corrente->nextptr;
            }
            corrente=corrente->nextptr;
        }else{
            precedente=corrente;
            corrente=corrente->nextptr;
        }
    }
}

void writeFile(Parametri p, Nodo*B){
    FILE * fp = fopen(p.output_filename, "w");
    if(!fp){
        fprintf(stderr, "Errore: File non aperto\n");
        exit(1);
    }
    Nodo*corrente=B;
    while(corrente){
        fprintf(fp, "%s %s %d %d %d %c\n", corrente->nome, corrente->cognome, corrente->eta, corrente->peso, corrente->altezza, corrente->sesso);
        corrente=corrente->nextptr;
    }
    fclose(fp);
}



int main(int argc, char*argv[]){
    Parametri p = readInput(argc, argv);
    printf("=======PUNTO A=======\n");
    printf("input = %s, output = %s\n", p.input_filename, p.output_filename);
    printf("=======PUNTO B=======\n");
    FILE * fp = fopen(p.input_filename, "r");
    if(!fp){
        fprintf(stderr, "Errore: File non aperto\n");
        exit(1);
    }
    Nodo*A = NULL;
    A = readFile(&A, fp);
    List(A);
    Nodo*max = getMax(&A);
    printf("=======PUNTO C=======\n");
    printf("%s %s %d %d %d %c\n", max->nome, max->cognome, max->eta, max->peso, max->altezza, max->sesso);
    printf("=======PUNTO D=======\n");
    Nodo*B = NULL;
    for(int i=0;i<3;i++){
        Nodo*max = getMax(&A);
        inserisciInTesta(&B, max->nome, max->cognome, max->eta, max->peso, max->altezza, max->sesso);
        rimuoviNodo(max->nome, &A);
    }
    printf("A:\n");
    List(A);
    printf("B:\n");
    List(B);
    writeFile(p, B);

}