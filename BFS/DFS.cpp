#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include<vector>
#include "Profiler.h"
#include <queue>
#include<time.h>
#include <string.h>

Profiler profiler("profiler");

enum culoare { ALB, GRI, NEGRU};
enum label { TREE, BACK, FORWARD, CROSS };
std::queue<int>queue;
int varfuri, muchii, timp = 0, comp,atr, total;

typedef struct LabMuchie {
	int unu;
	int doi;
	label cullab;
}labMuc;

typedef struct Nod {
	int data;
	int pred;
	int dist;
	int dtime;
	int ftime;
	culoare cul;
	labMuc lab;
	std::vector<int>vecini;
}vf;

vf root[201];

void DFS_VISIT(int i) {
	timp ++;
	root[i].dtime = timp;
	root[i].cul = GRI;
	atr += 3;
	//printf("> %d ",root[i].data);
	for(int j = 0; j < root[i].vecini.size(); j++) {
		comp += 1;
		if (root[root[i].vecini[j]].cul == ALB) {
			atr += 1;
			root[root[i].vecini[j]].pred = root[i].data;
			//printf("> %d ",root[root[i].vecini[j]].data);
			int poz;
			poz = root[root[i].vecini[j]].data;
			DFS_VISIT(poz);
		}
		else {

			if (root[root[i].vecini[j]].cul = GRI) {
				root[root[i].vecini[j]].lab.unu = root[i].data;
				root[root[i].vecini[j]].lab.doi = root[root[i].vecini[j]].data;
				root[root[i].vecini[j]].lab.cullab = BACK;
				atr+=3;
			}
		
			if (root[i].dtime < root[root[i].vecini[j]].dtime) {
				root[root[i].vecini[j]].lab.unu = root[i].data;
				root[root[i].vecini[j]].lab.doi = root[root[i].vecini[j]].data;
				root[root[i].vecini[j]].lab.cullab = FORWARD;
				atr+=3;
			}

			if (root[i].dtime > root[root[i].vecini[j]].dtime) {
				root[root[i].vecini[j]].lab.unu = root[i].data;
				root[root[i].vecini[j]].lab.doi = root[root[i].vecini[j]].data;
				root[root[i].vecini[j]].lab.cullab = CROSS;
				atr+=3;
			}
			
			if (root[root[i].vecini[j]].cul = ALB) {
				root[root[i].vecini[j]].lab.unu = root[i].data;
				root[root[i].vecini[j]].lab.doi = root[root[i].vecini[j]].data;
				root[root[i].vecini[j]].lab.cullab = TREE;
				atr+=3;
			}
		}
	}
	root[i].cul = NEGRU;
	timp ++;
	root[i].ftime = timp;
	queue.push(root[i].data);
	atr += 3;
}

void DFS() {
	for(int i = 0; i < varfuri; i++) {
		root[i].cul = ALB;
		root[i].pred = -1;
		root[i].data =i ;
		atr += 2;
	}
	timp = 0;
	atr += 1;
	for(int i = 0; i < varfuri; i++) {
		if (root[i].cul == ALB) {
			comp += 1;
			DFS_VISIT(i);
		}
	}
}

void topo() {
	while (queue.size() != NULL) {
		int x;
		x= queue.front();
		printf(" Nod: %d TD: %d TF: %d \n", root[x].data, root[x].dtime, root[x].ftime );
		queue.pop();
	}
}

