#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("in.in");

struct nod{
    int x;
    nod* urm;
};

void pushBack(nod *&vf, nod *&sf,int &size,int x) {
    size ++;
    nod *p = new nod;
    p->x = x;
    p->urm = nullptr;
    if(sf == nullptr) {
        vf = sf = p;
    } else {
        sf->urm = p;
        sf = p;
    }
}

void pushFront(nod *&vf, nod *&sf,int &size,int x) {
    size ++;
    nod *p = new nod;
    p->x = x;
    if(vf == nullptr) {
        vf = sf = p;
        p->urm = nullptr;
    } else {
        p->urm = vf;
        vf = p;
    }
}

void writeList(nod *vf, nod *sf) {
    if( vf == sf ) {
        cout << "Lista este goala";
    } else {
        nod *p = vf;
        while( p != nullptr ) {
            cout << p->x << " ";
            p = p->urm;
        }
        cout << '\n';
    }
}

void insertAt(nod *vf, nod *sf,int &size, int x, int ind) {
    if( ind > size ){

        cout << "Indicele nu poate fi mai mare de " << size << '\n';
        cout << "Indexarea incepe de la 0!" << '\n';
        return;
    } else {
        if( ind == 0 ){
            pushFront(vf, sf, size, x);
            return;
        }
        if( ind == size){
            pushBack(vf, sf, size, x);
            return;
        }
        int c = 0;
        nod *p = vf;
        nod *q = new nod;
        q->urm = nullptr;
        q->x = x;
        while( c < ind - 1 ) {
            p = p->urm;
            c++;
        }
        q->urm = p->urm;
        p->urm = q;
        size++;
    }
}

bool searchElement(nod *vf, int x) {
    nod *p = vf;
    while( p != nullptr ) {
        if( p->x == x ) {
            return true;
        }
        p = p->urm;
    }
    return false;
}

int searchElementAt(nod *vf,int &size,int ind) {
    if( ind >= size ){
        cout << "Indicele nu poate fi mai mare de " << size << '\n';
        cout << "Indexarea incepe de la 0!" << '\n';
    } else {
        nod *p = vf;
        int c = 0;
        while( c < ind ) {
            p = p->urm;
            c++;
        }
        return p->x;
    }
}

void deleteElement(nod *vf,int &size,int x){
    if(searchElement(vf,x)){
        nod *p = vf;
        while( p != nullptr ) {
            if( p->urm->x == x ) {
                nod* q = p->urm->urm;
                delete p->urm;
                p->urm = q;
                size--;
                return;
            }
            p = p->urm;
        }
    }
}

void deleteElementAt(nod* vf, int &size, int ind){
    if( ind >= size && ind < 0){
        cout << "Indicele nu poate fi mai mare de " << size << '\n';
        cout << "Indexarea incepe de la 0!" << '\n';
    } else {
        nod *p = vf;
        int c = 0;
        while( c < ind - 1 ) {
            p = p->urm;
            c++;
        }
        nod* q = p->urm->urm;
        delete p->urm;
        p->urm = q;
        size--;
    }
}

void deleteAll(nod *vf, nod *sf, int &size) {
    if( vf == sf ) {
        cout << "Lista deja nu exista!" << '\n';
    } else {
        nod *p = vf;
        nod *tmp = p;
        while( p != nullptr ) {
            tmp = p->urm;
            delete p;
            p = tmp;
        }
        vf = sf;
        size = 0;
    }
}

nod* suma_liste(nod* vf1, nod *vf2){
    nod *p,*q,*vf_rezultat,*sf_rezultat;
    vf_rezultat = sf_rezultat = nullptr;
    int size_rezultat = 0;
    p = vf1;
    q = vf2;
    int sum_cifre,cifra1,cifra2;
    sum_cifre = cifra1 = cifra2 = 0;
    while( (p != nullptr || q != nullptr) || sum_cifre > 0 ){
        if(p != nullptr){
            cifra1 = p->x;
            p = p->urm;
        } else {
            cifra1 = 0;
        }
        if(q != nullptr){
            cifra2 = q->x;
            q = q->urm;
        } else {
            cifra2 = 0;
        }
        sum_cifre += cifra1 + cifra2;
        pushFront(vf_rezultat, sf_rezultat, size_rezultat, sum_cifre%10);
        sum_cifre /= 10;
    }
    return vf_rezultat;
}

