#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>

#define FILENAME_OUT "PretVeg.out"
using namespace std;

char * ToLower(char * loweringString){
    char * tmp = new char[strlen(loweringString)];
    for (int i = 0; i < strlen(loweringString); ++i) {
        tmp[i] = (char)tolower(loweringString[i]);
    }
    tmp[strlen(loweringString)] = '\0';
    return tmp;
}

class Produs
{
public:
    virtual float CalculPret() const = 0;
    virtual void Afisare() const = 0;
};

class Ingredient
{
    char* denumire;
    int cantitate;
    float pret_unitar;

public:
    Ingredient()
    {
        denumire = new char[strlen("nedefinit")];
        strcpy(denumire, "nedefinit");
        cantitate = 0;
        pret_unitar = 0;
    };
    ~Ingredient()
    {
        //delete denumire;
    };
    Ingredient(const char* _denumire, int _cantitate, float _pret_unitar)
    {
        denumire = new char[strlen(_denumire)];
        strcpy(denumire, _denumire);
        cantitate = _cantitate;
        pret_unitar = _pret_unitar;
    }

    Ingredient (const Ingredient& ingredient)
    {
        denumire = new char[strlen(ingredient.denumire)];
        strcpy(denumire, ingredient.denumire);
        cantitate =  ingredient.cantitate;
        pret_unitar = ingredient.pret_unitar;
    }

    Ingredient& operator = (const Ingredient& ingredient);
    friend ostream& operator << (ostream& out, Ingredient& ingredient);
    friend istream& operator >> (istream& in, Ingredient& ingredient);

    float Pret();

    char *getDenumire() const;

    int getCantitate() const;

    float getPret_unitar() const;
};

Ingredient &Ingredient::operator=(const Ingredient &ingredient)
{
    denumire = new char[strlen(ingredient.denumire)];
    strcpy(denumire, ingredient.denumire);
    cantitate =  ingredient.cantitate;
    pret_unitar = ingredient.pret_unitar;

    return *this;
}

ostream &operator << (ostream &out, Ingredient &ingredient)
{
    out << "Denumire ingredient: " << ingredient.denumire << '\n';
    out << "\tCantitate ingredient: " << ingredient.cantitate<< '\n';
    out << "\tPret unitar ingredient: " << ingredient.pret_unitar << '\n';
    return out;
}

istream &operator >> (istream &in, Ingredient &ingredient)
{
    char _denumire[500];
    cout << "\nIntroduceti denumirea ingredientului: ";
    in.getline(_denumire, 500);
    ingredient.denumire = new char[strlen(_denumire)];
    strcpy(ingredient.denumire, _denumire);
    cout << "\nIntroduceti cantitatea: ";
    in >> ingredient.cantitate;
    cout << "\nIntroduceti pretul unitar: ";
    in >> ingredient.pret_unitar;

    return in;
}

float Ingredient::Pret()
{
    return (pret_unitar*cantitate);
}

char *Ingredient::getDenumire() const
{
    return denumire;
}

int Ingredient::getCantitate() const
{
    return cantitate;
}

float Ingredient::getPret_unitar() const
{
    return pret_unitar;
}

class Pizza: public Produs
{
    Ingredient* ingrediente;
    int nrIngrediente;
    char* denPizza;
    float pret_total, manopera;
public:
    Pizza()
    {
        ingrediente = nullptr;
        nrIngrediente = 0;
        denPizza = new char[strlen("nedefinit")];
        strcpy(denPizza, "nedefinit");
        pret_total = 0;
        manopera = 0;
    }

    ~Pizza()
    {};

    Pizza(Ingredient* _ingrediente, int _nrIngrediente, const char* _denPizza, float _manopera)
    {
        nrIngrediente = _nrIngrediente;
        if (nrIngrediente > 0)
        {
            ingrediente = new Ingredient[nrIngrediente];
            for (int i =0; i < nrIngrediente; i++)
                ingrediente[i] = _ingrediente[i];
        }
        denPizza = new char[strlen(_denPizza)];
        strcpy(denPizza, _denPizza);
        pret_total = 0;
        manopera = _manopera;
    }

    Pizza (Pizza& pizza)
    {
        nrIngrediente = pizza.nrIngrediente;
        if (nrIngrediente > 0)
        {
            ingrediente = new Ingredient[nrIngrediente];
            for (int i =0; i < nrIngrediente; i++)
                ingrediente[i] = pizza.ingrediente[i];
        }
        denPizza = new char[strlen(pizza.denPizza)];
        strcpy(denPizza, pizza.denPizza);
        pret_total = pizza.pret_total;
        manopera = pizza.manopera;
    }

