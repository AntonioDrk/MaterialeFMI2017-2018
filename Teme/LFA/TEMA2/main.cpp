#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


using namespace std;

///DFA-ul propriu
class Dfa{
    /// Lista de adiacenta (tranzitiile)
    vector<vector<pair<int,char>>> listaAdiacenta;
    // Starile finale
    vector<int> stariFinale;
    // Alfabetul folosit (ajuta la partitionare/minimizare)
    vector<char> alfabet;
    // Vectorul de partitii ( -> partitie = fiecarei stari ii contribuim un numar natural,
    // acel numar reprezinta partitia acelei stari, mai multe stari cu acelasi numar => toate fac parte din aceeasi partitie
    vector<int> partitions;
    // Numarul starilor
    int nrNoduri;
    // Starea initiala
    int stareInitGlob;
    bool minimizat = false;

public:
    Dfa(char*);
    void printList();
    void minimiseDfa();
    void afisarePartitii();
    void afisareDfaMinimizat();
};

Dfa::Dfa(char *nume_fisier){
    ifstream fin(nume_fisier);
    ///Testam daca putem deschide fisierul
    if(fin.fail()){
        cout << "EROARE: Deschiderea fisierului \"" << nume_fisier << "\" nu a putut fi completata";
        exit(EXIT_FAILURE);
    }
    //Citim intai si intai alfabetul cu care lucram
    int nrCaractere;
    fin >> nrCaractere;
    for (int i = 0; i < nrCaractere; ++i) {
        char charCitit;
        fin >> charCitit;
        // Il introducem in vectorul care consta alfabetul dfa-ului
        alfabet.push_back(charCitit);
    }

    int nrTranzitii;
    // Citim nr de noduri si nr de tranzitii
    fin >> nrNoduri >> nrTranzitii;
    /// Alocam in lista de adiacenta, numarul de noduri care au tranzitii
    /// Se incepe de la 0
    listaAdiacenta.resize(nrNoduri);
    // Avem doar nrNoduri de partitionat (vezi minimizarea)
    partitions.resize(nrNoduri);
    for(int i = 0; i < nrTranzitii; ++i){
        /// Starea din care incepe tranzitia
        int stareInit;
        /// Ne formam o pereche de tipul StareFinala + CaracterDeTranzit
        pair<int,char> data;
        /// Citim din fisier starea initiala + starea finala + caracterul de tranzitie
        fin >> stareInit >> data.first >> data.second;
        /// Adaugam starea finala si caracterul de tranzitie pe pozitia starii initiale
        listaAdiacenta[stareInit].push_back(data);
    }

    /// Citim starea initiala a automatului
    fin >> stareInitGlob;

    /// Citim nr de stari finale
    int nrStariFin;
    fin >> nrStariFin;

    /// Alocam un vector de nrNoduri, initializat cu 0
    /// Il folosim pentru a stoca nodurile finale
    /// Ex: Daca nodul K are pe stariFinale[K] un 1, atunci K este stare finala
    stariFinale.resize(nrNoduri,0);
    for(int i = 0; i < nrStariFin; ++i){
        int stareFin;
        fin >> stareFin;
        stariFinale[stareFin] = 1;
    }
    fin.close();

}

// Afiseaza lista de adiacenta
void Dfa::printList(){
    for(int i = 0; i < listaAdiacenta.size(); i++){
        cout << i << " :  ";
        for(int j = 0; j < listaAdiacenta[i].size(); j++){
            cout << listaAdiacenta[i][j].first << "-" << listaAdiacenta[i][j].second << "  ";
        }
        cout << '\n';
    }
}

