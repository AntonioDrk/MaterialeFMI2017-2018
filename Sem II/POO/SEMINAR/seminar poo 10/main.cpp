#include <iostream>
using namespace std;


class B{
public: virtual int f()const{cout<<"1";return 1;};
    virtual void f(int x)const{cout<<" 3";};
    virtual void g()const{};

};

class D1:public B{
public:void g()const{};

};


class D2:public B{
public: int f()const {
        cout << "2";
        return 2;

    }


};




int main() {
  /*  int x;
    D2 ob;
    x=ob.f();
    ob.f(x); ///ca sa mearga trebuie sa fie ob.B::f(x);
*/

  B* p=new D2;

  int x;
  x=p->f();
  p->f(x);



    return 0;
}