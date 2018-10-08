#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,*v,i,j,m,mx;
    scanf ("%d", &n);
    v=(int*)malloc(n* sizeof(int));
    for (i=0;i<n;i++)
        scanf ("%d",&v[i]);
    m=v[0];
    mx=v[0];
    for (i=0;i<n;i++)
        if (v[i]<m) m=v[i];
        else if (v[i]>mx) mx=v[i];
    printf ("minimul si maximul sunt=%d %d",m,mx);
    return 0;
}