void initializareLista(nod *&vf, nod *&sf, int &size , bool p_back){
    int n,x;
    fin >> n;
    for(int i = 0; i < n; i++) {
        fin >> x;
        if(p_back){
            pushBack(vf, sf, size, x);
        } else {
            pushFront(vf, sf, size, x);
        }

    }
   // writeList(vf,sf);
}

void problema2() {
    nod *vf,*sf;
    int size=0;
    initializareLista(vf,sf,size,true);
    int ci,cp,sum;
    ci=cp=sum = 0;

    nod* p = vf;
    while( p != nullptr ) {
        if(p->x % 2 == 0){
            cp++;
        } else {
            ci++;
            sum += p->x;
        }
        p = p->urm;
    }
    cout << "Numarul valorilor pare este: " << cp << '\n';
    cout << "Media aritmetica a valorilor impare este: " << (int)(sum/ci) << '\n';
}

void problema3() {
    nod *vf,*sf;
    int sum,ind;
    vf = sf = nullptr;
    int size = 0;
    initializareLista(vf,sf,size,true);
    writeList(vf,sf);
    sum = ind = 0;
    nod *p = vf;
    while( p->urm != nullptr ) {
        sum = p->x + p->urm->x;
        ind++;
        insertAt(vf, sf, size, sum/2, ind);
        p = p->urm->urm;
        ind++;
    }
    writeList(vf,sf);
}

void problema4() {
    cout<< "Unitatile sunt in partea stanga pentru cele 2 numere!\n";
    cout<< "Unitatile sunt in partea dreapta pentru rezultat!\n\n";
    nod *vf1,*sf1,*vf2,*sf2;
    vf1=sf1=vf2=sf2= nullptr;
    int size1,size2;
    size1 = size2 = 0;
    initializareLista(vf1, sf1, size1, false);
    initializareLista(vf2, sf2, size2, false);
    writeList(vf1,sf1);
    cout << "+" << '\n';
    writeList(vf2,sf2);
    nod *vf = suma_liste(vf1,vf2);
    cout << "=" << '\n';
    writeList(vf, NULL);
}

void problema5() {
    nod *vf1,*sf1,*vf2,*sf2;
    vf1=sf1=vf2=sf2= nullptr;
    int size1,size2;
    size1 = size2 = 0;
    initializareLista(vf1, sf1, size1, false);
    initializareLista(vf2, sf2, size2, false);
    writeList(vf1,sf1);
    cout << "x" << '\n';
    writeList(vf2,sf2);

    nod *cifr1,*cifr2,*reminderHead,*reminderFinal,*reminderHeadCopy;
    cifr1 = vf1;
    cifr2 = vf2;
    reminderHead = reminderFinal = nullptr;
    int reminderSize = 0;
    int inceput_cifr2 = 0;

    while ( cifr2 != nullptr ) {
        cout << "While-ul cifr2\n";
        int produs = 0;
        reminderHeadCopy = reminderHead;

        for(int i=0; i<inceput_cifr2; i++) {writeList(reminderHead,reminderFinal);
            reminderHeadCopy = reminderHeadCopy->urm;
        }

        while ( cifr1 != nullptr || produs > 0) {
            cout << "While-ul cifr1\n";
            int int_cifr1 = cifr1 == nullptr?1:cifr1->x;
            produs += int_cifr1 * cifr2->x;

            if(reminderHeadCopy == nullptr){
                pushBack(reminderHead,reminderFinal,reminderSize,produs%10);
                reminderHeadCopy = reminderFinal;
                writeList(reminderHead,reminderFinal);
            } else {
                reminderHeadCopy->x += produs%10;
            }

            produs /= 10;
            cifr1 = cifr1->urm;
            reminderHeadCopy = reminderHeadCopy -> urm;
        }

        cifr2 = cifr2->urm;
        inceput_cifr2 ++;
    }
    writeList(reminderHead,reminderFinal);
}


int main()
{
    problema5();
    return 0;
}
