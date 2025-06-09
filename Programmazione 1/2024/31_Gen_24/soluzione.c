#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct parametri{
    char *input_filename, *output_filename;
}Parametri;

typedef struct interi{
    int n, m;
}Interi;

Parametri decodeParameters(int argc, char*argv[]){
    Parametri p;
    if(argc!=3){
        fprintf(stderr, "Errore: Parametri errati\n");
        exit(1);
    }
    p.input_filename = strdup(argv[1]);
    p.output_filename = strdup(argv[2]);

    if(strcmp(p.input_filename + strlen(p.input_filename) - 4, ".txt") !=0 || strcmp(p.output_filename + strlen(p.output_filename) - 4, ".txt") !=0){
        fprintf(stderr, "Errore: Estensione errata .txt\n");
        exit(1);
    }
    return p;
}

Interi readHeader(FILE *fp){
    Interi in;
    fscanf(fp, "%d %d", &in.n, &in.m);
    return in;
}

double ***readFile(FILE *fp, Interi in){
    double ***X = malloc(in.n * sizeof(double**));
    for(int i=0;i<in.n;i++){
        X[i] = malloc(in.m * sizeof(double*));
        for(int j=0;j<in.m;j++){
            X[i][j] = malloc(sizeof(double));
            fscanf(fp, "%lf", X[i][j]);
        }
    }
    return X;
}

void Matrix(Interi in, double ***X){
    for(int i=0;i<in.n;i++){
        for(int j=0;j<in.m;j++){
            if(X[i][j]){
                printf("  %.2lf ", *X[i][j]);
            }else{
                printf("     * ");
            }
        }
        printf("\n");
    }
}

double *getArray(Interi in, double ***X){
    double *Y = calloc(in.n, sizeof(double));
    for(int i=0;i<in.n;i++){
        double s = 0.0;
        int c=0;
        for(int j=0;j<in.m;j++){
            s+=*X[i][j];
            c++;
        }
        Y[i] = s / c;
    }
    return Y;
}

void Array(Interi in, double *Y){
    for(int i=0;i<in.n;++i){
        printf("%.2lf ", Y[i]);
    }
}

void selectionSort(Interi in, double *Y){
    for(int i=0;i<in.n-1;i++){
        int min = i;
        for(int j=i+1;j<in.n;j++){
            if(Y[j] < Y[min]){
                min = j;
            }
        }
        if(min != i){
            double temp = Y[i];
            Y[i] = Y[min];
            Y[min] = temp;
        }
    }
}

void processX(Interi in, double ***X, double *Y){
    for(int i=0;i<in.n;++i){
        for(int j=0;j<in.m;j++){
            if(*X[i][j] > Y[i]){
                X[i][j] = NULL;
            }
        }
    }
}

void writeToFile(Parametri p, Interi in, double***X){
    FILE *fp = fopen(p.output_filename, "w");
    if(!fp){
        fprintf(stderr, "Errore: File non aperto\n");
        exit(1);
    }

    for(int i=0;i<in.n;i++){
        for(int j=0;j<in.m;j++){
            if(X[i][j]){
                fprintf(fp, "  %.2lf ", *X[i][j]);
            }else{
                fprintf(fp, "     * ");
            }
        }
        fprintf(fp, "\n");
    }
}

int main(int argc, char*argv[]){
    Parametri p = decodeParameters(argc, argv);
    printf("======A Stampa Parametri======\ninput_filename = %s\noutput_filename = %s\n", p.input_filename, p.output_filename);
    FILE *fp = fopen(p.input_filename, "r");
    if(!fp){
        fprintf(stderr, "Errore: File non aperto\n");
        exit(1);
    }
    Interi in = readHeader(fp);
    printf("======B Valori n e m======\nn = %d\nm = %d\n", in.n, in.m);
    double***X = readFile(fp, in);
    printf("======B Matrice X======\n");
    Matrix(in, X);
    printf("======C Array Y======\n");
    double *Y = getArray(in, X);
    Array(in, Y);
    printf("\n======C Array Y Ordinato======\n");
    selectionSort(in, Y);
    Array(in, Y);
    processX(in, X, Y);
    printf("\n======D Matrice X modificata======\n");
    Matrix(in, X);
    writeToFile(p, in, X);
}