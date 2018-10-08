#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char **versuri;
    int nr_versuri;
}Poezie;

void versuri_cuvinte_poezie(char *nume_fisier, int *nr_versuri, int *nrMax_lit){
    FILE *f = fopen(nume_fisier,"r");
    if(f == NULL){
        printf("EROARE LA DESCHIDEREA FISIERULUI");
        exit(-1);
    }
    char versCurrent[500];
    while(fgets(versCurrent,500,f)){
        int nr_lit = 0;
        int verif_vers = 0;

        for (int i = 0; i < strlen(versCurrent); ++i) {
            if((versCurrent[i] <= 'Z' && versCurrent[i] >= 'A') || (versCurrent[i] <= 'z' && versCurrent[i] >= 'a')){
                nr_lit++;
                verif_vers = 1;
            }
        }
        if(verif_vers == 1){
            (*nr_versuri)++;
        }
        *nrMax_lit = nr_lit > *nrMax_lit?nr_lit:*nrMax_lit;
        if(feof(f)) break;
    }
    fclose(f);
}

void incarcaPoezie(char *nume_fisier, Poezie *poezia){

    /// MA FOLOSESC DE FUNCTIA ANTERIOARA SA AFLU DIMENSIUNILE DE ALOCARE
    int nr_versuri = 0;
    int nrMax_lit = 0;

    versuri_cuvinte_poezie(nume_fisier,&nr_versuri,&nrMax_lit);

    (*poezia).versuri = (char**)malloc(sizeof(char*) * nr_versuri);

    for (int i = 0; i < nr_versuri; ++i) {
        (*poezia).versuri[i] = (char*)malloc(sizeof(char) * nrMax_lit);
    }

    (*poezia).nr_versuri = nr_versuri;

    /// INCEP A CITI DIN FISIER
    FILE *f = fopen(nume_fisier,"r");
    if(f == NULL){
        printf("EROARE LA DESCHIDEREA FISIERULUI");
        exit(-1);
    }
    char versCurrent[500];
    int index = 0;
    while(fgets(versCurrent,500,f)) {

        int verif_vers = 0;

        for (int i = 0; i < strlen(versCurrent); ++i) {
            if((versCurrent[i] <= 'Z' && versCurrent[i] >= 'A') || (versCurrent[i] <= 'z' && versCurrent[i] >= 'a')) {
                verif_vers = 1;
            }
        }

        if(verif_vers == 1){            /// Daca versul e valid (nu e doar un \n), il copiez in poezia.versuri[index]
            strcpy((*poezia).versuri[index],versCurrent);
        }
        index++;
        if(feof(f)) break;
    }
    fclose(f);
}

int main( )
{
    char numeFisier[] = "bacovia_1.txt";
    Poezie poez;
    incarcaPoezie(numeFisier,&poez);
    for(int i = 0; i < 12; ++i){
        printf("Versul %d: %s",i,poez.versuri[i]);
    }
    return 0;
}