void Dfa::minimiseDfa() {
    minimizat = true;
    //TODO 1 break into partitions the given dfa
    // TODO 1.1 Luam starile finale si le punem intr-o partitie(2) , iar pe cele nefinale in alta partitie(1)
    for (int i = 0; i < nrNoduri; ++i) {
        // Este starea i nefinala? Daca da atunci are partitia 1, daca nu atunci are partitia 2
        partitions[i] = (stariFinale[i] == 0) ? 1 : 2;
    }
    // Vectorul de partitii cu care lucram pentru a modifica partitiile
    vector<int> tmpPartitions(nrNoduri,0);
    // Vectorul pe care o sa-l folosim sa testam partitiile
    vector<int> testPartitions(nrNoduri);
    // Precum algoritmul sugereaza, partitionam pana cand instanta urmatoare
    // de partitii este egala cu instanta precedenta de partitii
    do{
        // El tine seama de penultima configuratie a partitiilor (astfel incat sa o testam cu configuratia
        testPartitions = partitions;
        // TODO 1.2 O modalitate de a lua fiecare partitie in parte (maxim al partitiei + nr de elemente pentru fiecare partitie?)
        // Partitia numerotata cu nr cel mai mare (un fel de nrPartitii)
        int nrPartitii = *max_element(partitions.begin(),partitions.end()).base();
        // Tine seama de ce numar va avea urmatoarea partitie creeata
        int indPartNoua = nrPartitii + 1;
        // i REPREZINTA PARTITIA CU CARE LUCRAM
        for(int i = 1; i <= nrPartitii; ++i){
            // Iau fiecare stare din fiecare partitie si o pun intr-un vector (sa stiu ce stari sunt in aceeasi partitie)
            vector<int> stariDinPartitii;
            // Parcurgem vectorul de partitii
            for(int j = 0; j < nrNoduri; ++j){
                if(partitions[j] == i){
                    // Bagam toate starile care au aceeasi partitie intr-un vector
                    stariDinPartitii.push_back(j);
                }
            }
            // TODO 1.2.2 Luam fiecare pereche din fiecare partitie si verificam echivalenta lor prin verificarea fiecarui caracter din alfabet
            // Daca partitia noastra consta doar dintr-o stare, o copiem si trecem mai departe
            if(stariDinPartitii.size() == 1){
                tmpPartitions[stariDinPartitii[0]] = partitions[stariDinPartitii[0]];
                continue;
            }
            // Indicele care face prima selectie (luam prima stare din vector o comparam cu restul, luam a doua si o comparam cu restul si tot asa
            for(int indPrimaSelStare = 0; indPrimaSelStare < stariDinPartitii.size(); ++indPrimaSelStare){
                // Indicele celei de a doua stari selectate
                for(int indDouaSelStare = indPrimaSelStare + 1; indDouaSelStare < stariDinPartitii.size(); ++indDouaSelStare){
                    // Prima stare cu care lucrez
                    int primaStare = stariDinPartitii[indPrimaSelStare];
                    // A doua stare cu care lucrez
                    int douaStare = stariDinPartitii[indDouaSelStare];
                    // Daca ambele au fost cumva prelucrate si sunt intr-o partitie, n-are sens sa le mai verificam odata
                    if( tmpPartitions[primaStare] != 0 && tmpPartitions[douaStare] != 0) continue;
                    // Am cele doua stari selectate, testam acuma echivalenta lor
                    bool echivalente = true;
                    // Stocam fiecare caracter din alfabet (ne folosim de el pentru a stabili echivalenta)
                    char charCurent;
                    for(int indAlfabet = 0; indAlfabet < alfabet.size(); ++indAlfabet){
                        // Luam cate un caracter din alfabet
                        charCurent = alfabet[indAlfabet];
                        // Unde duce prima stare
                        int finalPrima;
                        // Unde duce a doua stare
                        int finalDoua;
                        /* ----------- Caut unde duce prima stare pentru caracterul ales din alfabet ------------------------ */
                        for(int indTranz = 0; indTranz < listaAdiacenta[primaStare].size(); ++indTranz){
                            if(listaAdiacenta[primaStare][indTranz].second == charCurent){
                                finalPrima = listaAdiacenta[primaStare][indTranz].first;
                                break;
                            }
                        }
                        /* ---------- Caut unde duce a doua stare pentru caracterul ales din alfabet --------------------- */
                        for(int indTranz = 0; indTranz < listaAdiacenta[douaStare].size(); ++indTranz){
                            if(listaAdiacenta[douaStare][indTranz].second == charCurent){
                                finalDoua = listaAdiacenta[douaStare][indTranz].first;
                                break;
                            }
                        }
                        // DACA UNDE SE DUC CELE DOUA STARI SELECTATE DIFERA CA PARTITII => NU SUNT ECHIV
                        if(partitions[finalPrima] != partitions[finalDoua]){
                            echivalente = false;
                        }
                    }
                    // Daca sunt echivalente cele doua pot fi in aceeasi partitie
                    if(echivalente){
                        tmpPartitions[primaStare] = tmpPartitions[douaStare] = partitions[primaStare];
                    } else {
                        // Daca NU SUNT echivalente o pastram pe prima in partitia precedenta, o mutam pe a doua intr-o partitie noua
                        tmpPartitions[primaStare] = partitions[primaStare];
                        tmpPartitions[douaStare] = indPartNoua;
                        // Crestem indexul partitiei avand in vedere ca deja am creat una noua;
                        indPartNoua++;
                    }
                }
            }
        }


        // IMPORTANT UPDATAM PARTITIILE
        partitions = tmpPartitions;
        // Stergem vectorul cu care am lucrat pentru a avea unul nou
        tmpPartitions.erase(tmpPartitions.begin(),tmpPartitions.end());
        // Il initializam cu 0 peste tot (vezi if linia 144)
        tmpPartitions.resize(nrNoduri,0);
    }while(testPartitions != partitions );

    afisarePartitii();
}

