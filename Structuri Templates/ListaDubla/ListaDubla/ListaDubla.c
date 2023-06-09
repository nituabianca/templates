#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Carte Carte;
struct Carte {
	int nrPagini;
	char* titlu;
	float pret;
};
typedef struct Nod Nod;
struct Nod {
	Nod* next;
	Nod* prev;
	Carte info;
};

typedef struct ListaDubla ListaDubla;
struct ListaDubla {
	Nod* first;
	Nod* last;
};

void afisareCarte(Carte c) {
	printf("titlu: %s, nrPag: %d, pret: %f\n", c.titlu, c.nrPagini, c.pret);
}

void inserareInceput(ListaDubla* ld, Carte c) {
	Nod* nou = (Nod*)malloc(sizeof(Nod) * 1);
	nou->info = c;
	nou->prev = NULL;
	nou->next = ld->first;
	if (ld->first != NULL) {
		ld->first->prev = nou;
	}
	else {
		ld->last = nou;
	}
	ld->first = nou;
}

void inserareFinal(ListaDubla* ld, Carte c) {
	Nod* nou = (Nod*)malloc(sizeof(Nod) * 1);
	nou->info = c;
	nou->prev = ld->last;
	nou->next = NULL;
	if (ld->last != NULL)
		ld->last->next = nou;
	else
		ld->first = nou;
	ld->last = nou;
}

void afisareLista(ListaDubla ld) {
	while (ld.first) {
		afisareCarte(ld.first->info);
		ld.first = ld.first->next;
	}
}

void citire(FILE* f, ListaDubla* ld) {
	Carte c;
	int nr;
	char buffer[30];
	fscanf(f, "%d", &nr);
	for (int i = 0; i < nr; i++) {
		fscanf(f, "%d", &c.nrPagini);
		fscanf(f, "%s", buffer);
		c.titlu = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
		strcpy(c.titlu, buffer);
		fscanf(f, "%f", &c.pret);
		inserareFinal(ld, c);
	}
}

void cautare(ListaDubla ld, const char* titlu) {
	int gasit = 0;
	while (ld.first) {
		if (!strcmp(ld.first->info.titlu, titlu)) {
			gasit = 1;
		}
		ld.first = ld.first->next;
	}
	if (gasit == 1) {
		printf("Carte gasita");
	}
	else {
		printf("Cartea nu a fost gasita");
	}
}

void dezalocare(ListaDubla* ld) {
	while (ld->first) {
		free(ld->first->info.titlu);
		ld->first = ld->first->next;
		if (ld->first) {
			free(ld->first->info.titlu);
		}
		free(ld->first);
		ld->last = NULL;
		ld->first = NULL;
	}
}

void main() {
	ListaDubla ld;
	ld.first = NULL;
	ld.last = NULL;
	Carte c;

	FILE* f = fopen("fisier.txt", "r");
	citire(f, &ld);

	afisareLista(ld);

	//dezalocare(&ld);

	cautare(ld, "carte1");
	cautare(ld, "carte");
}