#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

typedef struct parametri{
    char *input_filename;
}Parametri;

typedef struct interi{
    int n;
    int m;
}Interi;


Parametri decodeParameters(int argc, char*argv[]){
    Parametri p;
    if(argc!=2){
        fprintf(stderr, "Errore: Parametri errati\n");
        exit(1);
    }

    p.input_filename = strdup(argv[1]);

    if(strcmp(p.input_filename + strlen(p.input_filename) - 4, ".csv") !=0 ){
        fprintf(stderr, "Errore: Estensione errata\n");
        exit(1);
    }
    return p;
}

Interi readHeader(FILE *fp){
    Interi in;
    fscanf(fp, "%d,%d", &in.n, &in.m);
    return in;
}

short ***readFile(Interi in, FILE *fp){
    short ***X = malloc(in.n * sizeof(short**));
    if(!X){
        fprintf(stderr, "Errore: Memoria non allocata\n");
        exit(1);
    }
    for(int i=0;i<in.n;i++){
        X[i] = malloc(in.m * sizeof(short*));
        for(int j=0;j<in.m;j++){
            X[i][j] = malloc(sizeof(short));
            fscanf(fp, "%hu,", X[i][j]);
        }
    }
    return X;
}

void Matrix(short ***X, Interi in, FILE *fp, char *simbolo){
    for(int i=0;i<in.n;i++){
        for(int j=0;j<in.m;j++){
            if(X[i][j]){
                fprintf(fp, " %3hu ", *X[i][j]);
            }else{
                fprintf(fp, " %3s ", simbolo);
            }
        }
        printf("\n");
    }
}

short *getArray(Interi in, short ***X){
    short *Y = calloc(in.n, sizeof(short));
    if(!Y){
        fprintf(stderr, "Errore: Memoria non allocata\n");
        exit(1);
    }
    for(int i=0;i<in.n;i++){
        short max = *X[i][0];
        for(int j=0;j<in.m;j++){
            if(X[i][j]){
                if(*X[i][j] > max){
                    max = *X[i][j];
                }
            }
        }
        Y[i] = max;
    }
    return Y;
}

void Array(Interi in, short *Y){
    for(int i=0;i<in.n;i++){
        printf("%hu ", Y[i]);
    }
}

void bubbleSort(Interi in, short *Y){
    for(int i=0;i<in.n-1;i++){
        for(int j=0;j<in.n-i-1;j++){
            if(Y[j] < Y[j+1]){
                short temp = Y[j];
                Y[j] = Y[j+1];
                Y[j+1] = temp;
            }
        }
    }
}

void processX(short ***X, Interi in, short *Y){
    for(int i=0;i<in.n;i++){
        for(int j=0;j<in.m;j++){
            if(*X[i][j] > (float)((Y[i]/2)+1)){
                X[i][j] = NULL;
            }
        }
    }
}

int main(int argc, char*argv[]){
    Parametri p = decodeParameters(argc, argv);
    printf("======A Stampa Parametri======\ninput_filename = %s\n", p.input_filename);
    FILE *fp = fopen(p.input_filename, "r");
    if(fp == NULL){
        fprintf(stderr, "Errore: File non aperto\n");
        exit(1);
    }
    Interi in = readHeader(fp);
    printf("======B Valori n e m======\nn = %d m = %d\n", in.n, in.m);
    short ***X = readFile(in, fp);
    printf("======B Matrice X======\n");
    Matrix(X, in, stdout, "");
    printf("======C Array Y======\n");
    short *Y = getArray(in, X);
    Array(in, Y);
    bubbleSort(in, Y);
    printf("\n======C Array Y Ordinato======\n");
    Array(in, Y);
    printf("\n======D Matrice X modificata======\n");
    processX(X, in, Y);
    Matrix(X, in, stdout, "*");
    printf("======E Stampa su standard error======\n");
    Matrix(X, in, stderr, "-");
}