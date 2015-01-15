#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include<vector>
#include "Profiler.h"
#include <queue>
#include<time.h>

Profiler profiler("profiler");
int varfuri, muchii;

enum culoare { ALB, GRI, NEGRU} ;
std::queue<int>queue;

typedef struct Nod {
	int data;
	int pred;
	int dist;
	culoare cul;
	std::vector<int>vecini;

}vf;

 vf root[201];
 int poz, comp, atr, total,totaltot;
 
void BFS(int sursa) {

	//initializare noduri
	
	for(int i=0; i <= varfuri; i++) {
		root[i].cul = ALB;
		root[i].dist =MAXINT;
		root[i].pred = -1;
		atr += 3;
	}

	root[sursa].cul = GRI;
	root[sursa].dist = 0;
	root[sursa].pred = -1;
	atr +=3 ;

	queue.empty();
	queue.push(root[sursa].data);
	//printf("Am mers la::: %d",root[sursa].data);

	while (queue.size() != 0) {
		
		int pozNext =queue.front();
		atr += 1;
		//printf("Am mers la: %d \n", pozNext);

		//printf (" %d \t \n", root[pozNext].pred);
		printf(" %d ", pozNext);
		if (root[root[pozNext].pred].pred != root[pozNext].pred) printf("\n");
		for (int y = 0 ; y < root[pozNext].vecini.size(); y++) {printf("\t");}
			queue.pop();
		for(int i = 0; i< root[pozNext].vecini.size(); i++) {

			if (root[root[pozNext].vecini[i]].cul == ALB) {
				root[root[pozNext].vecini[i]].cul = GRI;
				root[root[pozNext].vecini[i]].dist +=1;
				root[root[pozNext].vecini[i]].pred = root[pozNext].data;
				queue.push(root[root[pozNext].vecini[i]].data);
				//printf("Am mers la %d",root[i].data);
				comp += 1;
				atr += 3;
			}//if
		}//for
		root[pozNext].cul = NEGRU;
		atr +=1;
	}//while
}//BFS

void pathPrint(vf *root, int sursa, int dest) {
	if (root[sursa].data == root[dest].data) {
	printf(" %d \n", root[sursa].data);
	}
	else if (root[dest].vecini.size() == NULL) {
			printf("Nu exista drum de la %d la %d \n", root[sursa].data, root[dest].data);
		}
		else {
			pathPrint(root, sursa, root[root[dest].vecini[0]].data);
			printf(" %d \n", root[dest].data);
		}
}

void printCopii(int varf) {
	for (int i = 0; i< root[varf].vecini.size(); i++) {
		printf("\t %d", root[varf].vecini[i]);
	}
}

void prettyPrint(int varfuri) {
	
	for(int i = 0; i< varfuri; i++) {
		//print tab de size copii
		for (int j = 0; j< root[i].vecini.size(); j++) { printf("\t"); }
		printf(" %d \n", i);
		printCopii(i);
		printf("\n");

	}	
}

