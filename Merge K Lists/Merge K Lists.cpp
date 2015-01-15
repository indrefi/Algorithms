/*
Indre Ionut

Imbinarea a k liste ordonate intr-un mod eficient O(n log k).
*/

#include <conio.h>
#include "Profiler.h"
#include <stdio.h>
#include <stdlib.h>

Profiler profiler("profiler");

int n, k, heapSize, vectorSize;

struct Nod {
	int val;
	Nod *urm;
};

void MinHeapify(Nod *vector[], int i) {
	int left = (2 * i);     
	int right = ((2 * i) + 1);
	int min;

	if ((left <= heapSize)) {
		profiler.countOperation("Operatii", vectorSize);
		if (vector[left]->val < vector[i]->val) {
			min = left;
		}
		else {
			min = i;
		}
	
	}
	else {
		min = i;
	}

	if ((right <= heapSize)) {
		profiler.countOperation("Operatii", vectorSize);
		if (vector[right]->val < vector[min]->val) {
			min = right;
		}
	}

	if (min != i) {
		profiler.countOperation("Operatii", vectorSize, 3);
		Nod *swap;
		swap = vector[i];
		vector[i] = vector[min];
		vector[min] = swap;
		MinHeapify(vector, min);
	}
}

Nod *Imbinare(Nod* listaTemp[]) {
	heapSize = k;
	Nod *rad = NULL;
	Nod *aux = NULL;
	Nod *vector[100];

	int i;

	for (i = 1; i <= k; i++) {
		vector[i] = listaTemp[i -1];
		profiler.countOperation("Operatii", vectorSize);
	}

	for (i = (heapSize / 2); i >= 1; i--)
		MinHeapify(vector, i);

	i = 0;
	
	while (i <= n) {
		if (rad == NULL) {
			aux = rad = vector[1];
			profiler.countOperation("Operatii", vectorSize);
		}
		else {
			aux->urm = vector[1];
			aux = vector[1];
			profiler.countOperation("Operatii", vectorSize, 2);
		}

		profiler.countOperation("Operatii", vectorSize);
		if (vector[1]->urm != NULL) {
			profiler.countOperation("Operatii", vectorSize);
			vector[1] = vector[1]->urm;
		}
		else {
			profiler.countOperation("Operatii", vectorSize);
			vector[1] = vector[heapSize];
			heapSize--;
		}

		MinHeapify(vector, 1);
		i++;
	}
	return rad;
}

void main() {
		
	int selectie, i, j;
	
	printf("1- Demonstratie 2- Imbinate k Liste \n");
	scanf("%d", &selectie);

	switch(selectie) {
		case 1:
			{
				n = 20;
				k = 4;
				int vector[80];
				Nod *Lista[4];

				for (i = 0; i < k; i++) {
					Lista[i] = NULL;
					FillRandomArray(vector, n / k, 0, 100, false, 1);
					for (j = 0; j < n / k; j++) {
						Nod *nod = (Nod*) malloc (sizeof( Nod));
						Nod *temp;

						nod->val = vector[j];
						nod->urm = NULL;
						
						if (Lista[i] == NULL) {
							Lista[i] = nod;
						}
						else {
							temp = Lista[i];
							while (temp->urm != NULL) {
								temp = temp->urm;
							}
							temp->urm = nod;
						}
					}	
				}

				for (i = 0; i < k; i++) {
					Nod *p;
					p = Lista[i];
					printf("\n");
					while (p != NULL){
					printf("%d ",p->val);
					p = p->urm;
					
					}
				}

				Nod *imbinate = Imbinare(Lista);

				printf("Listele Imbinare sunt: \n");
				for (i = 0; i < n; i++) {
					printf("%d ", imbinate->val);
					imbinate = imbinate->urm;
				}
			} // case 1
		break;

		case 2:
			{
				int vector[10000], valoareK = 0;
				n = 10000;

				while (valoareK <3 ) {					
					if (valoareK == 0)  k = 5;
					if (valoareK == 1)  k = 10;
					if (valoareK == 2)  k = 100;

				for (n = 100; n <= 10000; n += 100) {
					for (int rep = 0; rep < 5; rep++) {
						Nod *Lista[10000] = { NULL };
						
						for (i = 0; i < k; i++) {
							Lista[i] = NULL;
							FillRandomArray(vector, n / k, 0, 10000, false, 1);

							for (j = 0; j < n / k; j++) {
								Nod *nod = (Nod*) malloc (sizeof( Nod));
								Nod *aux;

								nod->val = vector[j];
								nod->urm = NULL;

								if (Lista[i] == NULL) {
									Lista[i] = nod;
								}
								else {
									aux = Lista[i];
									while (aux->urm != NULL) {
										aux = aux->urm;
									}
									aux->urm = nod;
								}
							 } // for j
						}// for i
						Nod *ListaOrdonata = Imbinare(Lista);
					} // for rep
				} // for n
				valoareK ++;
				} // selectie k

				profiler.showReport();
			}
		break;

		default:
			printf("Selectie invalida! \n");
		break;
	} //switch

	getch();

} //main