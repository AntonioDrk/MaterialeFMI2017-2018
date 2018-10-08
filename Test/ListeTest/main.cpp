#include <iostream>

using namespace std;

struct nod{
    int info;   /// Informatia stocata in nod
    nod *next; /// Pointer la urmatorul nod
};

void pushFront(nod*& head, int info){     /// *& pointer cu referinta, astfel incat,
                                         /// cand modific head-ul in functie, sa fie modificat si inafara functiei
    nod *p = new nod;   /// Aloc memoria necesara unui nod si o stochez in pointerul p
    p->info = info;   /// Atribui informatia in nodul nou creat
    p->next = head;   /// Pentru ca adaug la inceput, noul nod trebuie sa fie inaintea head-ului, grafic ar fi ( p->head->...)
    head = p;         /// Pentru ca noul nod e la inceput => lista are un head nou deci trebuie sa updatam head-ul
}

void writeList(nod* head){
    nod *p = head;
    while(p != nullptr){
        cout << p->info << " ";
        p = p->next;
    }
    cout << '\n';
}

int main()
{

    return 0;
}
