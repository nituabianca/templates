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

void inserareFinalListaSimpla (Carte c, Nod** cap) {
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
	*ht =  initializareHashTable(nr);
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
				cap_lista_i =aux;
			}
		}
	}
}

Carte cautare_nume(HashTable ht, const char * nume) {
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