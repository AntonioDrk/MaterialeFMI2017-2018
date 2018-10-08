#include <iostream>

using namespace std;

/// CERINTA 5


class Nod{
protected:
    int info;
    Nod *next;
public:
    Nod(){
        info = 0;
        next = nullptr;
    }
    Nod(Nod &nod){
        if(&nod != nullptr) {
            info = nod.getInfo();
            next = nod.getNext();
        }
    }

    Nod(int _info){
        info = _info;
        next = nullptr;
    }
    Nod(int _info, Nod *_next){
        info = _info;
        next = _next;
    }
    int getInfo(){
        return info;
    }

    int setInfo(int _info){
        info = _info;
    }

    Nod* getNext(){
        return next;
    }

    void setNext(Nod *nod){
        next = nod;
    }

    Nod& operator =(Nod& nodDreapta){
        info = nodDreapta.getInfo();
        next = nodDreapta.getNext();
    }

    friend ostream& operator <<(ostream& o, Nod& nod){
        o << nod.getInfo();
        return o;
    }
    friend istream& operator >>(istream& in, Nod& nod){
        int data;
        in >> data;
        nod.info = data;
        return in;
    }
};

class Nod_dublu:public Nod{
    Nod *ante;
public:
    Nod_dublu():Nod(){
        ante = nullptr;
    }

    Nod_dublu(Nod &nod):Nod(nod){
        ante = nullptr;
    }

    Nod_dublu(Nod_dublu &nod_dublu):Nod(nod_dublu){
        ante = nod_dublu.getAnte();
    }

    Nod_dublu(int _info):Nod(_info){
        ante = nullptr;
    }
    Nod_dublu(int _info, Nod *_next, Nod*_ante):Nod(_info,_next){
        ante = _ante;
    }

    // GET SET ANTE
    Nod* getAnte(){
        return ante;
    }
    void setAnte(Nod *nod) {
        ante = nod;
    }

    Nod_dublu& operator =(Nod_dublu& nodDreapta){
        info = nodDreapta.getInfo();
        next = nodDreapta.getNext();
        ante = nodDreapta.getAnte();
    }

    friend ostream& operator <<(ostream& o, Nod_dublu& nod){
        o << nod.getInfo();
        return o;
    }
    friend istream& operator >>(istream& in, Nod_dublu& nod){
        int data;
        in >> data;
        nod.setInfo(data);
        return in;
    }
};

class Lista{
protected:
    Nod_dublu *start;
public:
    Lista(){
        start = nullptr;
    }

    Lista(Lista &listaDeCopiat){
        if(listaDeCopiat.getStart() != nullptr) {
            start = new Nod_dublu(*listaDeCopiat.getStart());
            Nod_dublu *indiceCopie = (Nod_dublu *) listaDeCopiat.getStart()->getNext();
            Nod_dublu *indiceCurent = start;
            while (indiceCopie != nullptr) {
                indiceCurent->setNext( new Nod_dublu(indiceCopie->getInfo()) );
                indiceCurent = (Nod_dublu *) indiceCurent->getNext();
                indiceCopie = (Nod_dublu *) indiceCopie->getNext();
            }
        }
    }

    // Pentru a avea un constructor parametrizat am folosit o initializare a n elemente
    Lista(int dimens){
        start = new Nod_dublu();
        Nod_dublu *pIndex = start;
        while(dimens > 1){
            pIndex->setNext( new Nod_dublu );
            pIndex = (Nod_dublu*)pIndex->getNext();
            dimens--;
        }
    }

    ~Lista(){
        while(start != nullptr){
            pop_front();
        }
    }

    virtual Nod_dublu * getStart(){
        return start;
    }

    void push_back(int info){

        if(start == nullptr){
            start = new Nod_dublu(info);

        } else {

            Nod_dublu *indexP = start;
            while (indexP->getNext() != nullptr) {
                indexP = (Nod_dublu *) indexP->getNext();
            }

            indexP->setNext(new Nod_dublu(info));
        }
    }

    int pop_front(){
        if(start == nullptr){
            cout<<"Ati incercat sa faceti pop_front la ceva inexistent";
            return -999999999;
        }
        Nod_dublu *tmp = start;
        start = (Nod_dublu*)start->getNext();
        delete(tmp);
    }

    Lista& operator =(Lista& listDreapta){
        while(start != nullptr){
            pop_front();
        }
        start = new Nod_dublu( *listDreapta.getStart() );
        Nod_dublu *indiceDreapta = (Nod_dublu*) listDreapta.getStart()->getNext();
        Nod_dublu *indiceStanga = start;
        while( indiceDreapta != nullptr ){                              // Cat timp in dreapta avem ce sa parcurgem
            indiceStanga->setNext( new Nod_dublu( *indiceDreapta ) );
            indiceStanga = (Nod_dublu*) indiceStanga->getNext();
            indiceDreapta = (Nod_dublu*) indiceDreapta->getNext();
        }
        return *this;
    }

