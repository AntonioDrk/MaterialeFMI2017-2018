#include <iostream>
using namespace std;


class X{

    int i;
public:
    X(int ii){i=ii;}
;
    int f1()/*se introduce aici const ca sa mearga programul */{ return i;}; ///eroare eoarece f2 care e functie care protejeaza obiectul incearca sa apeleze o functie care nu protejeaza
    X f2()const{
        int i=f1();
        return X(34-i);

    }


};


const X f3(){
    return X(16);

}

int f4(const X& x){
    return x.f1();
}



int main() {
 X ob(11);
 cout<<f4(ob.f2().f1());


    return 0;
}