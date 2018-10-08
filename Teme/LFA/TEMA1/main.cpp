#include <iostream>
#include <fstream>
using namespace std;

ifstream fin("in.in");

class state{
public:
    int id;
    char tranzitii[10][2]   /// Muchiile pe care o stare o poate avea la alta stare
    state(int id){
        this.id = id;
        for(int i = 0; i < 10; i++){
            tranzitii[i][0] = tranzitii[i][1] = 0;
        }
    }
};

int main()
{
    int n;
    int m;

    fin >> n;   /// Numarul de stari citite
    state Q[n];

    for(int i = 0; i < n; ++i){
        Q[i] = new state(i);
    }

    fin >> m;   /// Numarul de tranzitii (delta) de citit
    int stare1,stare2;
    char cuvant_tranzitie;
    for(int i = 0; i < m; ++i){
        fin >> stare1 >> stare2 >> cuvant_tranzitie;    /// Exemplu citire: ( 0 , 0 , c ) starea 0 duce in starea 0 prin c
        if(Q[stare1].tranzitii[stare2][0] == 0){        /// Verific daca din el pleaca deja o muchie in alta stare
            Q[stare1].tranzitii[stare2][0] = cuvant_tranzitie;
        } else {
            Q[stare1].tranzitii[stare2][1] = cuvant_tranzitie;
        }
    }
    return 0;
}