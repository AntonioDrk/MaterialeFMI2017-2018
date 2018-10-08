#include <iostream>
//clasa lui R patrat
using namespace std;

class pereche {

int a;
float b;
public :
    pereche (int , float );
    pereche (pereche &);
    pereche &operator = (pereche &);
    friend istream & operator >> (istream & , pereche &);
    friend ostream & operator << ( ostream & , pereche & );
    pereche & operator + ( pereche &);
    friend pereche & operator * ( pereche & , pereche &);
    ~pereche ();

};
pereche :: pereche ( int x=0 , float y =0 ) { a = x ; b  = y;};
pereche :: pereche  ( pereche &x )
{
     a = x.a ;
     b = x.b;
}
pereche & pereche :: operator = ( pereche  &d )
{
    if  ( this != &d)
    {
         a = d.a;
         b = d.b;
    }
    return *this ;


}
istream & operator >> ( istream  &x , pereche &p)
{
    x>>p.a>>p.b;
    return x;
}
ostream & operator << ( ostream &out  , pereche &p)
{
    out<< p.a << " " <<p.b;
    return out;
}
pereche & pereche :: operator + ( pereche &p)
{
    pereche suma;
    suma.a = a+ p.a;
    suma.b = b + p.b;
    return suma ;
}
pereche  & operator * ( pereche & p , pereche & q )
{
    pereche rez;
    rez.a=p.a*q.a;
    rez.b = p.b * q.b ;
    return rez;
}
pereche :: ~pereche () {}

int main()
{
    pereche a,s,b;

    cin>>a;
    cin>>b;
s=a*b;
    cout<<s;
}
