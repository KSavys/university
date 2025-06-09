#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#define vocali "aeiou"

unsigned int get_random() {
    static unsigned int m_w = 424242;
    static unsigned int m_z = 242424;
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}

typedef struct parametri{
    int min, max, n;
}Parametri;


Parametri decodeParameters(int argc, char*argv[]){
    Parametri p;
    if(argc!=4){
        fprintf(stderr, "Errore: Parametri errati\n");
        exit(1);
    }
    p.min = atoi(argv[1]),
    p.max = atoi(argv[2]);
    p.n = atoi(argv[3]);
    
    if(p.min < 7 || p.min > 12){
        fprintf(stderr, "Errore: Min errato\n");
        exit(1);
    }
    if(p.max < 7 || p.max > 12){
        fprintf(stderr, "Errore: Min errato\n");
        exit(1);
    }
    if(p.min > p.max){
        fprintf(stderr, "MIN deve essere minore di Max\n");
        exit(1);
    }

    if(p.n < 0){
        fprintf(stderr, "n deve essere positivo\n");
        exit(1);
    }
    return p;
}

char *generateString(int x){
    char *str = malloc((x + 1) * sizeof(char));
    for(int i=0;i<x;i++){
        str[i] = vocali[get_random() % 5];
    }
    str[x] = '\0';
    return str;
}

char **makeArray(int n, Parametri p){
    char **A = malloc(n * sizeof(char*));
    for(int i=0;i<n;i++){
        int x = p.min + (get_random() % (p.max - p.min + 1));
        A[i] = generateString(x);
    }
    return A;
}

void Array(int n, char **A){
    for(int i=0;i<n;i++){
        printf("%s\n", A[i]);
    }
}

void sortArray(int n, char**A){
    for(int i=1;i<n;i++){
        char *app = A[i];
        int j = i-1;
        while(j>=0 && A[j+1] > app){
            A[j+1] = A[j];
            j--;
        }
        A[j+1] = app;
    }
}

char *concatString(int n, char**A){
    int len=0;
    for(int i=0;i<n;i++){
        len+=strlen(A[i]);
    }
    char *str = malloc((len + 1) * sizeof(char));
    for(int i=0;i<n;i++){
        strcat(str, A[i]);
    }
    str[len] = '\0';
    return str;
}

void replaceCharacters(int len, char *str){
    for(int i=0;i<len;i++){
        if(str[i] == 'u' && str[i-1] == 'e'){
            str[i] = '*';
        }
    }
}

int main(int argc, char*argv[]){
    Parametri p = decodeParameters(argc, argv);
    printf("Punto A - Parametri inseriti: min=%d, max=%d, n=%d\n", p.min, p.max, p.n); 
    printf("Punto B:\n");
    char ** A = NULL;
    A = makeArray(p.n, p);
    Array(p.n, A);
    sortArray(p.n, A);
    printf("Punto C:\n");
    char *str = NULL;
    str = concatString(p.n, A);
    printf("%s\n", str);
    printf("Punto D:\n");
    int len = strlen(str);
    replaceCharacters(len, str);
    printf("%s\n", str);
}