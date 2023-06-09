#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Carte Carte;
struct Carte {
	int id;
	char* titlu;
	float pret;
};

typedef struct Nod Nod;
struct Nod {
	Carte info;
	Nod* stanga;
	Nod* dreapta;
};

void afisareCarte(Carte c) {
	printf("id: %d; titlu: %s; pret: %f\n", c.id, c.titlu, c.pret);
}

void inserareArboreBinar(Carte c, Nod** radacina) {
	if (*radacina == NULL) {
		Nod* nou = (Nod*)malloc(sizeof(Nod) * 1);
		nou->info = c;
		nou->stanga = NULL;
		nou->dreapta = NULL;
		*radacina = nou;
	}
	else {
		if (c.id > (*radacina)->info.id) {
			inserareArboreBinar(c, &(*radacina)->dreapta);
		}
		else {
			inserareArboreBinar(c, &(*radacina)->stanga);
		}
	}
}

void afisareArboreInOrdine(Nod* radacina) {
	//in ordine: s->r->d
	//preordine: r->s->d
	//postordine: s->d->r?
	if (radacina != NULL) {
		afisareArboreInOrdine(radacina->stanga);
		afisareCarte(radacina->info);
		afisareArboreInOrdine(radacina->dreapta);
	}
}

void citire(FILE* f, Nod** radacina) {
	Carte c;
	int nr;
	char buffer[30];
	fscanf(f, "%d", &nr);
	for (int i = 0; i < nr; i++) {
		fscanf(f, "%d", &c.id);
		fscanf(f, "%s", buffer);
		c.titlu = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
		strcpy(c.titlu, buffer);
		fscanf(f, "%f", &c.pret);
		inserareArboreBinar(c, radacina);
	}
}

int calculInaltime(Nod* radacina) {
	if (radacina) {
		int inaltimeStanga = calculInaltime(radacina->stanga);
		int inaltimeDreapta = calculInaltime(radacina->dreapta);
		if (inaltimeDreapta > inaltimeStanga) {
			return inaltimeDreapta + 1;
		}
		else {
			return inaltimeStanga + 1;
		}
	}
	else {
		return 0;
	}
}

int sumaFrunze(Nod* radacina) {
	if (radacina == NULL) {
		return 0;
	}
	else if(radacina->stanga && radacina->dreapta == NULL) {
		return radacina->info.id;
	}
	else {
		return sumaFrunze(radacina->stanga) + sumaFrunze(radacina->dreapta);
	}
}

void cautareArboreBinar(Nod* radacina, const char* titlu) {
	int gasit = 0;
	if (radacina) {
		if (radacina) {
			if (!strcmp(radacina->info.titlu, titlu)) {
				printf("carte gasita");
			}
			else {
				printf("Carte negasita");
			}
		}
		cautareArboreBinar(radacina->stanga, titlu);
		cautareArboreBinar(radacina->dreapta, titlu);
	}
}

Nod* stergereNod(Nod* radacina, int id) {
	if (radacina == NULL) {
		return radacina;
	}
	if (id < radacina->info.id) {
		radacina->stanga = stergereNod(radacina->stanga, id);
	}
	else if (id > radacina->info.id) {
		radacina->dreapta = stergereNod(radacina->dreapta, id);
	}
	else {
		if (radacina->stanga == NULL && radacina->dreapta == NULL) {
			return NULL;
		}
		else if (radacina->stanga == NULL) {
			Nod* tmp = radacina->dreapta;
			free(radacina);
			return tmp;
		}
		else if (radacina->dreapta == NULL) {
			Nod* tmp = radacina->stanga;
			free(radacina); return tmp;
		}
		struct Nod* nodMinim = radacina->dreapta;
		while (nodMinim->stanga != NULL) {
			nodMinim = nodMinim->stanga;
		}
		radacina->info.id = nodMinim->info.id;
		radacina->dreapta = stergereNod(radacina->dreapta, nodMinim->info.id);
	}
	return radacina;
}


void dezalocareArboreBinar(Nod** radacina) {
	if (*radacina) {
		dezalocareArboreBinar(&(*radacina)->stanga);
		dezalocareArboreBinar(&(*radacina)->dreapta);
		free((*radacina)->info.titlu);
		free(*radacina);
	}
	*radacina = NULL;

}

void main() {
	Nod* radacina = NULL;
	Carte c;
	int suma = 0;
	FILE* f = fopen("fisier.txt", "r");
	citire(f, &radacina);
	afisareArboreInOrdine(radacina);
	printf("\nInaltime arbore: %d\n", calculInaltime(radacina));
	printf("\n%d", sumaFrunze(radacina));

	printf("\nCAUTARE\n");
	cautareArboreBinar(radacina, "carte1");
	printf("\n");
	cautareArboreBinar(radacina, "carte");

	printf("\nstergere nod\n");
	stergereNod(radacina, 23);
	afisareArboreInOrdine(radacina);

	printf("\nstergere arbore\n");
	dezalocareArboreBinar(&radacina);
	afisareArboreInOrdine(radacina);
}
