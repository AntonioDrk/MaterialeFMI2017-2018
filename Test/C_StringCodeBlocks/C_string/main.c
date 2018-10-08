#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student{
    char Nume[100];
    float Note[10];
    float Medie;
    int Grupa;
};


/// CITIREA UNUI NUMAR SI AL UNUI SIR DE CARACTERE
void citire(int *n, char *Nume, FILE *f){
    fscanf(f,"%d",n);
    fpos_t position = ftell(f);
    position +=2;
    fsetpos(f,&position);
    fgets(Nume,1000,f);
}


int main()
{
    FILE *f;
    struct Student v[100];

    if((f = fopen("in.in","r"))){
        int n,i,j;
        fscanf(f,"%d",&n);                              ///Numarul de elevi
        for(i=0; i < n; i++){
            int nr_note;
            fscanf(f,"%100s %d",v[i].Nume,&nr_note);    ///Numarul de note al elevului
            for(j=0; j < nr_note; j++){
                fscanf(f,"%f",&v[i].Note[j]);           ///Citim fiecare nota
                v[i].Medie += v[i].Note[j];             ///O adaugam la medie
            }
            v[i].Medie /= nr_note;                      ///Dupa citirea fiecarei note, impartim suma notelor la nr notelor ( asa calculam media )
            fscanf(f,"%d",&v[i].Grupa);                 ///La final, in fisier, apare si grupa, o citim
        }
        fprintf(stdout,"Grupa: %d\nElevul: %s\n\n",v[3].Grupa,v[3].Nume);
        fprintf(stdout,"Media: %.1f\n",v[3].Medie);
    } else {
        fprintf(stdout,"Eroare la deschiderea fisierului");
    }
    return 0;
}
