#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Carte Carte;
struct Carte {
	char* titlu;
	int nrPagini;
	float pret;
};

typedef struct Nod Nod;
struct Nod {
	Carte info;
	Nod* next;
};

void afisareCarte(Carte c) {
	printf("Titlu: %s; nrPagini: %d; pret: %5.2f\n", c.titlu, c.nrPagini, c.pret);
}

Nod* inserareInceput(Nod* cap, Carte c) {
	Nod* nou = (Nod*)malloc(sizeof(Nod) * 1);
	nou->info = c;
	nou->next = cap;
	cap = nou;
	return cap;
}

void inserareFinal(Nod* cap, Carte c) {
	Nod* aux = cap;
	Nod* nou = (Nod*)malloc(sizeof(Nod) * 1);
	nou->info = c;
	nou->next = NULL;
	if (cap == NULL) {
		cap = nou;
	}
	else {
		while (aux->next != NULL) {
			aux = aux->next;
		}
		aux->next = nou;
	}
}

void afisareLista(Nod* cap) {
	while (cap) {
		afisareCarte(cap->info);
		cap = cap->next;
	}
}

void citireDinFisier(FILE* f, Nod** cap) {
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
		*cap = inserareInceput(*cap, c);
	}
}

void cautareDupaTitlu(Nod* cap, const char* titlu) {
	int gasit = 0;
	while (cap) {
		if (!strcmp(cap->info.titlu, titlu)) {
			gasit = 1;
		}
		cap = cap->next;
	}
	if (gasit == 1) {
		printf("Carte gasita");
	}
	else {
		printf("Cartea nu a fost gasita");
	}
}

void dezalocareLista(Nod* cap) {
	while (cap) {
		Nod* aux = cap->next;
		free(cap->info.titlu);
		free(cap);
		cap = aux;
	}
}

void main() {
	Nod* cap = NULL;
	Carte c;

	FILE* f = fopen("fisier.txt", "r");
	citireDinFisier(f, &cap);

	afisareLista(cap);

	//dezalocareLista(cap);

	cautareDupaTitlu(cap, "carte1");
	printf("\n\n");
	cautareDupaTitlu(cap, "carte");
}