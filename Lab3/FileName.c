#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    float medieB, medie4A;
} liceu;

typedef enum { medii, superioare, doctorat } studii;

typedef enum { tehnic, economic } profil;

typedef union {
    liceu note;
    float notaL;
    profil p;
} inf;

typedef struct {
    int zi, luna, an;
} dataN;

typedef struct {
    char nume[20], prenume[20];
    dataN dN;
    float s;
    inf info;  // union
    studii st; // field selector
} angajat;

int citire(angajat a[]) {
    FILE* f;
    int i = 0;
    if ((f = fopen("Fisier.txt", "rt")) == NULL) {
        printf("Fisierul nu a fost gasit");
        return -1;
    }
    while (!feof(f)) {
        fscanf(f, "%s %s %d/%d/%d %f %d", a[i].nume, a[i].prenume, &a[i].dN.zi, &a[i].dN.luna, &a[i].dN.an, &a[i].s, &a[i].st);
        switch (a[i].st) {
        case medii:
            fscanf(f, "%f %f", &a[i].info.note.medieB, &a[i].info.note.medie4A);
            break;
        case superioare:
            fscanf(f, "%f", &a[i].info.notaL);
            break;
        case doctorat:
            fscanf(f, "%d", &a[i].info.p);
            break;
        }
        i++;
    }
    return i;
}

void afisare(angajat a[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%s %s %d/%d/%d %f %d\n", a[i].nume, a[i].prenume, a[i].dN.zi, a[i].dN.luna, a[i].dN.an, a[i].s, a[i].st);
        switch (a[i].st) {
        case medii:
            printf("%f %f\n", a[i].info.note.medieB, a[i].info.note.medie4A);
            break;
        case superioare:
            printf("%f\n", a[i].info.notaL);
            break;
        case doctorat:
            printf("%d\n", a[i].info.p);
            break;
        }
    }
}

int main(void) {
    angajat a[20];
    int n;
    n = citire(a);
    if (n != -1)
        afisare(a, n);

    return 0;
}