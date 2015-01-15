/**
	Ionut Indre
**/

#include <stdio.h>
#include <stdlib.h>
#include <vector>

#define sizeVect 10


//Definire pentru varinata intai.
typedef struct Nod {
	int val; 
	std::vector<Nod> copii;
};

typedef struct node {
	int data;
	node *left; 
	node *right;
} Tree;

/*
void prettyPrint( node *root, int level ) {
	if ( root != NULL ) {
		prettyPrint( root -> right, level+1 );
		for (int i = 0; i < level; i++)
			printf("   ");
		printf("%d \n", root -> data);
		prettyPrint( root -> left, level+1 );
	}
}
*/

// Un arbore multi cai de ordin n are n-1 valori si n copii.
int main() {
	  	
    int selectie;
	printf("1- Varianta 1 2- Varinata 2 \n");
	scanf("%d", &selectie);

	switch(selectie){
		case 1: {
			
			int vect[sizeVect];
			// 9 elemente
			vect[1]=2;
			vect[2]=7;
			vect[3]=5;
			vect[4]=2;
			vect[5]=7;
			vect[6]=7;
			vect[7]=-1;
			vect[8]=5;
			vect[9]=2;
			//R1:
			for (int i = 1; i < sizeVect; i++) {
				printf("P:%d - C: %d \n", vect[i], i);
			}

			
			int vect2[sizeVect];
			vect2[1]=2;
			vect2[2]=7;
			vect2[3]=5;
			vect2[4]=2;
			vect2[5]=7;
			vect2[6]=7;
			vect2[7]=-1;
			vect2[8]=5;
			vect2[9]=2;

			int j = 1;
			int min = 999;
			while (j <  sizeVect) {
				min = 999;
				int poz = 1;
				for (int i = 1; i < sizeVect; i++) {
					if (vect2[i] < min) {
						poz = i;
						min =  vect2[poz];
					}
				}
				printf("%d \n", poz);
				vect2[poz] = 1000;
				j++;
			}

			Nod vectNod[sizeVect];

			for (int i = 1; i < sizeVect; i++) {
				vectNod[i].val = i;
			}
			
			for (int i = 0; i < sizeVect; i++) {
				if ( vect[i] > 0 ) {
					vectNod[vect[i]].copii.push_back(vectNod[i]);
				}
			}

			//R2:
			
			printf("\n Noduri \t Copii");
			for (int i = 0; i < sizeVect; i++) {
				if (vectNod[i].copii.size() > 0 || vectNod[i].val > 0) {
					printf("%d: \n",i);
				}
				for (int j = 0; j < vectNod[i].copii.size(); j++) {
					printf("\t");
					printf("%d : %d \n", j, vectNod[i].copii.at(j) );
				}
				printf("\n");
			}

			/*
			int aux = 1;
			int i = 1;
			while (i < sizeVect)
				if (vect[i] < 0) aux = i;
			printf("%d \n", vectNod[aux].val);
			printf("\t");
			for (int j = 0; j < vectNod[aux].copii.size(); j++) {
					printf("%d \n", vectNod[i].copii.at(j) );
					for (int k = 0;k<vectNod[vectNod[i].copii.at(j)].copii.size() ;k++)
											printf("%d \n", vectNod[j].copii.at(k) );

				}
			*/
			
			getchar();
			int test;
			scanf("%d", &test);
			return 0;
		} //case 1
		break;
		
		case 2: {
			
		}//case 2
		break;
		
		default:
			printf("Selectie invalida! \n");
		break;
	}//switch 1  
}//main