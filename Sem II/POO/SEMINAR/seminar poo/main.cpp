#include <iostream>

using namespace std;


class A{
protected:
static int x;
private:int y;
public:
A(int i){
x=i;
y=-i+4;
}
int put_x(A a){return a.x+a.y;}
}o1(5);

int A::x=7;

int main()
{
A a(10);
cout<<a.put_x(20)<<'\n';
cout<<a.put_x(1);

    return 0;
}
