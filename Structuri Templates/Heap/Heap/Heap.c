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
	dezalocareHeap(&heap.vector,heap.dim);
	//afisareHeap(heap);
}