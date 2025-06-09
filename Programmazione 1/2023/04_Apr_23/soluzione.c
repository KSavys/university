#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

typedef struct parametri{
    char *input_filename;
    int n, m;
}Parametri;

Parametri decodeParameters(int argc, char*argv[]){
    Parametri p;
    if(argc!=4){
        fprintf(stderr, "Errore: Parametri errati\n");
        exit(1);
    }

    p.n = atoi(argv[1]);
    p.m = atoi(argv[2]);
    p.input_filename = strdup(argv[3]);

    if(strcmp(p.input_filename + strlen(p.input_filename) - 4, ".txt") !=0){
        fprintf(stderr, "Errore: Estensione .txt errata\n");
        exit(1);
    }
    return p;
}

double ***readFile(FILE *fp, int n, int m){
    double ***X = calloc(n, sizeof(double**));
    if(!X){
        fprintf(stderr, "Memoria non allocata\n");
        exit(1);
    }

    for(int i=0;i<n;i++){
        X[i] = malloc(m * sizeof(double*));
        for(int j=0;j<n;j++){
            X[i][j] = malloc(sizeof(double));
            fscanf(fp, "%lf,", X[i][j]);
        }
    }
    return X;
}

void Matrix(int n, int m, double ***X){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            printf("%.2f ", *X[i][j]);
        }
        printf("\n");
    }
}

int *getArray(int n, int m, double ***X){
    int *Y = calloc(n, sizeof(int));
    if(!Y){
        fprintf(stderr, "Memoria non allocata\n");
        exit(1);
    }
    
    for(int i=0;i<n;i++){
        double max = *X[i][0], min = *X[i][0], s=0, q=0;
        int k=0;
        for(int j=0;j<m;j++){
            if(*X[i][j] > max){
                max = *X[i][j];
            }else{
                if(*X[i][j] < min){
                    min = *X[i][j];
                }
            }
            s+=*X[i][j];
            k++;
            q = s / k;
        }
        double a = q - (max-min)*0.3;
        double b = q + (max-min)*0.3; 
        int counter=0;       
        for(int j=0;j<m;j++){
            if(*X[i][j] >= a && *X[i][j] <= b){
                counter++;
            }
        }
        Y[i] = counter;
    }
    return Y;
}

void Array(int n, int *Y){
    for(int i=0;i<n;i++){
        printf("%d ", Y[i]);
    }
}

void insertionSort(int n, int *Y){
    for(int i=1;i<n;i++){
        int app = Y[i];
        int j = i-1;
        while(j>=0 && Y[j] > app){
            Y[j+1] = Y[j];
            j--;
        }
        Y[j+1] = app;
    }
}

int *getCumulative(int n, int *Y){
    int *Z = malloc(n * sizeof(int));
    if(!Z){
        fprintf(stderr, "Memoria non allocata\n");
        exit(1);
    }
    
    for(int i=0;i<n;i++){
        int s=0;
        for(int j=0;j<=i;j++){
            s+=Y[j];
        }
        Z[i] = s;
    }
    return Z;
}

void ArrayZ(int n, int *Z){
    for(int i=0;i<n;i++){
        printf("%d ", Z[i]);
    }
}

int main(int argc, char*argv[]){
    Parametri p = decodeParameters(argc, argv);
    printf("======Stampa Parametri======\nn = %d\nm = %d\nfilename = %s\n", p.n, p.m, p.input_filename);
    printf("======Stampa X====== \n");
    FILE *fp = fopen(p.input_filename, "r");
    if(!fp){
        fprintf(stderr, "Errore: File non aperto\n");
        exit(1);
    }
    double ***X = readFile(fp, p.n, p.m);
    Matrix(p.n, p.m, X);

    printf("======Stampa Y======\n");
    int *Y = getArray(p.n, p.m, X);
    Array(p.n, Y);
    printf("\n======Stampa Y ordinato======\n");
    insertionSort(p.n, Y);
    Array(p.n, Y);
    printf("\n======Stampa Z======\n");
    int *Z = getCumulative(p.n, Y);
    ArrayZ(p.n, Z);

}