    Pizza& operator = (const Pizza& pizza)
    {
        nrIngrediente = pizza.nrIngrediente;
        if (nrIngrediente > 0)
        {
            ingrediente = new Ingredient[nrIngrediente];
            for (int i =0; i < nrIngrediente; i++)
                ingrediente[i] = pizza.ingrediente[i];
        }
        denPizza = new char[strlen(pizza.denPizza)];
        strcpy(denPizza, pizza.denPizza);
        pret_total = pizza.pret_total;
        manopera = pizza.manopera;

        return *this;
    }

    friend ostream& operator << (ostream& out, const Pizza& pizza)
    {
        out << "\nDenumire Pizza: " << pizza.denPizza;
        out << "\nNumar Ingrediente: " << pizza.nrIngrediente;
        if (pizza.nrIngrediente > 0)
        {
            out << "\nIngrediente: ";
            for (int i = 0; i < pizza.nrIngrediente; i++)
                out << "\n\t" << pizza.ingrediente[i];
        }
        return out;
    }

    friend istream& operator >> (istream& in, Pizza& pizza)
    {
        char _denPizza[500],str[1];

        cout << "\nIntroduceti numele pizzei: ";
        in.getline(_denPizza,500);
        if(_denPizza[0] == '\0'){
            cout <<"\nO eroare la citirea denumirii pizzei, introduceti inca odata numele pizzei: ";
            in.getline(_denPizza,500);
        }
        pizza.denPizza = new char[ strlen(_denPizza) ];
        strcpy(pizza.denPizza, _denPizza);
        cout << "\nIntroduceti nr ingrediente: ";
        in >> pizza.nrIngrediente;

        if(pizza.nrIngrediente > 0)
        {
            pizza.ingrediente = new Ingredient[pizza.nrIngrediente];
            cout << "\nIntroduceti ingredientele ";
            for (int i = 0; i < pizza.nrIngrediente; ++i)
            {
                cout << '\n';
                in.getline(str, 1);
                in >> pizza.ingrediente[i];
            }
        }
        cout << "\nIntroduceti costul manoperei: ";
        in >> pizza.manopera;
        pizza.pret_total = 0;
        return in;
    }

    void setPret_total(float pret_total)
    {
        Pizza::pret_total = pret_total;
    }


    float CalculPret() const override
    {
        float s = 0;
        for (int i = 0; i < nrIngrediente; i++)
        {
            s = s + ingrediente[i].Pret();
        }
        s = s + manopera;

        return s;
    }

    void Afisare() const override
    {
        cout << *this;
        cout << "\nPretul este: "<< this->CalculPret();
    }

    Ingredient *getIngrediente() const;

    int getNrIngrediente() const;

    char *getDenPizza() const;
};

Ingredient *Pizza::getIngrediente() const
{
    return ingrediente;
}

int Pizza::getNrIngrediente() const
{
    return nrIngrediente;
}

char *Pizza::getDenPizza() const
{
    return denPizza;
}

class OnLinePizza: public Pizza
{
    int distanta;

public:
    OnLinePizza(): Pizza()
    {
        distanta = 0;
    };

    ~OnLinePizza(){};
    OnLinePizza(int _distanta, Ingredient* _ingrediente, int _nrIngrediente, const char* _denPizza, float _manopera): Pizza( _ingrediente, _nrIngrediente, _denPizza, _manopera)
    {
        distanta = _distanta;
    };

    OnLinePizza (OnLinePizza& online): Pizza(static_cast<Pizza&>(online))
    {
        distanta = online.distanta;
    }

    friend ostream& operator << (ostream& out, OnLinePizza& oPizza)
    {
        out << static_cast<Pizza&>(oPizza);
        try
        {
            out << "\nDistanta: " << oPizza.distanta;
            if(oPizza.distanta < 0)
                throw 1;
        }catch (int x){
            if(x == 1)
                cout << "\nNu exista distante negative intre doua puncte pe un plan";
        }
        return out;
    }

    void setDistanta(int distanta)
    {
        OnLinePizza::distanta = distanta;
    }

    float CalculPret() const override
    {
        float pret_dist;
        int dist;
        dist = distanta/10;
        float proc;
        proc = Pizza::CalculPret() * 0.05;
        float pret_pizz = Pizza::CalculPret();
        pret_dist = proc * dist + pret_pizz;
        return pret_dist;
    }

    int getDistanta() const;
};

int OnLinePizza::getDistanta() const
{
    return distanta;
}

