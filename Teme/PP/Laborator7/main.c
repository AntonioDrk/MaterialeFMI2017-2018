#include <stdio.h>
#include <string.h>

void problema1a(){
    /// Fisiere
    FILE *f;
    FILE *q;
    /// Deschiderea lor
    f = fopen("in.txt", "r");
    q = fopen("out.txt","w");
    /// Caracterul ce trebuie sters
    char n = fgetc(f);
    printf("Caracterul : %c \n", n);

    char c;
    while(1){
        c = getc(f);
        if(feof(f)){
            break;
        }
        if(c != n)putc(c,q);
    }
    fclose(f);
    fclose(q);
}

void problema1b(){
    /// Fisier
    FILE *f;
    /// Buffer-ul in care stochez textul format
    char buffer[1000];
    int length = 0;
    /// Deschiderea fisierului
    f = fopen("in.txt", "r+");
    /// Caracterul ce o sa fie sters
    char n = fgetc(f);
    printf("Caracterul : %c \n", n);

    char c;
    while(1){
        c = getc(f);
        if(feof(f)){
            break;
        }
        if(c != n) {
            buffer[length] = c;
            length++;
        }
    }
    buffer[length] ='\0';
    fputs(buffer,f);
    fclose(f);
}

void problema2(){
    /// Fisier
    FILE *f;

    ///Declararea buffer-ului in care restitui textul
    char buffer[1000];
    int length = 0;

    f = fopen("in.txt", "r+");

    char n = fgetc(f);
    char m = fgetc(f);

    printf("Caracterul : %c \n", n);
    printf("Va fi inlocuit cu : %c \n", m);

    char c;
    while(1){
        c = getc(f);
        if(feof(f)){
            break;
        }
        if(c != n) {
            buffer[length] = c;
        }else {
            buffer[length] = m;
        }
        length++;
    }
    buffer[length] ='\0';
    fseek(f,2,0);
    fputs(buffer,f);
    fclose(f);
}

int main() {
    problema2();
    return 0;
}