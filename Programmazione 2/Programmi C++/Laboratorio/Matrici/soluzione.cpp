#include <iostream>
using namespace std;

class Matrice{
private:
    int righe, colonne;
    int **dati;
public:
    Matrice(int righe = 2, int colonne = 3) : righe(righe), colonne(colonne){
        dati = new int*[righe];
        for(int i=0;i<righe;i++){
            dati[i] = new int[colonne]{0};
        }
    }

    Matrice(const Matrice &mtx) : righe(mtx.righe), colonne(mtx.colonne){
        dati = new int*[righe];
        for(int i=0;i<righe;i++){
            dati[i] = new int[colonne];
            for(int j=0;j<colonne;j++){
                dati[i][j] = mtx.dati[i][j];
            }
        }
    }
    
    ~Matrice(){
        for(int i=0;i<righe;i++) delete[] dati[i];
        delete [] dati;
    }


    void acquisici() {
        for(int i=0;i<righe;++i){
            for(int j=0;j<colonne;++j){
                cin >> dati[i][j];
            }
        }
    }

    friend ostream& operator<<(ostream&out, const Matrice &mtx){
        for(int i=0;i<mtx.righe;i++){
            for(int j=0;j<mtx.colonne;j++){
                out << mtx.dati[i][j] << "  ";
            }
            out << endl;
        }
        return out;
    }

    Matrice& operator+(const Matrice &mtx){
        Matrice*risultato = new Matrice(righe, colonne);
        for(int i=0;i<righe;i++){
            for(int j=0;j<colonne;j++){
                risultato->dati[i][j] = dati[i][j] + mtx.dati[i][j];
            }
        }
        return *risultato;
    }

    Matrice& operator*(const Matrice &mtx){
        Matrice*risultato = new Matrice(righe, colonne);
        for(int i=0;i<righe;i++) {
            for(int j=0;j<colonne;j++) {
                risultato->dati[i][j] = dati[i][j] * mtx.dati[i][j];
            }
        }
        return *risultato;
    }

    Matrice & operator=(const Matrice&mtx){
        if(this!=&mtx){
            for(int i=0;i<righe;i++) delete[] dati[i];
            delete [] dati;
            righe = mtx.righe;
            colonne = mtx.colonne;
            dati = new int*[righe];
            for(int i=0;i<righe;i++){
                dati[i] = new int[colonne];
                for(int j=0;j<colonne;j++){
                    dati[i][j] = mtx.dati[i][j];
                }
            }
        }
        return *this;
    }
}; 
int main(void) {
    Matrice A, B, C, D;
    cout << "Inserire i (6) elementi della matrice 2X3 in sequenza: ";
    A.acquisici();
    cout << "Inserire i (6) elementi della matrice 2X3 in sequenza: ";
    B.acquisici();
    cout << endl;
    cout << "Matrice A:" << endl;
    cout << A;
    cout << endl;
    cout << "Matrice B:" << endl;
    cout << B;
    cout << endl;
    cout << "C = A + B" << endl;
    C = A + B;
    cout << C;
    cout << endl;
    cout << "C = A * B" << endl;
    D = A * C;
    cout << D;
    return 0;
}