template <class T>
class Meniu
{
    Pizza** pizze;
    static int index;

    vector<char*> numeCarnuri;

public:
    Meniu()
    {
        /// Adaugam pe aici mai multe carnuri, ca sa verificam daca pizza nu le contine => e vegetariana
        /// Note: E case sensitive, toate carnurile sa fie scrise cu litere mici ale alfabetului latin
        numeCarnuri.push_back("carne");
        numeCarnuri.push_back("carnati");
        numeCarnuri.push_back("salam");
        numeCarnuri.push_back("pui");
        pizze = nullptr;
    }
    ~Meniu(){};

    void operator += (Pizza *pizza)
    {
        Pizza** temp;
        temp = new Pizza*[index];
        for (int i=0; i < index; i++)
            temp[i]=pizze[i];
        delete(pizze);
        index++;
        pizze = new Pizza*[index];
        for (int i = 0; i< index; i++)
            if (i < index - 1)
                pizze[i] = temp[i];
            else
                pizze[i] =  pizza;
    }

    float sumaTotala(){
        float s = 0;
        for (int i = 0; i < index; ++i) {
            s += pizze[i]->CalculPret();
        }
        return s;
    }

    void vegetariana()
    {
        float pret_total_veg = 0;
        bool ok;
        int index_veg = 0;
        for (int i=0; i< index; i++)
        {
            ok = true;
            for (int j=0; j < pizze[i]->getNrIngrediente(); j++)
            {
                // Verificare daca pizza noastra are carne pe ea
                for (int k = 0; k < numeCarnuri.size(); ++k) {
                    if(strcmp(ToLower(pizze[i]->getIngrediente()[j].getDenumire()),numeCarnuri[k]) == 0){
                        ok = false;
                    }
                }
            }
            if (ok)
            {
                pret_total_veg = pret_total_veg + pizze[i]->CalculPret();
                index_veg++;
            }
        }
        ofstream contabil(FILENAME_OUT);
        contabil << "Pretul pizza vegetariana per comanda este: " << pret_total_veg;
        contabil << "\nS-au vandut " << index_veg << " pizza vegetariene";
        contabil.close();
    }

    void afisareMeniu(){
        cout << "--------------------------COSUL DUMNEAVOASTRA--------------------------\n\n";
        for (int i = 0; i < index; ++i) {
            cout << *pizze[i];
        }
        cout << "-----------------------------------------------------------------------\n\n";
    }

    void verifica_exceptie();
};

template<>
void Meniu<int>::verifica_exceptie()
{
    for (int i = 0; i < index; i++)
        try
        {
            if (pizze[i]->getNrIngrediente() < 0)
                throw 1;
            for (int j=0; j < pizze[i]->getNrIngrediente(); j++)
            {
                if (pizze[i]->getIngrediente()[j].getCantitate() < 0)
                    throw 2;
                if (pizze[i]->getIngrediente()[j].getPret_unitar() < 0)
                    throw 3;
            }

        }catch(int valoare)
        {
            switch(valoare)
            {
                case 1:
                    cout << "\nNu puteti introduce numar negativ de ingrediente";
                    break;
                case 2:
                    cout << "\nNu puteti introduce o cantitate negativa de ingrediente";
                    break;
                case 3:
                    cout << "\nNu puteti introduce un pret negativ";
                    break;
                default:
                    cout << "\nEroare necunoscuta";
            }
            exit(-1);
        }
};

template <class T>
int Meniu <T> ::index = 0;


void CitireAfisareUnu(){
    Pizza **Pizze;
    double dnrPizze;
    int inrPizze;

    cout << "Numarul de pizze dorite: ";
    cin >> dnrPizze;

    while(cin.fail()){
        cin.clear();
        cin.ignore();
        cout << "Numar INCORECT de pizze, folositi doar numere naturale pozitive\n\n";
        cout << "Numarul de pizze dorite: ";
        cin >> dnrPizze;
        cout << '\n';
    }

    try{
        inrPizze = (int)dnrPizze;
    }catch(exception &e){
        cout << "Erorr: " << e.what() << '\n';
        cout << "Numarul dat este gresit, folositi DOAR numere NATURALE POZITIVE\n";
        exit(-1);
    }

    try {
        Pizze = new Pizza*[inrPizze];
    }catch (bad_alloc &e){
        cout << "Numarul de pizze introdus este gresit, eroare " << e.what();
        exit(-1);
    }

    for (int i = 0; i < inrPizze; ++i) {
        int op;
        cout << "Ce tip de pizza doriti:\n"
                "[1]Pizza normala\n"
                "[2]Pizza online\n";
        cin >> op;
        switch (op){
            case 1:
                Pizze[i] = new Pizza();
                break;
            case 2:
                Pizze[i] = new OnLinePizza();
                break;
            default:
                cout << "Optiune gresita!";
                exit(-1);
                break;
        }
        cin >> *Pizze[i];
    }
    for (int i = 0; i < inrPizze; ++i) {
        cout << *Pizze[i];
    }
}

