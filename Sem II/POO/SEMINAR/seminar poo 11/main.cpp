#include <iostream>
using namespace std;

class B{
protected:int x;
public:B(int i=3){x=i;};
  virtual B minus(){return 1-x;};


};
class D:public B{
public: D(int i=8):B(i){};
    void afisare(){cout<<x;};

    D minus(int y){return (1+x+y);}


};



int main() {

B* p1=new D;
*p1=p1->minus();
    ((D*)p1)->afisare();

    return 0;
}