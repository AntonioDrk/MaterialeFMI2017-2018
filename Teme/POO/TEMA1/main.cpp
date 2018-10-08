#include <iostream>
#include <stdlib.h>
using namespace std;

class Nod{
public:
    char info;
    Nod* next;
    Nod();

    Nod(char);
    ~Nod();
};

class Stiva_de_caractere{
    Nod *head;
public:
    Stiva_de_caractere();   ///initializeaza varful stivei cu nullptr;
    ~Stiva_de_caractere();  ///dezaloca toate elementele stivei;
    void push(char);
    char pop();
    char top();
    bool isempty();
    friend ostream& operator<<(ostream&, Stiva_de_caractere&);
    friend istream& operator>>(istream&, Stiva_de_caractere&);
    Stiva_de_caractere& operator-(Stiva_de_caractere&);
};

Stiva_de_caractere::Stiva_de_caractere(){
    head = nullptr;
}

Stiva_de_caractere::~Stiva_de_caractere() {
    Nod *p = head;
    while(p != nullptr){
        head = head->next;
        delete(p);
        p = head;
    }
}

void Stiva_de_caractere::push(char data){
    auto *tmp = new Nod(data);
    if (head != nullptr){
        tmp->next = head;
    }
    head = tmp;
}

char Stiva_de_caractere::pop(){
    if(head != nullptr){
        Nod *tmp = head;
        head = tmp->next == nullptr ? nullptr : tmp->next;
        char t = tmp->info;
        delete tmp;
        return t;
    }
    cout << "EROARE LA POP" << '\n';
    return '-';
}

char Stiva_de_caractere::top(){
    return head != nullptr ? head->info : '-';
}

bool Stiva_de_caractere::isempty(){
    return head == nullptr;
}

Stiva_de_caractere& Stiva_de_caractere::operator-(Stiva_de_caractere& rightSide){

    Stiva_de_caractere *result;

    result = new Stiva_de_caractere();

    /// Cat timp ambele stive au ceva in ele
    while(isempty() == false && rightSide.isempty() == false){

        /// Variabila de comparare (compareResult)
        char cmpRes;

        /// Compar primul caracter din fiecare stiva
        cmpRes = top() > rightSide.top() ? top() : rightSide.top();

        /// Elimin primul caracter din ambele stive
        pop();rightSide.pop();

        /// Dau push la rezultatul compararii
        result->push(cmpRes);
    }

    return *result;

}

ostream& operator<<(ostream &out, Stiva_de_caractere &stiva){
    out << "STIVA : ";
    while(stiva.isempty() == false ){
        out << stiva.pop() << "  ";
    }
    out << '\n';
    return out;
}

istream& operator>>(istream &in, Stiva_de_caractere &stiva){
    cout << "INTRODUCETI DIMENSIUNEA STIVEI: ";
    int n;
    cin >> n;
    cout << "\nINTRODUCETI CARACTERELE:  ";
    char t;
    for(int i = 0; i < n; i++){
        in >> t;
        stiva.push(t);
    }
    cout << '\n';
    return in;
}

Nod::Nod(){
    info = '-';
    next = nullptr;
}

Nod::Nod(char _info){
    info = _info;
    next = nullptr;
}

Nod::~Nod(){
    info = '-';
}


int main() {

    Stiva_de_caractere v[100];
    int nrStive = 0;

    while(1){
        int option;
        cout << "1. Initializati un vector de stive de caractere\n"<<
                "2. Scadeti doua stive din vector si vedeti rezultatul\n" <<
                "3. QUIT\n" <<
                "Optiunea dorita: ";
        cin >> option;
        system("cls");  /// Clear console
        if(option < 1 || option > 3){
            cout << "Nu exista aceasta optiune, incercati inca odata";
            continue;
        }
        switch(option){
        case 1:
            cout << "Cate stive doriti?\nNumar de stive: ";
            cin >> nrStive;
            for (int i = 0; i < nrStive; i++){
                cin >> v[i];
            }
            break;
        case 2:
            /// Daca nu s-au citit macar 2 stive
            if(nrStive <= 1){
                cout << "Mai am nevoie de stive\n";
            } else {
                cout << "Alegeti doi indici din vector ca sa-i scadeti si sa vedeti rezultatul!\n";
                int ind1,ind2;
                cin >> ind1 >> ind2;
                /// Daca indicii sunt incadrati corect
                if(ind1 < 0 || ind1 >= nrStive || ind2 < 0 || ind2 >= nrStive){
                    cout << "Ati introdus indicii gresit, zic sa luati totul de la capat :)\n";
                }else {
                    cout << "Totul pare ok, rezultatul dintre scaderea stivei nr " << ind1 << " si stiva nr " << ind2 << " este:\n";
                    cout << v[ind1] - v[ind2] << '\n';
                }
            }
            break;
        case 3:
            /// Iesim
            cout << "O zi frumoasa ☺\n";
            return 0;
            break;
        }
    }

    return 0;
}
