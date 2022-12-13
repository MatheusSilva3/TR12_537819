#include "heap.h"

//Essa função serve para criar e alocar o espaço da heap, alem de alocar o espaço do vetor de elementos da heap
HEAP* HEAP_create(int n, COMP* comp) {
	HEAP* heap = malloc(sizeof(HEAP));
	heap -> elems = malloc(n * sizeof(void*));
	heap -> N = n;
	heap -> P = 0;
	heap -> comparador = comp;

	return heap;
}

//Essa função serve para adicionar um elemento na heap e ordenalo
void HEAP_add(HEAP* heap, void* novoelem) {
  if (heap -> P < heap -> N) {
    heap -> elems[heap -> P] = novoelem;
	int pos = heap -> P;

	while (heap -> comparador(heap -> elems[pos], heap -> elems[(pos - 1) / 2]) > 0) {
		void* aux = heap -> elems[pos];
		heap -> elems[pos] = heap -> elems[(pos - 1) / 2];
		heap -> elems[(pos - 1) / 2] = aux;	
		pos = (pos - 1) / 2;
	}	

	heap -> P++;
  }
}

//Essa função serve para remover o elemento da heap e reordenalo
void* HEAP_remove(HEAP* heap) {
	void* min = heap -> elems[0];

	heap -> elems[0] = heap -> elems[heap -> P - 1];
	heap -> elems[heap -> P - 1] = min;
	
	heap -> P--;

	int ascendente = 0;
	int descendente = ascendente * 2 + 1;
	
	while (descendente < heap->P) {
		if (descendente + 1 < heap -> P) {
			if (heap -> comparador(heap -> elems[descendente], heap -> elems[descendente + 1]) < 0) {
				descendente += 1;
			}
		}

		if (heap -> comparador(heap -> elems[ascendente], heap -> elems[descendente]) < 0) {
			void* aux = heap -> elems[ascendente];
			heap -> elems[ascendente] = heap -> elems[descendente];
			heap -> elems[descendente] = aux;

			ascendente = descendente;
			descendente = ascendente * 2 + 1;
		} else {
			descendente = heap -> P + 1;
		}
	}

	return min;
}