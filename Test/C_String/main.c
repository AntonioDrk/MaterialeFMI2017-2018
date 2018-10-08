#include <stdio.h>
#include <string.h>
int main() {
    FILE *f;
    if(f = fopen("in.in","r")){
        char a[20];
        int n;
        fscanf(f,"%d",&n);
        fgets(a,20,f);
        a[strlen(a)] = '\0';
        printf("Numarul: %d \nSirul de caractere: %s",n,a);
    } else {
        printf("Eroare la deschiderea fisierului");
    }
    return 0;
}