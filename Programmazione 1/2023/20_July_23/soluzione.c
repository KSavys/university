#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned int get_random() {
    static unsigned int m_w = 424242;
    static unsigned int m_z = 242424;
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}

typedef struct parametri{
    int n, m;
    char*input_filename;
}Parametri;

Parametri decodeParameters(int argc,char*argv[]){
    Parametri p;
    if(argc!=3){
        fprintf(stderr, "Errore: Parametri errati\n");
        exit(1);
    }

    p.n = atoi(argv[1]);
    p.m = atoi(argv[2]);
    p.input_filename = NULL;

    if((p.n < 3 || p.n > 7) || (p.m < 3 || p.m > 7)){
        fprintf(stderr, "Errore: Lunghezza n o m errate\n");
        exit(1);
    }
    return p;
}

int ***getRandomMatrix(int n, int m, int h){
    int ***A = calloc(n, sizeof(int**));
    for(int i=0;i<n;i++){
        A[i] = calloc(m, sizeof(int*));
        for(int j=0;j<m;j++){
            A[i][j] = calloc(1, sizeof(int));
            *A[i][j] = (get_random() % (h + 1));
        }
    }
    return A;
}

void Matrix(int n, int m, int ***A){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(A[i][j]){
                printf("%3d ", *A[i][j]);
            }else{
                printf("  * ");
            }
        }
        printf("\n");
    }
}

void removeMax(int ***A, int n, int col){
    int indicemax = -1, max = -1;
    for(int i=0;i<n;i++){
        if(A[i][col] !=NULL && *A[i][col] > max){
            max = *A[i][col];
            indicemax = i;
        }
    }
    free(A[indicemax][col]);
    A[indicemax][col] = NULL;
}

void modifyMatrix(int ***A, int n, int m){
    for(int col=0;col<m;col++){
        for(int j=0;j<3;j++){
            removeMax(A, n, col);
        }
    }
}

int rowMinNull(int ***A, int n, int m){
    int min=m;
    int indicemin=-1;
    for(int i=0;i<n;i++){
        int minNull=0;
        for(int j=0;j<m;j++){
            if(!A[i][j]){
                minNull++;
            }
        }
        if(minNull < min){
            min = minNull;
            indicemin = i;
        }
    }
    return indicemin;
}

void riga(int m, int riga, int ***A){
    for(int i=0;i<m;i++){
        if(A[riga][i]){
            printf("%3d ", *A[riga][i]);
            }else{
                printf("  * ");
            }
        }
}


int main(int argc, char*argv[]){
    Parametri p = decodeParameters(argc, argv);
    printf("Punto A - Parametri inseriti:\nn=%d\nm=%d\n", p.n, p.m);
    int h=0;
    printf("Inserisci un numero compreso tra 10 e 100:\n");
    scanf("%d", &h);
    if(h < 10 || h > 100){
        fprintf(stderr, "Errore: h non compreso fra 10 e 100\n");
        exit(1);
    }
    printf("Punto B - Contenuto di A:\n");
    int ***A = getRandomMatrix(p.n, p.m, h);
    Matrix(p.n, p.m, A);
    printf("Punto C - Contenuto di A dopo la modifica:\n");
    modifyMatrix(A, p.n, p.m);
    Matrix(p.n, p.m, A);
    printf("Punto D - Riga con minor numero di NULL:\n");
    int Riga=0;
    Riga = rowMinNull(A, p.n, p.m);
    riga(p.m, Riga, A);
    return 0;
}


