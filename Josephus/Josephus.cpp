/*
Indre Ionut
Josephus
*/

#include <stdio.h>
#include <stdlib.h>
#include "Profiler.h"
Profiler profiler("demo");

int n, m;

typedef struct node {
	int data, size;
	node *left; 
	node *right; 
	node *parent;
} Tree;

Tree *build(int first, int last) {

	profiler.countOperation("Comparatii", n);
	if(first <= last) {
		Tree *root = (Tree*)malloc(sizeof(Tree));
		root -> parent = NULL; 
		root->size=last-first+1;
		root->data = (last+first)/2;
		
		//Construiesc si setez parintele - stanga
		root->left = build(first,(first+last)/2-1);
		
		profiler.countOperation("Comparatii", n);
		if ( root -> left != NULL ) {
			root -> left -> parent = root;
			profiler.countOperation("Atribuiri", n);
		}
			
		//Construiesc si setez parintele - dreapta
		root->right = build((first+last)/2+1, last);
		
		profiler.countOperation("Comparatii", n);
		if ( root -> right != NULL ) {
			root -> right -> parent = root;
			profiler.countOperation("Atribuiri", n);
		}

		return root;
	}
	return NULL;
}

void prettyPrint( Tree *root, int level ) {
	if ( root != NULL ) {
		prettyPrint( root -> right, level+1 );
		for (int i = 0; i<level; i++)
			printf("   ");
		printf("%d - %d\n", root -> data, root->size );
		prettyPrint( root -> left, level+1 );
	}
}

Tree *osSelect ( Tree *x, int i ) {
	int r;

	profiler.countOperation("Comparatii", n);
	if ( x -> left == NULL ) {
		r = 1; 
     	profiler.countOperation("Atribuiri", n);

	} 
	else {
	r = x -> left -> size+1;
	profiler.countOperation("Atribuiri", n);

	}

	profiler.countOperation("Comparatii", n);
	if ( i == r )
		 return x;
	else if (i < r ) 
			return osSelect(x->left, i);
		 else return osSelect(x->right, i-r);
	profiler.countOperation("Comparatii", n);

}

Tree  *findTreeMin(Tree *x) {
	
	profiler.countOperation("Comparatii", n);
	while ( x -> left != NULL ) {
		x = x -> left;
		profiler.countOperation("Atribuiri", n);

	}
	return x;
}

Tree *findTreeSuccessor( Tree *x ) {
	Tree *y = new Tree;
	
	profiler.countOperation("Comparatii", n);
	if ( x -> right != NULL ) {
		return findTreeMin( x -> right );
		profiler.countOperation("Atribuiri", n);
		y = x -> parent;
	}
	while ( y != NULL &&  x == y ->right ) {
		x = y; 
		y = y -> parent;
		profiler.countOperation("Comparatii", n);
		profiler.countOperation("Atribuiri", n, 2);

	}
	return y;
}

void deleteNode ( Tree *root, Tree *z ) {
	Tree *y = new Tree;
	Tree *x = new Tree;
	profiler.countOperation("Comparatii", n);
	if ( z -> left == NULL || z -> right == NULL ) {
		y = z;
		profiler.countOperation("Atribuiri", n);
	}
	else {
		y = findTreeSuccessor(z); 
		profiler.countOperation("Atribuiri", n);
	}
	profiler.countOperation("Comparatii", n);
	if ( y -> left != NULL ) {
		profiler.countOperation("Atribuiri", n);
		x = y -> left;
	}
	else x = y -> right; 
	if ( x != NULL )          
		x -> parent = y -> parent;
	profiler.countOperation("Comparatii", n, 2);
	if ( y -> parent == NULL ) {
		profiler.countOperation("Atribuiri", n);
		root = x; 
	}
	//profiler.countOperation("Comparatii", n);
	else if ( y == y -> parent -> left ) {
			y -> parent -> left = x;
			profiler.countOperation("Atribuiri", n);
		 }
		 else {
			y -> parent -> right = x;
			profiler.countOperation("Atribuiri", n);
		 }
	z -> data = y -> data;
	while(z!=NULL) {
		z->size--;
		z=z->parent;
		profiler.countOperation("Comparatii", n);
		profiler.countOperation("Atribuiri", n);
	}
	free (y);
}

void Josephus(int n, int m) {
	Tree *x;
	Tree *root = build(1, n);
	int j = 1;

	for(int k=n;k>0;k--) {
		j=((j+m-2) % k)+1;
		x=osSelect(root,j);
		printf("%d ",x->data);
		deleteNode(root,x);
	}
}

void JosephusPrint(int n, int m) {
	Tree *x;
	Tree *root = build(1, n);
	int j = 1;
	printf("Demo n=7 m=3 inainte de stergeri. \n");
	prettyPrint(root,0);
	printf("############ \n Dupa stergere \n");
	for(int k=(n-1);k>0;k--) {
		j=((j+m-2) % k)+1;
		x=osSelect(root,j);
		printf("Stergem %d  \n \n",x->data);
		deleteNode(root,x);
		prettyPrint(root,0);
	}
}

int main () {

	int selectie;
	
	printf("1- Demonstratie 2- Josephus \n");
	scanf("%d", &selectie);

	switch(selectie) {
	case 1: {
		n = 7;
		m = 3;
		Josephus(n,m);
		getchar();
		}
	break;
	case 2: {
		n = 11;
		m = 5;
		JosephusPrint(n,m);
		/*
		for (int i = 11; i<=10000; i++) {
			n = i;
			m = n/2;
			JosephusPrint(n,m);
		}
				
		for (int i = 11; i<=10000; i++) {
			n = i;
			m = n/2;
			Josephus(n,m);
		}
		*/
		getchar();
	}
	break;

	default:
		printf("Selectie invalida! \n");
		break;
	} // switch

	profiler.showReport();
	getchar();
	return 0;
}