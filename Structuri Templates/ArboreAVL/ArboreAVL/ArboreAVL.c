#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Carte Carte;
struct Carte {
	int id;
	char* titlu;
};

typedef struct Nod Nod;
struct Nod {
	Carte info;
	Nod* stanga;
	Nod* dreapta;
};

void afisareCarte(Carte c) {
	printf("id: %d; titlu: %s\n", c.id, c.titlu);
}

void inserareArboreBinar(Nod** radacina, Carte c) {
	if (*radacina == NULL) {
		Nod* nou = (Nod*)malloc(sizeof(Nod) * 1);
		nou->info = c;
		nou->stanga = NULL;
		nou->dreapta = NULL;
		*radacina = nou;
	}
	else {
		if (c.id > (*radacina)->info.id) {
			inserareArboreBinar(&(*radacina)->dreapta, c);
		}
		else {
			inserareArboreBinar(&(*radacina)->stanga, c);
		}
	}
}

void afisareArboreInOrdine(Nod* radacina) {
	if (radacina) {
		afisareArboreInOrdine(radacina->stanga);
		afisareCarte(radacina->info);
		afisareArboreInOrdine(radacina->dreapta);
	}
}

int calculInaltime(Nod* radacina) {
	if (radacina) {
		int inaltimeS = calculInaltime(radacina->stanga);
		int inaltimeD = calculInaltime(radacina->dreapta);
		if (inaltimeD > inaltimeS) {
			return inaltimeD + 1;
		}
		else
		{
			return inaltimeS + 1;
		}
	}
	else {
		return 0;
	}
}

void rotireStanga(Nod** radacina) {
	Nod* aux = (*radacina)->dreapta;
	(*radacina)->dreapta = aux->stanga;
	aux->stanga = (*radacina);
	*radacina = aux;
}

void rotireDreapta(Nod** radacina) {
	Nod* aux = (*radacina)->stanga;
	(*radacina)->stanga = aux->dreapta;
	aux->dreapta = (*radacina);
	*radacina = aux;
}

int calculDezechilibru(Nod* radacina) {
	if (radacina) {
		return calculInaltime(radacina->stanga) - calculDezechilibru(radacina->dreapta);
	}
	else {
		return 0;
	}
}

void inserareAVL(Carte c, Nod** radacina) {
	if (*radacina == NULL) {
		Nod* nou = (Nod*)malloc(sizeof(Nod) * 1);
		nou->info = c;
		nou->stanga = NULL;
		nou->dreapta = NULL;
		*radacina = nou;
	}
	else {
		if (c.id > (*radacina)->info.id) {
			inserareArboreBinar(&(*radacina)->dreapta, c);
		}
		else {
			inserareArboreBinar(&(*radacina)->stanga, c);
		}
	}
	int dezechilibru = calculDezechilibru(*radacina);
	if (dezechilibru == 2) {
		if (calculDezechilibru((*radacina)->dreapta == 1)) {
			rotireDreapta(&(*radacina)->dreapta);
		}
		rotireStanga(radacina);
	}
	if (dezechilibru == 2) {
		if (calculDezechilibru((*radacina)->stanga == 1)) {
			rotireStanga(&(*radacina)->stanga);
		}
		rotireDreapta(radacina);
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
		inserareAVL(c, radacina);
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

int sumaFrunze(Nod* radacina) {
	if (radacina == NULL) {
		return 0;
	}
	else if (radacina->stanga && radacina->dreapta == NULL) {
		return radacina->info.id;
	}
	else {
		return sumaFrunze(radacina->stanga) + sumaFrunze(radacina->dreapta);
	}
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

	FILE* f = fopen("fisier.txt", "r");
	citire(f, &radacina);
	afisareArboreInOrdine(radacina);

	printf("\nCAUTARE\n");
	cautareArboreBinar(radacina, "carte1");
	printf("\n");
	cautareArboreBinar(radacina, "carte");

	printf("\n%d", sumaFrunze(radacina));

	printf("\nstergere nod\n");
	stergereNod(radacina, 23);
	afisareArboreInOrdine(radacina);

	printf("\nstergere arbore\n");
	dezalocareArboreBinar(&radacina);
	afisareArboreInOrdine(radacina);
}