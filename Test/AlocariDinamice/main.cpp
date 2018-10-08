#include <iostream>

using namespace std;

int main()
{
    int dim_curr = 0;
    int *v = NULL;
    int *aux = NULL;
    int x;
    while(1){
        scanf("%d",&x);

        if( x == 0){
            break;
        }

        aux = realloc(v,(dim_curr + 1)*sizeof(int));
        if(aux != NULL){
            aux[dim_curr++] = x;
            v = aux;
        } else {
            free(v);
            return 0;
        }

    }



    return 0;
}