// O afisare a vectorului de partitii
void Dfa::afisarePartitii(){
    cout << "PARTITIILE FINALE SUNT:\n";
    for(int i=0; i < partitions.size(); ++i){
        cout << i << " ";
    }
    cout << "\n------------------\n";
    for(int i=0; i < partitions.size(); ++i){
        cout << partitions[i] << " ";
    }
    cout << "\n";
}

void Dfa::afisareDfaMinimizat() {
    // Daca dfa-ul nostru a fost minimizat
    if(minimizat){
        int nrPartitii = *max_element(partitions.begin(),partitions.end()).base();
        for(int i = 1; i <= nrPartitii; ++i) {
            // Iau fiecare stare din fiecare partitie si o pun intr-un vector (sa stiu ce stari sunt in aceeasi partitie)
            vector<int> stariDinPartitii;
            // Parcurgem vectorul de partitii
            cout << "Partitia P" << i << " contine starile { ";
            for (int j = 0; j < nrNoduri; ++j) {
                if (partitions[j] == i) {
                    // Bagam toate starile care au aceeasi partitie intr-un vector
                    stariDinPartitii.push_back(j);
                    cout << j << " ";
                }
            }
            cout << "}\n";
            // Stocam fiecare caracter din alfabet (ne folosim de el pentru a stabili echivalenta)
            char charCurent;
            for(int indAlfabet = 0; indAlfabet < alfabet.size(); ++indAlfabet) {
                // Luam cate un caracter din alfabet
                charCurent = alfabet[indAlfabet];
                // Starea unde duce partitia i pentru caracterul charCurent
                int stareFinala;
                for(int indTranz = 0; indTranz < listaAdiacenta[stariDinPartitii[0]].size(); ++indTranz){
                    if(listaAdiacenta[stariDinPartitii[0]][indTranz].second == charCurent){
                        stareFinala = listaAdiacenta[stariDinPartitii[0]][indTranz].first;
                    }
                }

                cout << "Partitia P" << i << " duce " << charCurent << " in partitia P" << partitions[stareFinala] << '\n';
            }
        }
    }
}

int main()
{
    Dfa mainDfa("date.in");
    mainDfa.minimiseDfa();
    mainDfa.afisareDfaMinimizat();
    return 0;
}