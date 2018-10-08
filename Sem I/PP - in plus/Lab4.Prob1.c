#include <stdio.h>
#include <stdlib.h>
typedef int vector[20];

int main()
{   vector v;
    int n,i,k,a,b,j,x,y,mx;
    scanf("%d",&a);
    scanf("%d",&b);
    for (y=a;y<=b;y++)
    {
    n=y;
    x=0;
    while (n>0)
    {
        v[x]=n%10;
        n=n/10;
        if (n<=0)
            break;
          else x++;
    }
    mx=v[0];
    for (i=1;i<x;i++)
    {
    if (v[i]>mx)
        {mx=v[i];
         j=i;
        }
    }
    k=0;
    for (i=0;i<j && k==0;i++)
            if (v[i]>v[i+1] || v[i]==v[i+1])k=1;
    for (i=j;i<x && k==0;i++)
        if (v[i]<v[i+1] || v[i]==v[i+1]) k=1;
    if (k==0)
        printf ("\n%d",y);
    }
     return 0;
}