int main() {

	int selectie;
	
	printf(" 1- Demonstratie 2-Cerinta 1 3- Cerinta 2\n");
	scanf(" %d ", &selectie);

	switch(selectie) {
	case 1:

		varfuri = 10;
		muchii = 9;
		srand (time(NULL));

		for(int i = 0; i < varfuri; i++) {
			root[i].cul = ALB;
			root[i].dist = MAXINT;
			root[i].pred = NULL;
			root[i].data = i;
		}
		//int m;
		//m = 0;
		//while (m < muchii) {
		//for( int i = 0; i < varfuri; i++ ) {

			int vect1[15], vect2[15];
			
			FillRandomArray(vect1, muchii, 10, varfuri+9, FALSE, 0);
			FillRandomArray(vect2, muchii, 10, varfuri+9, TRUE, 0);
			int random;
			for (int j = 0; j< muchii;j++) { 
				if (vect1[j] == vect2[j]) {
					do {
						random = 10 + rand()% varfuri;
					} while (random == vect2[j]);
					vect1[j] = random;
				}
				root[vect1[j] - 10].vecini.push_back(vect2[j] - 10);
			}

			//int nod1 = rand() % varfuri;
			//int nod2 = rand() % varfuri;
			/**
			for (int j = 0; j < root[i].vecini.size(); j++) {
				
				while(root[nod2].vecini[i] == nod1) {
					nod1 = rand()%varfuri;
					}
			}**/

			// + testare aceeasi muchie
			
			//m++;
			//if (m == muchii) break;
		//}
		//}

		for (int i = 0; i < varfuri; i++) {
			printf("%d: ", i );
	
			for (int j = 0; j < root[i].vecini.size(); j++) {
				printf("%d, ", root[i].vecini[j] );
			}

			printf("\n");
		}

		printf("\n Run BFS! \n");
		BFS(1);
		printf("\n Run Path Print! \n");
		pathPrint(root,1,3);
		printf("\n Run Pretty Print \n");
		prettyPrint(10);
		/**
		printf("\nGGG\n");

		int vectp[10];
		for (int i = 0; i < varfuri; i++) {
			vectp[i] = root[i].pred;
			printf(" %d ", vectp[i]);
		}

		int aux;aux=0;
		for (int i = 0; i < varfuri; i++) {
			for (int j = 0; j < varfuri;j ++) {
				if (vectp[j] > vectp[i]){
					aux = vectp[j];
					vectp[j]= vectp[i];
					vectp[i]=aux;
				}
			}
		}

		printf("\nAFIS SORTAT\n");
		for (int i = 0; i < varfuri; i++) {
			printf("%d ",vectp[i]);
		}

		int vectp2[10];
		int size;
		size = 0;
		vectp2[0] = vectp[0];

		printf("RRR");
		
		int f;
		for ( f = 1; f < varfuri; f++) {
			printf("%d",vectp[f]);
			int x = vectp[f-1];
			if (x != vectp[f]) {
				vectp2[f] = vectp[f];
				size++;
			}else
				vectp2[f] = 11;
		}
		printf("\nAFIS\n");
		for (int c = 0; c <= size; c++) {
			printf(" %d ",vectp2[c]);
		}
		printf("\n FINAL \n");
		
		for (int i = 0; i <= size; i++) {
		
			for (int j = 0; j < varfuri; j++) {
				if (root[j].pred == vectp2[i]) printf(" %d ", root[j].data);
			}
			printf("\n");
		}**/

		int pauza;
		scanf(" %d ", &pauza);

		break;

	case 2:
		
		varfuri = 100;
		total =0;
		for(int i = 1; i <= varfuri; i++) {
			root[i].cul = ALB;
			root[i].dist = MAXINT;
			root[i].pred = NULL;
			root[i].data = i;
		}

		for (int k = 1000; k<= 5000; k = k + 100) {
			total += comp + atr;
			//int m;
			//m = 0;
			comp = 0;
			atr = 0;

			int vect1[5001], vect2[5001];
			
			FillRandomArray(vect1, k , 10, 109, FALSE, 0);
			FillRandomArray(vect2, 100, 10, 109, TRUE, 0);

			//for (int ll = 0; ll < 5000; ll = ll + 1) {
			//printf("%d \n", vect1[ll]);
			//}
			//for (int ll = 0; ll < 100; ll = ll + 1) {
			//printf("%d \n", vect2[ll]);
			//}

			int j;
			j = 0;
			while (j < k) { 
				for (int i = 0; i < varfuri; i++) { 
				/**	if (vect1[i] == vect2[j]) {
					do {
						random = 10 + rand()% varfuri;
					} while (random == vect2[j]);
					vect1[i] = random;
				}**/
					root[vect2[i] - 10].vecini.push_back(vect1[j] - 10);
					j++;
					printf("%d=>%d \n", vect2[i]-10, vect1[j]-10);
				}
			}

			

			//for (int j = 0; j< muchii;j++) { 

			//	root[vect2[j] - 10].vecini.push_back(vect1[j] - 10);
			//}

			//while (m < k) {

			//int nod1 = rand() % varfuri;
			//int nod2 = rand() % varfuri;
			// +  testare aceeasi muchie
			//printf("%d=>%d \n",nod1, nod2);
			
			//root[nod2].vecini.push_back(nod1);
			//m++;
			//root[nod2].pred = nod1;
			//if (m = k) break;
			//}
			
			BFS(3);
			
			//for (int j = 1; j <= 100; j++) {
			//printf("Nod:%d => Culoare: %d => Pred: %d\n", root[j].data, root[j].cul, root[j].pred);
			//}
			profiler.countOperation("Atribuiri", k, atr );
			profiler.countOperation("Comparatii", k, comp );
			profiler.countOperation("Total", k, total );
		}

		pauza;
		scanf(" %d ", &pauza);

		profiler.createGroup("Operatii","Atribuiri", "Comparatii","Total");
		profiler.showReport();

		break;
	case 3:
		srand (time(NULL));
		muchii = 9000;
		total = 0;

		for(int i= 100; i<= 200; i = i + 10 ) {
			totaltot += total;
			total += comp + atr;
			//int m;
			//m = 0;
			comp = 0;
			atr = 0;

			for(int j = 0; j < i; j++) {
			
				root[j].cul = ALB;
				root[j].dist = MAXINT;
				root[j].pred = NULL;
				root[j].data = j;
			}

			int vect1[9001], vect2[9001];
			
			FillRandomArray(vect1, muchii, 10, i + 9, FALSE, 0);
			FillRandomArray(vect2, i, 10, i + 9, TRUE, 0);
			for (int w= 0;w<i;w++) {printf("%d \n",vect2[w]-10);}
			int l;
			l = 0;
			while (l < 8800) { 
				for (int ll = 0; ll < i; ll++) { 
				/**	if (vect1[l] == vect2[ll]) {
					do {
						random = 10 + rand()% i;
					} while (random = vect2[ll]);
					vect1[l] = random;
				}**/
				root[vect2[ll] - 10].vecini.push_back(vect1[l] - 10);
				l++;
				//if (l = 9000) break;
				printf("%d=>%d \n", vect2[ll]-10, vect1[l]-10);
				}

			} 
			
			printf("%d si i %d fdfdf",l,i);

			//for (int j = 0; j< muchii;j++) { 

			//	root[vect2[j] - 10].vecini.push_back(vect1[j] - 10);
			//}
			//m = 0;
			//while (m<9000) {

				//int nod1 = rand() % i;
				//int nod2 = rand() % i;
				// + testare aceeasi muchie
				//root[nod2].vecini.push_back(nod1);
				//m++;
				//if (m = 9000) break;
			//}

			BFS(1);

			profiler.countOperation("Atribuiri", i, atr );
			profiler.countOperation("Comparatii", i, comp );
			profiler.countOperation("Total", i, total );
			
		}

		pauza;
		scanf(" %d ", &pauza);

		profiler.createGroup("Operatii","Atribuiri", "Comparatii","Total");
		profiler.showReport();

		break;

	default:

		printf(" Operatie Invalida! ");

		break;
	}
return 0;
}