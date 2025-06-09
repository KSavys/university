#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#define MAX 255

typedef struct parametri{
    char *input_filename;
    char *output_filename;
}Parametri;

typedef struct nodo{
    char nome[MAX];
    char cognome[MAX];
    int numero_conto;
    int anno_apertura;
    float saldo;
    struct nodo*nextptr;
}Nodo;

Parametri readInput(int argc, char*argv[]){
    Parametri p;
    if(argc!=3){
        fprintf(stderr, "Errore: Parametri errati\n");
        exit(EXIT_FAILURE);
    }

    p.input_filename = strdup(argv[1]);
    p.output_filename = strdup(argv[2]);

    if(strcmp(p.input_filename + strlen(p.input_filename) - 4, ".txt") !=0 || strcmp(p.output_filename + strlen(p.output_filename) - 4, ".txt") !=0){
        fprintf(stderr, "Errore: Estensione .txt errata\n");
        exit(EXIT_FAILURE);
    }
    return p;
}

Nodo*inserisciNodo(Nodo**head, char *nome, char *cognome, int numero_conto, int anno_apertura, float saldo){
    Nodo *nuovo = calloc(1, sizeof(Nodo));
    if(!nuovo){
        fprintf(stderr, "Errore: Memoria non allocata\n");
        exit(1);
    }
    strcpy(nuovo->nome, nome);
    strcpy(nuovo->cognome, cognome);
    nuovo->numero_conto=numero_conto;
    nuovo->anno_apertura=anno_apertura;
    nuovo->saldo=saldo;
    nuovo->nextptr=NULL;

    if((*head) == NULL || nuovo->anno_apertura < (*head)->anno_apertura){
        nuovo->nextptr=(*head);
        return *head=nuovo;
    }

    Nodo*corrente=(*head);

    while(corrente->nextptr && corrente->nextptr->anno_apertura <= nuovo->anno_apertura){
        corrente=corrente->nextptr;
    }
    nuovo->nextptr = corrente->nextptr;
    corrente->nextptr = nuovo;
    return (*head);
}

Nodo*readFile(FILE *fp, Nodo **head){
    char nome[255], cognome[255];
    int anno_apertura, numero_conto;
    float saldo;

    while(fscanf(fp, "%s %s %d %d %f", nome, cognome, &numero_conto, &anno_apertura, &saldo) == 5){
        (*head) = inserisciNodo(head, nome, cognome, numero_conto, anno_apertura, saldo);
    }
    fclose(fp);
    return (*head);
}

void List(Nodo*head){
    Nodo*corrente=head;
    while(corrente){
        printf("%s %s %d %d %.2f\n", corrente->nome, corrente->cognome, corrente->numero_conto, corrente->anno_apertura, corrente->saldo);
        corrente=corrente->nextptr;
    }
}

float getMax(Nodo**head){
    Nodo*corrente=*head;
    float max = (*head)->saldo;

    while(corrente){
        if(corrente->saldo > max){
            max = corrente->saldo;
        }
        corrente=corrente->nextptr;
    }
    return max;
}

float calcoloX(Nodo*head, float max){
    float min = (2023 - head->anno_apertura) / 5.0;
    if(min > 1.0){
        min = 1.0;
    }
    return min * (head->saldo / max);
}

int len(Nodo*head){
    int n=0;
    Nodo*corrente=head;
    while(corrente){
        ++n;
        corrente=corrente->nextptr;
    }
    return n;
}

void removeAccount(Nodo **head){
    float maxSaldo = getMax(head), maxX = 0;
    Nodo *corrente = *head;

    while(corrente){
        float x = calcoloX(corrente, maxSaldo);
        if(x > maxX){
            maxX = x;
        }
        corrente = corrente->nextptr;
    }

    corrente = *head;
    Nodo *precedente = NULL;

    while(corrente){
        float x = calcoloX(corrente, maxSaldo);
        if(x == maxX){
            if(!precedente){
                *head = corrente->nextptr;
            }else{
                precedente->nextptr = corrente->nextptr;  
            }
            corrente = corrente->nextptr;
        }else{
            precedente = corrente;
            corrente = corrente->nextptr;
        }
    }
}

void writeFile(Parametri p, Nodo*head){
    FILE *fp = fopen(p.output_filename, "w");
    if(!fp){
        fprintf(stderr, "Errore: FILE non aperto\n");
        exit(1);
    }

    Nodo*corrente=head;
    while(corrente){
        fprintf(fp, "%s %s %d %d %.2f\n", corrente->nome, corrente->cognome, corrente->numero_conto, corrente->anno_apertura, corrente->saldo);
        corrente=corrente->nextptr;
    }
    fclose(fp);
    printf("File scritto correttamente.\n");
}

int main(int argc, char*argv[]){
    Parametri p = readInput(argc, argv);
    printf("Punto A:\n");
    printf("input = %s\noutput = %s", p.input_filename, p.output_filename);
    printf("\nPunto B:\n");
    FILE *fp = fopen(p.input_filename, "r");
    if(!fp){
        fprintf(stderr, "Errore: FILE non aperto\n");
        exit(1);
    }
    Nodo*A=NULL;
    A = readFile(fp, &A);
    List(A);
    int n = len(A);
    int h = n / 2;
    float max = getMax(&A);
    for(int i=0;i<h;i++){
        removeAccount(&A);
    }
    printf("\nPunto D:\n");
    writeFile(p, A);

}