    friend istream& operator >>(istream& in, Lista& list){
        int dimens;
        cout << "Dimensiunea listei: ";
        in >> dimens;
        cout << "\nNumerele pe care doriti sa le introduceti:";
        int x;
        for(int i = 0; i < dimens; i++){
            in >> x;
            list.push_back(x);
        }
        return in;
    }

    friend ostream& operator <<(ostream& o, Lista& list){
        Nod_dublu *p;
        p = list.getStart();
        o << "\nLista: ";
        while(p != nullptr){
            o << p->getInfo() << " ";
            p = (Nod_dublu*)(p->getNext());
        }
        return o;
    }

};

class Lista_Circulara:public Lista{
public:
    Lista_Circulara():Lista(){}

    Lista_Circulara(int dimens):Lista(dimens){}

    Lista_Circulara(Lista_Circulara& lcCopiere){
        if(lcCopiere.getStart() != nullptr) {
            start = new Nod_dublu(*lcCopiere.getStart());
            Nod_dublu *indiceCopie = (Nod_dublu *) lcCopiere.getStart()->getNext();
            Nod_dublu *indiceCurent = start;
            while (indiceCopie != nullptr) {
                indiceCurent->setNext(new Nod_dublu(indiceCopie->getInfo()));
                ( (Nod_dublu*)indiceCurent->getNext() )->setAnte( indiceCurent );   // Setez anteriorul urmatorului ca fiind indiceCurent
                indiceCurent = (Nod_dublu *) indiceCurent->getNext();
                indiceCopie = (Nod_dublu *) indiceCopie->getNext();
            }
        }
    }

    ~Lista_Circulara(){
        while(start != nullptr){
            popAt(1);
        }
    }

    void push(int info){
        if(start == nullptr){
            start = new Nod_dublu(info);
            start->setNext(start);
        } else {
            Nod_dublu *index;
            index = start;
            while(index->getNext() != start){
                index = (Nod_dublu*)index->getNext();
            }
            Nod_dublu *tmp = new Nod_dublu(info);
            index->setNext(tmp);
            tmp->setAnte(index);
            tmp->setNext(start);
            start->setAnte(tmp);
        }
    }

    // Remove elem at position index from start
    // NUMEROTAREA INCEPE DE LA 1
    int popAt(int index){
        if(start == nullptr) return 0;

        Nod_dublu *indexCurent = start;
        int contor = 1;
        while(contor < index){
            indexCurent = (Nod_dublu*)indexCurent->getNext();
            contor++;
        }
        //                  curr -> next()    -> prev()  =     curr -> prev()
        ( (Nod_dublu*)indexCurent->getNext() )->setAnte( indexCurent->getAnte() );
        //                  curr -> prev()    -> next() =      curr -> next()
        ( (Nod_dublu*)indexCurent->getAnte() )->setNext( indexCurent->getNext() );
        if (indexCurent == start){
            start = (Nod_dublu*)indexCurent->getNext();
            if(indexCurent == start){
                start = nullptr;
            }
        }
        int x = indexCurent->getInfo();
        delete(indexCurent);
        return x;
    }

    Nod_dublu* getStart() override {
        return start;
    }

    friend ostream& operator <<(ostream& o, Lista_Circulara& listC){
        Nod_dublu *p;
        p = listC.getStart();
        o << "\nLista_Circulara: ";
        while(p->getNext() != listC.getStart()){
            o << p->getInfo() << " ";
            p = (Nod_dublu*)(p->getNext());
        }
        o << p->getInfo() << " ";
        return o;
    }

    friend istream& operator >>(istream& in, Lista_Circulara& listC){
        int dimens;
        cout << "Dimensiunea listei circulare: ";
        in >> dimens;
        cout << "\nNumerele pe care doriti sa le introduceti:";
        int x;
        for(int i = 0; i < dimens; i++){
            in >> x;
            listC.push(x);
        }
        return in;
    }
    static bool isEmpty(Lista_Circulara &lc){
        return lc.getStart() == nullptr;
    }
};

