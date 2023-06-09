//LISTA SIMPLA

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

//LISTA DUBLA

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

//STIVA

#include<stdio.h>
#include<malloc.h>

typedef struct Produs Produs;
struct Produs {
	char* nume;
	float pret;
};

typedef struct Nod Nod;
struct Nod {
	Produs info;
	Nod* next;
};

Produs initializare(const char* nume, float pret) {
	Produs p;
	p.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(p.nume, nume);
	p.pret = pret;
	return p;
}

void afisareProdus(Produs p) {
	printf("Produsul %s are pretul %5.2f", p.nume, p.pret);
}


void push(Produs produs, Nod** varf) {
	Nod* nou = (Nod*)malloc(sizeof(Nod) * 1);
	nou->info = produs;
	nou->next = *varf;
	*varf = nou;
}

void afisareStiva(Nod* varf) {
	while (varf) {
		afisareProdus(varf->info);
		printf("\n");
		varf = varf->next;
	}
}

void pop(Nod** varf) {
	Produs p;
	p.nume = NULL;
	p.pret = 0;
	if (*varf) {
		p = (*varf)->info;
		Nod* tmp = *varf;
		*varf = (*varf)->next;
		free(tmp);
	}
	return p;
}

void main() {
	Nod* varf = NULL;
	Produs p1, p2, p3;
	p1 = initializare("P1", 34.99);
	p2 = initializare("P2", 12.32);
	p3 = initializare("P3", 12.32);

	push(p1, &varf);
	push(p2, &varf);
	push(p3, &varf);

	afisareStiva(varf);

	printf("\ntest pop\n");
	pop(&varf);
	afisareStiva(varf);
}

//COADA

#include<stdio.h>
#include<malloc.h>

typedef struct Produs Produs;
struct Produs {
	char* nume;
	float pret;
};
typedef struct Nod Nod;
struct Nod {
	Produs info;
	Nod* next;
};

Produs initializare(const char* nume, float pret) {
	Produs p;
	p.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(p.nume, nume);
	p.pret = pret;
	return p;
}

void afisareProdus(Produs p) {
	printf("Produsul %s are pretul %5.2f\n", p.nume, p.pret);
}

void put(Produs p, Nod** first) {
	Nod* nou = (Nod*)malloc(sizeof(Nod) * 1);
	nou->info = p;
	nou->next = NULL;
	if (*first) {
		Nod* tmp = *first;
		while (tmp->next) {
			tmp = tmp->next;
		}
		tmp->next = nou;
	}
	else
		*first = nou;
}

void afisareCoada(Nod* first) {
	while (first != NULL) {
		afisareProdus(first->info);
		printf("\n");
		first = first->next;
	}
}

void pop(Nod** first) {
	Produs p;
	p.nume = NULL;
	p.pret = 0;
	if (*first) {
		p = (*first)->info;
		Nod* tmp = *first;
		*first = (*first)->next;
		free(tmp);
	}

	return p;
}


void main() {
	Nod* first = NULL;
	put(initializare("P1", 12.32), &first);
	put(initializare("P2", 12.32), &first);
	put(initializare("P3", 12.32), &first);

	afisareCoada(first);

	printf("\ntest pop\n");
	pop(&first);
	afisareCoada(first);
}

//HASHTABLE

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Carte Carte;
struct Carte {
	int nrPag;
	char* titlu;
	float pret;
};

typedef struct Nod Nod;
struct Nod {
	Nod* next;
	Carte info;
};

typedef struct HashTable HashTable;
struct HashTable {
	int dim;
	Nod** vector;
};

void afisareCarte(Carte c) {
	printf("Titlu: %s; nrPag: %d; pret: %f\n", c.titlu, c.nrPag, c.pret);
}

HashTable initializareHashTable(int dim) {
	HashTable ht;
	ht.dim = dim;
	ht.vector = (Nod**)malloc(sizeof(Nod*) * ht.dim);
	for (int i = 0; i < ht.dim; i++) {
		ht.vector[i] = NULL;
	}
	return ht;
}

void inserareFinalListaSimpla(Carte c, Nod** cap) {
	Nod* nou = (Nod*)malloc(sizeof(Nod) * 1);
	nou->info = c;
	nou->next = NULL;
	if (*cap) {
		Nod* temp = *cap;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nou;
	}
	else {
		*cap = nou;
	}
}

int hash(const char* titlu, int dim) {
	return strlen(titlu) % dim;
}

void inserareChaining(HashTable ht, Carte c) {
	if (ht.dim > 0) {
		int poz;
		poz = hash(c.titlu, ht.dim);
		if (poz < ht.dim && poz >= 0) {
			inserareFinalListaSimpla(c, &ht.vector[poz]);
		}
	}
}

//void inserareLinearProbing(Carte* c, HashTable ht) {
//	int poz;
//	if (ht.vector) {
//		poz = hash(c->titlu, ht.dim);
//		if (ht.vector[poz] == NULL) {
//			ht.vector[poz] = c;
//		}
//		else {
//			int index = 1;
//			while (poz + index < ht.dim) {
//				if (ht.vector[poz + index] == NULL) {
//					ht.vector[poz + index] = c;
//					poz = poz + index;
//					break;
//				}
//				index++;
//			}
//		}
//	}
//}

