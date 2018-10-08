#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <cstring>
using namespace std;

class AutomateMachine{

    struct Transition{
        int toState;
        char validArgument;      // Daca duce prin mai multe moduri la acelasi nod
    };

    vector< vector<Transition> > Transitions; // Multimea de conexiuni, un fel de lista de adiacenta
                                // ( 0 fiind starea zero care duce in Transitions[0].toState prin Transition[0].ValidArguments[0];
    int initState;             // Starea initiala
    vector<int> FinalStates;    // Starile finale

public:
    int LoadParams(char *fileName){     // Incarcam datele
        fstream fin(fileName);
        if(fin == NULL){ return -1;}    // -1 reprezinta o eroare la deschiderea fisierului
        int initReadState;
        fin >> initReadState;       // Citim starea initiala

        int n;
        fin >> n;

        for(int i = 0; i < n; ++i){
            int tmpValue;
            fin >> tmpValue;                    // Citim una dintre starile finale
            FinalStates.push_back(tmpValue);    // Le adaugam multimii de stari finale
        }

        fin >> n;   // Citim numarul de conexiuni
        for(int i = 0; i < n; ++i){
            char cost;
            int startState,toState;

            fin >> startState >> toState >> cost;       // Citesc starea din care incepe conexiunea, unde se termina, costul ( cuvantul prin care ajunge in starea cealalta )
            Transitions[startState].push_back(*new Transition);  // Alocam o conexiune noua ( trebuie dereferentiata )
            Transitions[startState][Transitions[startState].size() - 1].toState = toState;
            Transitions[startState][Transitions[startState].size() - 1].validArgument = cost;
        }

        fin.close();    // Nu uitam sa inchidem fisierul, foarte important
    }

    void WordTest(char *cuvant, int currentState){
        bool isFinalState = false;
        for(int i = 0; i < FinalStates.size(); ++i){
            if(currentState == FinalStates[i] && (cuvant == NULL || cuvant[0] == '\0')){       // Daca sirul de litere s-a terminat si suntem intr-un finalState afisam mesaj si return
                isFinalState = true;
            }
        }

        if( isFinalState ){
            cout << "Cuvantul apartine limbajului";
            return;
        }

        bool matchFound = false;
        int index;

        for(int i = 0; i < Transitions[currentState].size(); ++i){   // Pentru toate conexiunile ce ies din
            if ( Transitions[currentState][i].validArgument == cuvant[0] ){ // Daca prima litera are o conexiune
                matchFound = true;      // Daca am gasit unde sa mergem
                index = i;              // Salvam indexul conexiunii
                break;
            }
        }
        if( matchFound ){
            char tmp[strlen(cuvant) - 1];           // Formam o variabila temporara de dimensiunea celei vechi - 1 ( am sters o litera )
            for(int k = 0; k < strlen(cuvant); ++k){    // Copiez cuvantul fara prima litera
                tmp[k] = cuvant[k+1];
            }
            WordTest(tmp,Transitions[currentState][index].toState); // Reapelam functia recursiv
        }else{
            cout << "Cuvantul NU apartine limbajului";
            return;
        }

    }

};

int main()
{

    return 0;
}