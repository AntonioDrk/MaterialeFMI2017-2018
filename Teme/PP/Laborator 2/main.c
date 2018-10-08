#include <stdio.h>
#include <stdlib.h>

void pb1() {
    int n,p = 1<<30;
    printf("Introduceti un numar: ");scanf("%d",&n);
    printf("Numarul in binar este: ");
    while(p>0){
        if(p & n) {
            printf("1");
        } else {
            printf("0");
        }
        p = p>>1;
    }
}

void pb2() {
    int x,n;
    printf("x = ");scanf("%d",&x);
    printf("n = ");scanf("%d",&n);
    printf("Numarul %d dupa setarea bit-ului de pe pozitia %d, este: %d\n",x,n,(1<<n) | x);
    printf("Numarul %d dupa stergerea bit-ului de pe pozitia %d, este: %d\n",x,n,~(1<<n) & x);
    printf("Numarul %d dupa stergerea bit-ului de pe pozitia %d, este: %d\n",x,n,~(1<<n) & x);
}

void pb3() {
    int x,y,n,p;
    printf("x = ");scanf("%d",&x);
    printf("y = ");scanf("%d",&y);
}

int main()
{
    printf("%.2f",214.332323f);
    return 0;
}
