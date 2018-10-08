#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

struct nod {
    int info;
    nod *next;
};

struct pol {
    int gr,coef;
    pol *next;
};

ifstream fin("in.in");

void inserareOrdonata(nod*&head, int &size, int x){
    nod* p = head;
    nod* tmp = nullptr;

    if( p == nullptr){ /// Daca nu exista HEAD
        p = new nod;
        p->info = x;
        p->next = nullptr;
        head = p;
        size++;
        return;
    }

    if(x <= head->info){    /// Daca elementul pe care incerc sa-l inserez e mai mic decat HEAD
        nod *q = new nod;
        q->info = x;
        q->next = head;
        head = q;
        size++;
        return;
    }

    while(p != nullptr){    ///Parcurg sa vad unde trebuie inserat elementul
        if(x >= p->info){
            tmp = p;
        }
        p = p->next;
    }

    if(tmp != nullptr)      ///Pe pozitia tmp (care e cu una la stanga fata de p) inseram in fata lui noul elem.
    {
        nod *q = new nod;
        q->info = x;
        q->next = tmp->next;
        tmp->next = q;
        size++;
    }

}

void inserareOrdonataPolin(pol*&head, int &size, int grad, int coef){
    pol* p = head;
    pol* tmp = nullptr;

    if( p == nullptr){ /// Daca nu exista HEAD
        p = new pol;
        p->gr = grad;
        p->coef = coef;
        p->next = nullptr;
        head = p;
        size++;
        return;
    }

    if(grad <= head->gr){    /// Daca elementul pe care incerc sa-l inserez e mai mic decat HEAD
        pol *q = new pol;
        q->gr = grad;
        q->coef = coef;
        q->next = head;
        head = q;
        size++;
        return;
    }

    while(p != nullptr){    ///Parcurg sa vad unde trebuie inserat elementul
        if(grad >= p->gr){
            tmp = p;
        }
        p = p->next;
    }

    if(tmp != nullptr)      ///Pe pozitia tmp (care e cu una la stanga fata de p) inseram in fata lui noul elem.
    {
        pol *q = new pol;
        q->gr = grad;
        q->coef = coef;
        q->next = tmp->next;
        tmp->next = q;
        size++;
    }

}

void showList(nod* head){
    nod* p = head;
    if( p == nullptr ){
        cout<< "Lista este goala";
        return;
    }
    while( p != nullptr ){
        cout << p->info << " ";
        p = p->next;
    }
}

void showListPolin(pol* head){ ///Afisarea polinomului
    pol* p = head;
    if( p == nullptr ){
        cout<< "Polinomul nu exista";
        return;
    }
    while( p != nullptr ){
        cout << p->coef << "x^" << p->gr << " " ;
        p = p->next;
    }
    cout << '\n';
}

/*void pushBack(pol *&vf, pol *&sf, int &size, int coef, int gr) {
    size ++;
    pol *p = new pol;
    p->coef = coef;
    p->gr = gr;
    p->next = nullptr;
    if(sf == nullptr) {
        vf = sf = p;
    } else {
        sf->next = p;
        sf = p;
    }
}

void pushFront(pol *&vf, pol *&sf, int &size, int coef, int gr) {
    size ++;
    pol *p = new pol;
    p->coef = coef;
    p->gr = gr;
    if(vf == nullptr) {
        vf = sf = p;
        p->urm = nullptr;
    } else {
        p->urm = vf;
        vf = p;
    }
}

void deleteAll(pol *vf, pol *sf, int &size) {
    if( vf == sf ) {
        cout << "Lista deja nu exista!" << '\n';
    } else {
        pol *p = vf;
        pol *tmp = p;
        while( p != nullptr ) {
            tmp = p->urm;
            delete p;
            p = tmp;
        }
        vf = sf;
        size = 0;
    }
}

void sortList(pol *&vf, pol *&sf, int &size) {
    pol* vf_rez,*sf_rez;
    vf_rez = sf_rez = nullptr;
    int size_rez = 0;

    int min = vf->gr;
    pol* minpointer = vf;

    while(size > 0){
        for(pol *p = vf; p != nullptr; p = p->urm){
            if(p->gr < min){
                min = p->gr;
                minpointer = p;
            }
        }
        pushBack(vf_rez,sf_rez,size_rez,minpointer->coef,minpointer->gr);
        size--;
    }
    size = size_rez;
    vf = vf_rez;
    sf = sf_rez;
}*/

void citireLista(nod *&head, int &size){
    int n;
    fin >> n;
    for(int i=0; i<n; i++){
        int x;
        fin >> x;
        inserareOrdonata(head,size,x);
    }
    showList(head);
}

void citireListaPoli(pol *&head, int &size){
    int n;
    fin >> n;
    for(int i=0; i<n; i++){
        int grad,coef;
        fin >> grad;
        fin >> coef;
        inserareOrdonataPolin(head,size,grad,coef);
    }
    showListPolin(head);
}

void problema2(){
    int size1 = 0;
    pol *head = nullptr;
    int multiplier;
    citireListaPoli(head,size1);
    fin >> multiplier;
    pol *p = head;
    while(p != nullptr){
        p->coef *= multiplier;
        p = p->next;
    }
    showListPolin(head);
}

void problema3(){
    int size1 = 0;
    pol *head = nullptr;
    int evalNumber;
    int result = 0;
    citireListaPoli(head,size1);
    fin >> evalNumber;
    pol* p = head;
    while( p != nullptr ){
        result += p->coef * pow(evalNumber, p->gr);
        p = p->next;
    }
    cout << "P(" << evalNumber << ") = " << result;
}

void problema4(){
    int size1, size2, size3;
    size1 = size2 = size3 = 0;
    pol *head1, *head2, *head3;
    head1 = head2 = head3 = nullptr;
    cout << "P(x) = ";
    citireListaPoli(head1, size1);
    cout << "+\nQ(x) = ";
    citireListaPoli(head2, size2);
    pol *p = (size1 >= size2)?head1:head2;
    while(p != nullptr){
        pol *q = (size1 <= size2)?head1:head2;
        int ok = 0;
        while(q != nullptr){
            if(p->gr == q->gr){
                int newCoef = p->coef + q->coef;
                inserareOrdonataPolin(head3, size3, p->gr, newCoef);
                ok = 1;
            }
            q = q->next;
        }
        if(ok == 0){
            inserareOrdonataPolin(head3, size3, p->gr, p->coef);
        }
        p = p->next;
    }
    showListPolin(head3);

}

int main()
{
    ///nod* head = nullptr;
    problema4();


    return 0;
}
