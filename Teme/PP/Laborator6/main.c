#include <stdio.h>
#include <math.h>
#include <stdlib.h>

float squareRoot(float x){
    return sqrtf(x);
}

float inverse(float x){
    return 1/x;
}

float modified_sin(float x){
    return sinf(x);
}

typedef float (*funcDef)(float);

void problema4(){
    int n ;
    scanf("%d", &n);
    int a[n][n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d",*(a + i) + j);
        }
    }
    if(n%2 == 1){
        printf("Elementul de la intersecţia diagonalelor este: %d\n",*(*(a + n/2) + n/2));
    }
    printf("Elementele de pe diagonale sunt: ");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if( i == j || i+j == n - 1){
                printf("%d ",*(*(a + i) + j));
            }
        }
    }
}

int main() {
    funcDef v[] = {squareRoot,inverse,modified_sin}; /// For problem 3
    ///printf("inverse(453) : %.3f \n", v[2](453));
    ///problema4();
    printf("%s",getenv("DAY"));

    return 0;
}