void PbJosephus(){
    system("CLS");
    // n = cate num1ere sunt
    // m = din cat in cat se elimina un numar
    // k = al catelea numar eliminat dorim sa-l vedem
    int n,m,k;
    int kElement = -1;
    cout<<"Pentru problema lui Josephus, vom folosi o lista circulara numerotata consecutiv, incepand de la 1 pana la n";
    cout<<"\nIntroduceti cate numere sa se afle pe cerc, n = "; cin >> n;
    cout << "\nIntroduceti din cat in cat se sare, m = "; cin >> m;
    cout <<"\nIntroduceti al catelea numar eliminat doriti sa-l vizualizati, k = "; cin >> k;
    if(k > n){
        cout<<"\n Este nevoie de un numar k mai mic decat n !";
        PbJosephus();
        return;
    }
    Lista_Circulara lc;
    for(int i = 1; i <= n; i++){
        lc.push(i);
    }

    int contor = 0;
    while(contor < k){
        kElement = lc.popAt(m+contor); // Nu incep urmatoarea numerotare din pop de la ultima pozitie, de aceea ii dau m * contor
        contor++;
    }
    cout << "\nAl k-lea element est: " << kElement;
}

void DemonstratieVector(Lista *lcVec[]){
    system("CLS");
    int n;
    cout<< "Numarul de obiecte dorite: "; cin >> n;
    for(int i = 0; i < n; ++i){
        int op;
        cout << "\t1.Lista normala\n\t2.Lista circulara\n\tAlegere = ";cin >> op;
        if(op == 2){
            Lista_Circulara *lc = new Lista_Circulara;
            lcVec[i] = lc;
        }else {
            lcVec[i] = new Lista;
        }
        cin>>*lcVec[i];
    }
    cout << "\nAfisarea listelor:\n";
    for (int i = 0; i < n; ++i) {
        cout << *lcVec[i];
    }
}

void DemonstratieDownCast( ){
    system("CLS");
    cout << "Avem clasa de baza Nod si clasa derivata Nod_dublu, o sa facem downcast din clasa de baza in clasa derivata";
    cout << "Declaram doi pointeri de tip nod, 3 si 4, 3 legat ( -> ) de 4\n";
    Nod *p,*p2;
    p = new Nod(3);
    p2 = new Nod(4);
    p->setNext(p2);
    cout << "Luam un nod dublu (pd), gol\n";
    cout << "Il copiez pe 3 in nodul dublu prin downcasting\n";
    Nod_dublu *pd1;
    pd1 = (Nod_dublu*)p;
    cout<< "Dupa downcasting, 3 isi mentine legatura, apelez din nodul dublu getNext().getInfo() : " << pd1->getNext()->getInfo() << '\n';
    cout << "Dar el, fiind downcasting, o sa aiba o valuare reziduala pe post de ante, nu o sa aibe null, precum ar trebui daca era din constructor, pd.getAnte() == nullptr ? " << ( ( pd1->getAnte() )? " yes ": " no ") << '\n';

}

void DemonstratieUpCast( ){
    system("CLS");
    cout << "Avem clasa de baza Nod si clasa derivata Nod_dublu, o sa facem upcast din clasa derivata in clasa derivata";
    cout << "Declaram doi pointeri de tip nod_dublu, 13 si 37, 13 legat ( -> ) de 37, si 13 ( <- ) 37\n";
    Nod_dublu *p,*p2;
    p = new Nod_dublu(13);
    p2 = new Nod_dublu(37);
    p->setNext(p2);
    p2->setAnte(p);
    cout << "Luam un nod (pd), gol\n";
    cout << "Il copiez pe 37 in nod prin upcasting\n";
    Nod *pd;
    pd = p;
    cout<< "Dupa upcasting, 37 isi mentine legatura, apelez din nod getNext().getInfo() : " << pd->getNext()->getInfo() << '\n';
    cout << "Dar el, fiind upcast-uit, n-o sa aiba acces la .getAnte()" <<'\n';

}

int main() {
    bool exit = false;
    Lista *lcVec[1000];
    while(!exit) {
        cout << "\n\n\n\n\n\n\n";
        int op;
        cout << "1. Problema lui Josephus " <<
             "\n2. Vector de obiecte (liste circulare)" <<
             "\n3. Exemplu downcasting" <<
             "\n4. Exemplu upcasting" <<
             "\n5. Iesiti din program\n";
        cout << "Optiunea dumneavoastra: ";
        cin >> op;
        switch (op) {
            case 1:
                PbJosephus();
                break;

            case 2:
                DemonstratieVector(lcVec);
                break;

            case 3:
                DemonstratieDownCast();
                break;

            case 4:
                DemonstratieUpCast();
                break;

            case 5:
                exit = true;
                break;

            default:
                cout << "\nOptiune nerecunoscuta, incercati inca odata";
                break;
        }
    }
    return 0;
}