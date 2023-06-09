#define _CRT_SECURE_NO_WARNINGS
#include<malloc.h>
#include<stdio.h>
#include<string.h>

typedef struct Carte Carte;
typedef struct NodSecundar NodSecundar;
struct Carte {
	int id;
	char* titlu;
};

typedef struct NodPrincipal NodPrincipal;
struct NodPrincipal {
	Carte info;
	NodPrincipal* next;
	NodSecundar* vecini;
};


struct NodSecundar {
	NodPrincipal* info;
	NodSecundar* next;
};

void afisareCarte(Carte c) {
	printf("id: %d; titlu: %s\n", c.id, c.titlu);
}

void inserareListaPrincipala(NodPrincipal** cap, Carte c) {
	NodPrincipal* nou = (NodPrincipal*)malloc(sizeof(NodPrincipal) * 1);
	nou->info = c;
	nou->next = NULL;
	nou->vecini = NULL;
	NodPrincipal* aux = *cap;
	if (*cap) {
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = nou;
	}
	else {
		*cap = nou;
	}
}

void inserareListaSecundara(NodSecundar** cap, NodPrincipal* info) {
	NodSecundar* nou = (NodSecundar*)malloc(sizeof(NodSecundar));
	nou->info = info;
	nou->next = NULL;
	NodSecundar* aux = *cap;
	if (*cap) {
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = nou;
	}
	else {
		*cap = nou;
	}
}

void afisareGraf(NodPrincipal* np) {
	while (np) {
		afisareCarte(np->info);
		NodSecundar* aux = np->vecini;
		printf("\nVecini: \n");
		while (aux) {
			afisareCarte(aux->info->info);
			aux = aux->next;
		}
		printf("\n");
		np = np->next;
	}
}

NodPrincipal* cautareNod(NodPrincipal* nod, int id) {
	while (nod && nod->info.id != id) {
		nod = nod->next;
	}
	return nod;
}


void inserareVecini(NodPrincipal* nod, int id1, int id2) {
	NodPrincipal* nod1 = cautareNod(nod, id1);
	NodPrincipal* nod2 = cautareNod(nod, id2);
	if (nod1 != NULL && nod2 != NULL) {
		inserareListaSecundara(&nod1->vecini, nod2);
		inserareListaSecundara(&nod2->vecini, nod1);
	}
}

void citire(FILE* f, NodPrincipal** np) {
	Carte c;
	int nr;
	char buffer[30];
	fscanf(f, "%d", &nr);
	for (int i = 0; i < nr; i++) {
		fscanf(f, "%d", &c.id);
		fscanf(f, "%s", buffer);
		c.titlu = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
		strcpy(c.titlu, buffer);
		inserareListaPrincipala(np, c);
	}
}

int getNrNoduri(NodPrincipal* graf) {
	int nr = 0;
	while (graf) {
		nr++;
		graf = graf->next;
	}
	return nr;
}

void dezalocareGraf(NodPrincipal** graf) {
	while (*graf) {
		free((*graf)->info.titlu);
		NodSecundar* vecini = (*graf)->vecini;
		while(vecini) {
			NodSecundar* temp = vecini;
			vecini = vecini->next;
			free(temp);

		}
		NodPrincipal* temp = *graf;
		(*graf) = (*graf)->next;
		free(temp);
	}
	*graf = NULL;
}

void main() {
	NodPrincipal* graf = NULL;
	Carte c;

	FILE* f = fopen("fisier.txt", "r");
	citire(f, &graf);

	inserareVecini(graf, 1, 2);
	inserareVecini(graf, 1, 3);
	inserareVecini(graf, 2, 3);

	afisareGraf(graf);

	int nr = getNrNoduri(graf);
	printf("\nNr noduri: %d\n", nr);

	printf("\nDEZALOCARE\n");
	dezalocareGraf(&graf);
	afisareGraf(graf);

}