void GestiuneComanda(Meniu<int> &meniu, char* comandaText, bool &exitCondSecond){
    //TODO 2 De gestionat cumpararea pizze-lor
    int iioption = 0;
    double ddoption = 0;
    cout << comandaText << "Optiunea aleasa: ";
    cin >> ddoption;
    try{
        iioption = (int)ddoption;
    }catch(exception &e){
        cout << "Eroare: " << e.what() << '\n';
        cout << "Optiunea aleasa este gresita, folositi doar numerele ce apar pe ecran\n";
        exit(-1);
    }
    int nrPizze = 0;
    int tipComanda = 1;
    Pizza **Pizze;

    switch (iioption){
        //TODO 2.1 Adauga pizze la comanda
        case 1:
            cout << "[1] Comanda directa\n"
                    "[2] Comanda online\n\n";
            cin >> tipComanda;
            cout << '\n';
            cout << "Numarul de pizze de comandat: ";
            cin >> nrPizze;

            try {
                Pizze = new Pizza*[nrPizze];
            }catch (bad_alloc &e){
                cout << "Numarul de pizze introdus este gresit, eroare " << e.what();
                exit(-1);
            }


            for (int i = 0; i < nrPizze; ++i) {
                if(tipComanda == 1){
                    Pizze[i] = new Pizza();
                }else{
                    Pizze[i] = new OnLinePizza();
                }
                cin >> *Pizze[i];
                meniu += Pizze[i];
            }
            meniu.verifica_exceptie();
            break;
            //TODO 2.2 Verifica suma de plata
        case 2:
            cout << "Suma de plata este : " << meniu.sumaTotala() << " RON\n";
            meniu.afisareMeniu();
            break;
            //TODO 2.3 Checkout(Finalizare a comenzii si intocmirea contabila a pizzleor vegetariene vandute)
        case 3:
            cout << "Plata se va intocmi in scurt timp, costul total este de " << meniu.sumaTotala() << "RON\n";
            cout << "Se creeaza fisierul de contabilitate pentru pizzele vegetariene\n";
            meniu.vegetariana();
            cout << "Fisierul "<< FILENAME_OUT << " a fost creat\n";

            exitCondSecond = true;
            break;
            //TODO 2.4 Intoarcere la meniul principal
        case 4:
            exitCondSecond = true;
            break;
    }
}

int main()
{

    char menuText[] = { "------------------------------MENIU----------------------------------\n"
                        "                            PIZZERIA X                               \n"
                        "[1]Citire/stocare/afisare a n obiecte\n"
                        "[2]Gestiune comenzi pizza\n"
                        "[3]Iesire\n"
                        "---------------------------------------------------------------------\n\n"};

    char comandaText[] = { "-------------------------------GESTIONARE COMANDA----------------------------------------\n"
                           "[1]Adauga pizze la comanda\n"
                           "[2]Verifica suma de plata si vizualizare cos de cumparaturi\n"
                           "[3]Checkout(Finalizare a comenzii si intocmirea contabila a pizzleor vegetariene vandute)\n"
                           "[4]Intoarcere la meniul principal\n"
                           "---------------------------------------------------------------------------------------\n\n"};

    bool exitCond = false;
    bool exitCondSecond = false;

    int ioption = 0;

    double doption = 0;

    Meniu<int> meniu;

    while(!exitCond) {

        cout << menuText << "Optiunea aleasa: ";

        cin >> doption;
        cout <<'\n' << '\n';

       try{
            ioption = (int)doption;
        }catch(exception &e){
            cout << "Eroare: " << e.what() << '\n';
            cout << "Optiunea aleasa este gresita, folositi doar numerele ce apar pe ecran\n";
            exit(-1);
        }

        switch (ioption){
            case 1:
                CitireAfisareUnu();
                break;
            case 2:
                while(!exitCondSecond){
                    GestiuneComanda(meniu,comandaText,exitCondSecond);
                }
                exitCondSecond = false;
                break;
            case 3:
                exitCond = true;
                break;
            default:
                cout << "Optiune aleasa gresita\n";
                break;
        }
    }

    return 0;
}