void afisareHashTable(HashTable ht) {
	for (int i = 0; i < ht.dim; i++) {
		if (ht.vector[i]) {
			Nod* aux = ht.vector[i];
			printf("Poz din ht: %d\n", i);
			while (aux) {
				afisareCarte(aux->info);
				aux = aux->next;
			}
		}
		else {
			printf("Poz %d goala\n", i);
		}
	}
}

void citire(FILE* f, HashTable* ht) {
	Carte c;
	char buffer[30];
	int nr;
	fscanf(f, "%d", &nr);
	*ht = initializareHashTable(nr);
	for (int i = 0; i < nr; i++) {
		fscanf(f, "%d", &c.nrPag);
		fscanf(f, "%s", buffer);
		c.titlu = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
		strcpy(c.titlu, buffer);
		fscanf(f, "%f", &c.pret);
		inserareChaining(*ht, c);
	}
}



void dezalocare(HashTable ht) {
	for (int i = 0; i < ht.dim; i++) {
		if (ht.vector[i]) {
			Nod* cap_lista_i = ht.vector[i];
			while (cap_lista_i) {
				Nod* aux = cap_lista_i->next;
				free(cap_lista_i->info.titlu);
				free(cap_lista_i);
				cap_lista_i = aux;
			}
		}
	}
}

Carte cautare_nume(HashTable ht, const char* nume) {
	for (int i = 0; i < ht.dim; i++) {
		if (ht.vector[i]) {
			Nod* aux = ht.vector[i];
			while (aux) {
				if (!strcmp(aux->info.titlu, nume))
					return aux->info;
				aux = aux->next;
			}
		}
		else {
			printf("Poz %d goala\n", i);
		}
	}
}

void main() {
	HashTable ht;
	Carte c;
	FILE* f = fopen("fisier2.txt", "r");
	citire(f, &ht);

	afisareHashTable(ht);
	c = cautare_nume(ht, "carte1");
	printf("%s", c.titlu);

	//dezalocare(ht);
}

//ARBORE BINAR

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
	else if (radacina->stanga && radacina->dreapta == NULL) {
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


//AVL

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

//HEAP

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Carte Carte;
struct Carte {
	int id;
	char* titlu;
};

typedef struct Heap Heap;
struct Heap {
	int dim;
	Carte* vector;
};

void afisareCarte(Carte c) {
	printf("id: %d, titlu: %s\n", c.id, c.titlu);
}

void inserareHeap(Heap* heap, int i, Carte c) {
	heap->vector[i] = c;
}

void citire(FILE* f, Heap* heap) {
	Carte c;
	int nr;
	char buffer[30];
	fscanf(f, "%d", &nr);
	heap->vector = (Carte*)malloc(sizeof(Carte) * nr);
	heap->dim = nr;
	for (int i = 0; i < nr; i++) {
		fscanf(f, "%d", &c.id);
		fscanf(f, "%s", buffer);
		c.titlu = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
		strcpy(c.titlu, buffer);
		inserareHeap(heap, i, c);
	}
}

void afisareHeap(Heap heap) {
	for (int i = 0; i < heap.dim; i++) {
		afisareCarte(heap.vector[i]);
	}
}

void filtrare(Heap heap, int index) {
	if (heap.dim > 0) {
		int pozS = 2 * index + 1;
		int pozD = 2 * index + 2;
		int pozMax = index;

		if (heap.dim > pozS && heap.vector[pozMax].id < heap.vector[pozS].id) {
			pozMax = pozD;
		}
		if (heap.dim > pozD && heap.vector[pozMax].id < heap.vector[pozD].id) {
			pozMax = pozS;
		}

		if (pozMax != index) {
			Carte aux = heap.vector[pozMax];
			heap.vector[pozMax] = heap.vector[index];
			heap.vector[index] = aux;

			filtrare(heap, pozMax);
		}
	}
}

void extragere(Heap* heap, Carte* carte) {
	(*carte) = heap->vector[0];
	Carte aux = heap->vector[0];
	heap->vector[0] = heap->vector[heap->dim - 1];
	heap->vector[heap->dim - 1] = aux;
	heap->dim -= 1;
	filtrare((*heap), 0);

}

void dezalocareHeap(Carte** vector, int dim) {
	for (int i = 0; i < dim; i++) {
		free((*vector)[i].titlu);

	}
	free(*vector);
}

void main() {
	Heap heap;
	Carte c;

	FILE* f = fopen("fisier.txt", "r");
	citire(f, &heap);
	afisareHeap(heap);

	printf("\n\n");
	for (int i = heap.dim / 2 - 1; i >= 0; i--) {
		filtrare(heap, i);
	}
	afisareHeap(heap);

	printf("\n\n");
	extragere(&heap, &c);
	afisareHeap(heap);

	printf("\ndezalocare\n");
	dezalocareHeap(&heap.vector, heap.dim);
	//afisareHeap(heap);
}

//GRAF

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
		while (vecini) {
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