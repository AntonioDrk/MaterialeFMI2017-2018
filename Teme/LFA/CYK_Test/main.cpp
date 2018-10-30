#include<iostream>
#include<cstring>
#include<algorithm>
#include<string>
#include<cassert>
#include<iomanip>
using namespace std;

#define MAX 100
#define for(i,a,b) for(i=a;i<b; i++)

string gramatica[MAX][MAX];  //Stochez gramatica primita
string dpr[MAX]; //stocheaza definitiile
int p,nr_prod;

inline string concatenare( string a, string b)   //concateneaza nodurile neterminale unice
{
    int i;
    string r=a;
    for(i,0,b.length())
        if(r.find(b[i]) > r.length())
            r+=b[i];
    return (r);
}

inline void separare(string a)    //separa partea dreapta a gramaticii introduse
{
    int i;
    p=0;
    while(a.length())
    {
        i=a.find("|");
        if(i>a.length())
        {
            dpr[p++] = a;
            a="";
        }
        else
        {
            dpr[p++] = a.substr(0,i);
            a=a.substr(i+1,a.length());
        }
    }
}

inline int stg_chomsky(string a)   //verifica daca partea stanga a gramaticii e in FNC
{
    if(a.length()==1 && a[0]>='A' && a[0]<='Z')
        return 1;
    return 0;
}

inline int dr_chomsky(string a)   //verifica daca partea dreapta a gramaticii este in FNC
{
    if (a.length() == 1 && a[0]>='a' && a[0] <='z')
        return 1;
    if (a.length()==2 && a[0]>='A' && a[0]<='Z' && a[1]>='A' && a[1]<='Z' )
        return 1;
    return 0;
}

inline string cauta_prod(string p) //returneaza un string cu neterminalele (concatenate) care pot produce p
{
    int j,k;
    string r="";
    for(j,0,nr_prod)
    {
        k=1;
        while(!gramatica[j][k].empty())
        {
            if(gramatica[j][k] == p)
            {
                r=concatenare(r,gramatica[j][0]);
            }
            k++;
        }
    }
    return r;
}

inline string generare_combinatii(string a, string b)  // BA * AB = {BA, BB, AA, BB}
{
    int i,j;
    string pri=a,re="";
    for(i,0,a.length())
        for(j,0,b.length())
        {
            pri="";
            pri=pri+a[i]+b[j];
            re=re+cauta_prod(pri);     //verifica daca productiile generate pot fi create sau nu
        }
    return re;
}

int main()
{
    int i,pt,j,l,k;
    string a,str,r,pr,start;
    cout<<"\nIntroduceti variabila de start: ";
    cin >> start;
    cout<<"\nIntroduceti numarul productiilor: ";
    cin >> nr_prod;
    cout<<"\nIntroduceti productiile: ";
    for(i,0,nr_prod)
    {
        cin >> a;
        pt=a.find("->");
        gramatica[i][0] = a.substr(0,pt);
        if (stg_chomsky(gramatica[i][0]) == 0)
        {
            cout<<"\nGramatica nu este in FNC";
            abort();
        }
        a = a.substr(pt+2, a.length());
        separare(a);
        for(j,0,p)
        {
            gramatica[i][j+1]=dpr[j];
            if (dr_chomsky(dpr[j]) == 0)
            {
                cout<<"\nGramatica nu este in FNC";
                abort();
            }
        }
    }
    string matrice_t[MAX][MAX],st;
    cout<<"\nIntroduceti cuvantul pentru a fi verificat: ";
    cin >> str;
    for(i,0,str.length())       //Asigneaza valori diagonalei principale
    {
        r="";
        st = "";
        st+=str[i];
        for(j,0,nr_prod)
        {
            k=1;
            while (!gramatica[j][k].empty())
            {
                if(gramatica[j][k] == st)
                {
                    r=concatenare(r,gramatica[j][0]);
                }
                k++;
            }
        }
        matrice_t[i][i]=r;
    }
    int ii,kk;
    for(k,1,str.length())       //Asigneaza valori triunghiului superior
    {
        for(j,k,str.length())
        {
            r="";
            for(l,j-k,j)
            {
                pr = generare_combinatii(matrice_t[j-k][l],matrice_t[l+1][j]);
                r = concatenare(r,pr);
            }
            matrice_t[j-k][j] = r;
        }
    }

    int f=0;
    for(i,0,start.length())
    {
        //verifica daca ultimul element al primului rand contine variabila de start
        if(matrice_t[0][str.length()-1].find(start[i]) <= matrice_t[0][str.length()-1].length())
        {
            cout<<"Cuvantul este generat de gramatica\n";
            for(i,0,str.length())   //afiseaza matricea
            {
                k=0;
                l=str.length()-i-1;
                for(j,l,str.length())
                {
                    cout<<setw(9)<<matrice_t[k++][j]<<" ";
                }
                cout<<endl;
            }
            return 0;
        }
        cout<<"Cuvantul nu este generat de gramatica\n";
    }

    return 0;
}