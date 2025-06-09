#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#define MAX 50

typedef struct parametri{
    char*input_filename;
    char*output_filename;
}Parametri;

typedef struct persona{
    char nome[MAX];
    char cognome[MAX];
    int eta;
    float altezza;
}Persona;

int readHeader(FILE *fp){
    int n1=0;
    fscanf(fp, "%d", &n1);
    return n1;
}

Persona *readFile(int n, FILE *fp){
    Persona*array = calloc(n, sizeof(Persona));
    if(!array){
        fprintf(stderr, "Errore: Memoria non allocata\n");
        exit(EXIT_FAILURE);
    }
    for(int i=0;i<n;i++){
        fscanf(fp, "%s %s %d %f", array[i].nome, array[i].cognome, &array[i].eta, &array[i].altezza);
    }
    return array;
    fclose(fp);
}

void printArray(int n, Persona*array){
    for(int i=0;i<n;i++){
        printf("%d. Nome: %s, Cognome: %s, Eta': %d, Altezza: %.2f\n", i+1, array[i].nome, array[i].cognome, array[i].eta, array[i].altezza);
    }
}

Parametri decodeParameters(int argc, char*argv[]){
    Parametri p;
    if(argc!=3){
        fprintf(stderr, "Errore: Parametri errati\n");
        exit(EXIT_FAILURE);
    }
    p.input_filename = strdup(argv[1]);
    p.output_filename = strdup(argv[2]);
    if(strcmp(p.input_filename + strlen(p.input_filename) - 4, ".txt" )!=0 || strcmp(p.output_filename + strlen(p.output_filename) - 4, ".txt" )!=0 ){
        fprintf(stderr, "Errore: ESTENSIONE ERRATA\n");
        exit(EXIT_FAILURE);
    }
    return p;
}

int *extractAges(Persona *array, int n){
    int *Z = calloc(n, sizeof(int));
    if(!Z){
        fprintf(stderr, "Errore: Memoria non allocata\n");
        exit(EXIT_FAILURE);
    }

    for(int i=0;i<n;i++){
        Z[i] = array[i].eta;
    }
    return Z;   
}

int sortArray(int n, int *Z){
    if(n % 2 == 0){
        fprintf(stderr, "\nErrore: L'array non e' dispari\n");
        exit(EXIT_FAILURE);
    }

    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(Z[j] > Z[j+1]){
                int temp = Z[j];
                Z[j] = Z[j+1];
                Z[j+1] = temp;
                }
            }
        }
    return Z[n/2];
}

float calculateAverageHeight(Persona*array, int med, int n){
    float s=0;
    int c=0;
    for(int i=0;i<n;i++){
        if(array[i].eta > med){
            s+=array[i].altezza;
            c++;
        }
    }
    return (float) s / c;
}

void printArrayZ(int n, int *Z){
    for(int i=0;i<n;i++){
        printf("%d ", Z[i]);
    }
}

void writeOutput(Parametri p, Persona*array, float m, int n){
    FILE *fp = fopen(p.output_filename, "w");
    if(!fp){
        fprintf(stderr, "Errore: FILE non aperto\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < n; i++){
        if(array[i].altezza > m){
            fprintf(fp, "%s %s, Eta': %d, Altezza: %.2f\n", array[i].nome, array[i].cognome, array[i].eta, array[i].altezza);
        }
    }

    printf("File scritto correttamente.\n");
    fclose(fp);
}

int main(int argc, char*argv[]){
    Parametri p = decodeParameters(argc, argv);
    printf("======A Stampa Parametri======\ninput_filename = %s\noutput_filename = %s", p.input_filename ,p.output_filename);
    FILE *fp = fopen(p.input_filename, "r");
    if(!fp){
        fprintf(stderr, "Errore: FILE non aperto\n");
        exit(1);
    
    }
    int n=0;
    n = readHeader(fp);
    printf("\n======B Valori letti dall'header======\n");
    printf("n = %d\n", n);
    printf("\n======B Contenuto dell'array di strutture======\n");
    Persona *array = NULL;
    array = readFile(n, fp);
    printArray(n, array);
    printf("\n======C Array Z (eta')======\n");
    int *Z = NULL;
    Z = extractAges(array, n);
    printArrayZ(n, Z);
    int mediana = 0;
    mediana = sortArray(n, Z);
    printf("\n======C Array Z Ordinato======\n");
    printArrayZ(n, Z);
    printf("\nMediana delle eta': %d\n", mediana);
    printf("======D Altezza media delle persone con eta' superiore alla mediana======\n");
    float m = 0;
    m = calculateAverageHeight(array, mediana, n);
    printf("Media: %.2f", m);
    printf("\n======E Scrittura su file risultato.txt======\n");
    writeOutput(p, array, m, n);


}