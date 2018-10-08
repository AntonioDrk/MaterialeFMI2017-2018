#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
using namespace std;

class AutomatFD{

    int nrNoduri;                                    /// numar noduri
    int startNode;
    vector<int> finalNodes;                         /// lista nodurilor finale
    vector<vector<pair<int,char>>> listAdiacent;    /// lista adiacenta

public:
    AutomatFD();
    bool testareCuv(int stareCurenta, char *cuvant);
    void printList();
    int getStareInit();
};

AutomatFD::AutomatFD(){
    nrNoduri = 0;
    int nrMuchii,nrNoduriFinale;

    ifstream fin("in.in");

    fin >> nrNoduri >> nrNoduriFinale >> nrMuchii;
    fin >> startNode;

    listAdiacent.resize(nrNoduri);
    finalNodes.resize(nrNoduriFinale,0);

    for(int i = 0; i < nrNoduriFinale; i++){
        int x;
        fin >> x;
        finalNodes[x] = 1;
    }

    for(int i = 0; i < nrMuchii; i++){
        int x;
        pair<int,char> data;
        fin >> x >> data.first >> data.second;
        listAdiacent[x].push_back(data);
    }

    fin.close();
}

void AutomatFD::printList(){
    for(int i = 0; i < listAdiacent.size(); i++){
        for(int j = 0; j < listAdiacent[i].size(); j++){
            cout << i << " :    " << listAdiacent[i][j].first << "-" << listAdiacent[i][j].second << "  ";
        }
        cout << '\n';
    }
}

bool AutomatFD::testareCuv(int stareCurenta, char *cuvant){
    cout << "WORKING ON : : :  "<< cuvant << "\n" << "ON STATE : : :   " << stareCurenta << "\n\n";
    if(cuvant[0] == '\0'){
        if(finalNodes[stareCurenta] == 1){
            return true;
        }
        return false;
    }
    for(int j = 0; j < listAdiacent[stareCurenta].size(); j++){
        if(listAdiacent[stareCurenta][j].second == cuvant[0]){  /// Primul caracter al cuvantului, ne trimite undeva?
            return testareCuv(listAdiacent[stareCurenta][j].first,cuvant + 1);
        }
    }
    return false;
}

int AutomatFD::getStareInit(){
    return startNode;
}

int main()
{
    AutomatFD automat1 = *new AutomatFD();
    char cuv[1000];
    bool _exit = false;

    while(!_exit){

        cout << "Introduceti un cuvant pentru AFD: ";
        cin >> cuv;
        cout << "\n\n";

        if( strcmp(cuv,"quit") == 0 || strcmp(cuv,"exit") == 0){
            _exit = true;
            break;
        }

        if(strcmp(cuv,"alpha") == 0 || strcmp(cuv,"alfa") == 0){
            strcpy(cuv,"");
        }

        if(automat1.testareCuv(automat1.getStareInit(),cuv)){
            cout << "DA" << "\n\n";
        }else {
            cout << "NU" << "\n\n";
        }

    }
    return 0;
}