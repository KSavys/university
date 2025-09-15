#include <iostream>
#include <cstring>

using namespace std;

int somma(int *A, int *B) {
    return *A + *B;
}

int main(void) {
    int n = 5;
    int &x = n;

    cout << "n = " << n << endl;
    cout << "x = " << x << endl;
    cout << "x (indirizzo) = " << &x << endl;

    char c;
    char *p = &c;

    if (p == NULL)
        cout << "il carattere è NULL\n";
    else
        cout << "il carattere non è NULL\n";
    
    int i = 100;
    int *ptr1 = &i;
    int **ptr2 = &ptr1;

    cout << "i3 = " << ptr2 << endl;

    const char* str2 = "Io sono Leseratte";
    cout << str2 << endl;

    char alfabeto[6] = "ABCDE";
    char *p2;
    p2 = &alfabeto[2];
    cout << *p2 << endl;
    *p2++;
    cout << *p2 << endl;
    *p2--;
    *p2--;
    cout << *p2 << endl;

    
    int A = 5;
    int B = 5;

    int calcolo = somma(&A, &B);
    cout << "La somma è: " << calcolo << endl;

    //Allocazione di memoria

    char *pt = new char[100];

    int *Blocco;
    Blocco = new int[100];

    char str[] = "Io sono KSavys, Greetings from Italy";
    char str = {"ciao"};
    int len = strlen(str);
    char *ptr = new char[len + 1];

    strcpy(ptr, str);
    cout << "ptr = " << ptr << endl; 
    delete ptr;
    return 0;

}

