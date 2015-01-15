#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "Profiler.h"

Profiler profiler("profiler");

int varfuri, muchii;

typedef struct Nod {
	int data;
	struct Nod *parinte;
	int rank;
};

struct Nod* make_set(int x) {
	struct Nod *nod_curent = (struct Nod *)malloc(sizeof(struct Nod));
	nod_curent->data = x;
	nod_curent->rank = 0;
	nod_curent->parinte = nod_curent;
	profiler.countOperation(" Atribuiri", muchii);
	return nod_curent;
}

struct Nod *find_set(Nod *x) {
	profiler.countOperation(" Comparatii", muchii);
	if (x != x->parinte) {
		profiler.countOperation(" Atribuiri", muchii);
		x->parinte = find_set(x->parinte);
	}
	return x->parinte;
}

void link(Nod *x, Nod *y)
	{
		profiler.countOperation(" Comparatii", muchii);
		if( x->rank > y->rank ) {
			y->parinte = x;
			profiler.countOperation(" Atribuiri", muchii);

		}
		else {
			x->parinte = y;
			profiler.countOperation(" Atribuiri", muchii);
			profiler.countOperation(" Comparatii", muchii);
			if( x->rank == y->rank ) {
				y->rank = y->rank+1;
				profiler.countOperation(" Atribuiri", muchii);
			}
		}
}

void union_set(Nod *x, Nod *y) {
		link(find_set(x), find_set(y));
}

int main() {

	int selectie;
	
	printf(" 1- Demonstratie 2- Multimi Disjuncte \n");
	scanf(" %d ", &selectie);
	
	switch(selectie) { 
		case 1:
			varfuri = 9;
			int vect[10][10],i,j;

			for(i=1;i <= varfuri ;i++)
				for(j=1; j<= varfuri; j++)
					vect[i][j]=0;
			
			struct Nod **root;
			root = (struct Nod **)malloc(9*sizeof(struct Nod));

			vect[1][5]=1;	vect[1][4]=1;
			vect[5][1]=1;	vect[4][1]=1;
			
			vect[3][4]=1;	vect[4][8]=1;
			vect[4][3]=1;	vect[8][4]=1;
			
			vect[6][8]=1;	vect[2][3]=1;
			vect[8][6]=1;	vect[3][2]=1;
			vect[5][7] =1;  vect[7][5] =1;
			//for (i =0; i<12; i++) { muchii ++;}

			for(i=1; i<= varfuri;i++) {
				root[i] = make_set(i);	
			}

			for(i=1; i<= varfuri;i++)
				for(j=1;j <= varfuri;j++)
					if(vect[i][j]==1)
						union_set(root[i],root[j]);
			
			int contorMultimi;
			contorMultimi = 0;

			for(i=1; i<= varfuri;i++)
				if(root[i] == find_set(root[i]) ) {
					contorMultimi++;
					printf("Multimea %d : ", contorMultimi);
					for(j=1;j<= varfuri;j++)
						if(find_set(root[j]) != root[i])
							printf("%d  ",root[j]->data);
					printf(" \n");
				}


			for (int i = 1; i <= varfuri; i++) { 
				printf(" Data:%d: Parinte:%d: Rank:%d\n", root[i]->data,root[i]->parinte->data, root[i]->rank);
			}

			int pauza;
			scanf(" %d ", &pauza);
			profiler.createGroup("Total" ,"Atribuiri" ,"Comparatii");
			profiler.showReport();
			break;
		case 2:
			varfuri = 10000;
			int **vect2;
			vect2 = (int **)malloc(10100*sizeof(int*));
			int vf1,vf2,z;
			struct Nod **root2;
			
			for(z=0;z<10100;z++)
				vect2[z]=(int *)malloc(10100*sizeof(int));

			root2 = (struct Nod **)malloc(10000*sizeof(struct Nod));
			for (muchii = 10000; muchii <= 60000; muchii =  muchii+ 100) {

				for (varfuri = 1; varfuri <=10000; varfuri++){
					vf1 = rand()%10000;
					vf2 = rand()%10000;
					/**if ((vf1 == vf2) && (vf1 !=0) &&(vf2 !=0) && (vect2[vf1][vf2] !=1)) {
						do {
							vf1 = rand()%10000;
							vf2 = rand()%10000;
						}	while(vf1 == vf2);
					}**/
					vect2[vf1][vf2] = 1;
					vect2[vf2][vf1] = 1;
					printf("%d => %d \n", vf1,vf2);
				}
				
			}

			for(i=1; i<= varfuri;i++) {
				root2[i] = make_set(i);	
			}
			
			for(i=1; i<= varfuri;i++)
				for(j= 1;j <= varfuri;j++)
					if(vect2[i][j]==1)
						union_set(root2[i],root2[j]);
			
			int pauza2;
			scanf(" %d ", &pauza2);
			profiler.createGroup("Atribuiri" ,"Comparatii");
			profiler.showReport();
			break;
		default:
			printf(" Optiune invalida! \n");
			break;
			
	}//switch
	//getchar();
	return 0;
}//main