int main() {

	int selectie;
	printf(" 0- Corman 1- Demonstratie 2-Cerinta 1 3- Cerinta 2\n");
	scanf(" %d ", &selectie);

	switch(selectie) {
	case 0:

		varfuri = 6;
		muchii= 8;

		for(int i = 0; i <= varfuri; i++) {
			root[i].cul = ALB;
			root[i].dist = MAXINT;
			root[i].pred = NULL;
			root[i].data = i;
		}

		//root[].vecini.push_back();
		root[0].vecini.push_back(1);
		root[0].vecini.push_back(2);
		root[1].vecini.push_back(3);
		root[2].vecini.push_back(1);
		root[3].vecini.push_back(2);
		root[4].vecini.push_back(4);
		root[4].vecini.push_back(5);
		root[5].vecini.push_back(5);

		for (int i = 0; i < varfuri; i++) {
			printf("%d: ", i );
	
			for (int j = 0; j < root[i].vecini.size(); j++) {
				printf("%d, ", root[i].vecini[j] );
			}

			printf("\n");
		}

		DFS();

		printf("\n EDGE LABEL \n");
		
		for (int i = 0; i < muchii; i++) {
			char s[10]= "";
			switch (root[i].lab.cullab) {
			case TREE:
				strcpy(s, "TREE");
				break;
			case FORWARD:
				strcpy(s, "FORWARD");
				break;
			case CROSS:
				strcpy(s, "CROSS");
				break;
			case BACK:
				strcpy(s, "BACK");
				break;
			}
			printf(" %d => %d : %s \n", root[i].lab.unu, root[i].lab.doi, s);	
		}

		printf("\n Verificare timpi: \n");
		for (int i = 0; i < varfuri; i++) { 
			printf("\n %d : %d pana la %d \n",root[i].data,root[i].dtime,root[i].ftime);
		}

		printf("\n TOPOLOGIC: \n");
		topo();

		int pauza;
		scanf(" %d ", &pauza);

		break;
	case 1:
		
		varfuri = 10;
		muchii = 9;

		for(int i = 0; i <= varfuri; i++) {
			root[i].cul = ALB;
			root[i].dist = MAXINT;
			root[i].pred = NULL;
			root[i].data = i;
		}

		int vect1[11], vect2[11];
		FillRandomArray(vect1, muchii, 10, varfuri+9, FALSE, 0);
		FillRandomArray(vect2, muchii, 10, varfuri+9, TRUE, 0);

		for (int j = 0; j< muchii;j++) {
			root[vect1[j] - 10].vecini.push_back(vect2[j] - 10);
		}

		for (int i = 0; i < varfuri; i++) {
			printf("%d: ", i );
	
			for (int j = 0; j < root[i].vecini.size(); j++) {
				printf("%d, ", root[i].vecini[j] );
			}

			printf("\n");
		}

		DFS();
		
		for (int i = 0; i < varfuri; i++) {
			char s[10]= "";
			switch (root[i].lab.cullab) {
			case TREE:
				strcpy(s, "TREE");
				break;
			case FORWARD:
				strcpy(s, "FORWARD");
				break;
			case CROSS:
				strcpy(s, "CROSS");
				break;
			case BACK:
				strcpy(s, "BACK");
				break;
			}
			printf(" %d => %d : %s \n", root[i].lab.unu, root[i].lab.doi, s);
		}
		
		pauza;
		scanf(" %d ", &pauza);

		break;
case 2:
		
		varfuri = 100;
		total = 0;
		for(int i = 0; i <= varfuri; i++) {
			root[i].cul = ALB;
			root[i].dist = MAXINT;
			root[i].pred = NULL;
			root[i].data = i;
			root[i].vecini.clear();
		}

		for (int k = 1000; k<= 5000; k = k + 100) {
			
			total += comp + atr;
			comp = 0;
			atr = 0;
			int vect1[5001], vect2[5001];
			
			FillRandomArray(vect1, k , 10, varfuri+9, FALSE, 0);
			FillRandomArray(vect2, varfuri, 10, varfuri+9, TRUE, 0);

			int j;
			j = 0;
			while (j < k) { 
				for (int i = 0; i < varfuri; i++) { 

					//root[vect2[i] - 10].vecini.push_back(vect1[j] - 10);
					j++;
					printf("%d=>%d \n", vect2[i]-10, vect1[j]-10);
				}
			}

			DFS();
			
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

		muchii = 9000;
		total = 0;

		for(int i = 110; i<= 200; i = i + 10 ) {
			
			total += comp + atr;
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

			int l;
			l = 0;
			while (l < 9000) { 
				for (int ll = 0; ll < i; ll++) { 
				root[vect2[ll] - 10].vecini.push_back(vect1[l] - 10);
				l++;
				printf("%d=>%d \n", vect2[ll]-10, vect1[l]-10);
				}
			} 
			
			DFS();

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
	}//switch
return 0; 
}//main