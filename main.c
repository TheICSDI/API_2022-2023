#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define b 'b'
#define r 'r'
#define COST 64

typedef struct RB {
	int km;
	int *car;
	int numCar;
	char color;
	struct RB *right;
	struct RB *left;
	struct RB *p;} Nodo, *pntNodo;    // struttura dati nodo

typedef struct tr {
	pntNodo root;} tree, *pntTree; // struttura dati testa

// variabili globali
pntNodo nil;              // per fare solo una malloc
pntTree t;                // solo una albero con ogni stazione

void inorderTreeWalk(pntNodo x) {
	// debug
	if(x != nil){
		inorderTreeWalk(x->left);
		printf("%d\t", x->km);
		inorderTreeWalk(x->right);
	}
}

void leftRotate(pntNodo x) {
	pntNodo y = x->right;

	x->right = y->left;         //il sotto albero sinisrto di y
								//divenda quello destro di x
	if(y->left != nil)
		y->left->p = x;

	y->p = x->p;                //attacca il padre di x a y
	if(x->p == nil)
		t->root = y;

	else if(x == x->p->left)
		x->p->left = y;

	else
		x->p->right = y;

	y->left = x;
	x->p = y;
}

void rightRotate(pntNodo x) {
	pntNodo y = x->left;

	x->left = y->right;    //il sotto albero sinisrto di y
						   //divenda quello destro di x
	if(y->right != nil)
		y->right->p = x;

	y->p = x->p;
	if(x->p == nil)
		t->root = y;

	else if(x == x->p->right)
		x->p->right = y;

	else
		x->p->left = y;

	y->right = x;
	x->p = y;
}

void rbInsertFixUp(pntNodo z) {
	pntNodo x, y;

	if(z == t->root)
		t->root->color = b;

	else{
		x = z->p;
		if(x->color == r){
			if(x == x->p->left){
				y = x->p->right;

				if(y->color == r){
					x->color = b;
					y->color = b;
					x->p->color = r;

					rbInsertFixUp(x->p);
				}
				else{
					if(z == x->right){
						z = x;
						leftRotate(z);
						x = z->p;
					}
					x->color = b;
					x->p->color = r;
					rightRotate(x->p);
				}
			}
			else{
				y = x->p->left;

				if(y->color == r){
					x->color = b;
					y->color = b;
					x->p->color = r;

					rbInsertFixUp(x->p);
				}
				else{
					if(z == x->left){
						z = x;
						rightRotate(z);
						x = z->p;
					}
					x->color = b;
					x->p->color = r;
					leftRotate(x->p);
				}
			}
		}
	}
}

void rbInsert(pntNodo z) {
	pntNodo y = nil, x = t->root;

	while(x != nil){
		y = x;

		if(z->km < x->km)
			x = x->left;

		else		
			x = x->right;
	}
	z->p = y;

	if(y == nil)   //caso in cui l'albero t è vuoto       
		t->root = z;

	else if(z->km < y->km)
		y->left = z;

	else
		y->right = z;

	z->left = nil;
	z->right = nil;
	z->color = r;
	rbInsertFixUp(z);
}

pntNodo treeMinimum(pntNodo x) {
	while(x->left != nil)
		x = x->left;

	return x;
}

pntNodo treeMax(pntNodo x) {
	while(x->right != nil)
		x = x->right;

	return x;
}

void stampaStazione(pntNodo x);

int main()
{
	int i, num_stazione, num, car;
	bool is_stazione;
	char tmp;
	pntNodo stazione;

	// nodo sentinella NULL
	nil = malloc(sizeof(Nodo));
	nil->color = b;
	nil->p = NULL;
	nil->right = NULL;
	nil->left = NULL;

	// nodo testa dell'albero
	t = malloc(sizeof(tree));
	t->root = nil;
	
	while((tmp = getc_unlocked(stdin)) != EOF)
	{
		// aggiungi
		if(tmp == 'a'){
			// scorre la parola fino a -
			while((tmp = getc_unlocked(stdin)) != '-');
			// caso aggiungi-stazione
			if((tmp = getc_unlocked(stdin)) == 's'){
			 
				// scorre fino alla fine del comando
				while((tmp = getc_unlocked(stdin)) != ' ');

				// t = malloc(sizeof(tree));
				num_stazione = 0;
				is_stazione = true;
				car = 0;
				for (i = 0; (tmp = getc_unlocked(stdin)) != '\n'; i++) {

					if(is_stazione == true) {
						if (tmp == ' ') {
							is_stazione = false;
							stazione = malloc(sizeof(Nodo));
							stazione->km = num_stazione;
							// array car è grande COST
							stazione->car = calloc(COST, sizeof(int));
							stazione->numCar = 0;
							rbInsert(stazione);
						}
						else num_stazione = num_stazione * 10 + (tmp - '0');
					}
					else {
						if (tmp == ' ') {
							stazione->car[stazione->numCar] = car;
							stazione->numCar++;
							car = 0;
						}
						else {
							car = car * 10 + (tmp - '0');
						}
					}
				}
				stampaStazione(stazione);
			}
			// caso aggiungi-auto
			else if(tmp == 'a'){
				// scorre fino alla fine del comando
				while((tmp = getc_unlocked(stdin)) != ' ');
				// va gestitio la lettura degli interi
				printf("lettura aggiungi-auto e non so ancora cosa fare\n");
				while((tmp = getc_unlocked(stdin)) != '\n');
			}
		}
		// rottama
		else if (tmp == 'r'){
			// scorre fino alla fine del comando
			while((tmp = getc_unlocked(stdin)) != ' ');
			// va gestitio la lettura degli interi
			printf("lettura rottama-auto e non so ancora cosa fare\n");
			while((tmp = getc_unlocked(stdin)) != '\n');
		}
		else if (tmp == 'd') {
			// scorre fino alla fine del comando
			while((tmp = getc_unlocked(stdin)) != ' ');
			// va gestitio la lettura degli interi
			printf("lettura demolisci-stazione e non so ancora cosa fare\n");
			while((tmp = getc_unlocked(stdin)) != '\n');
		}
		else if (tmp == 'p') {
			// scorre fino alla fine del comando
			while((tmp = getc_unlocked(stdin)) != ' ');
			// va gestitio la lettura degli interi
			printf("lettura pianifica-percorso e non so ancora cosa fare\n");
			while((tmp = getc_unlocked(stdin)) != '\n');
		}
	}
	inorderTreeWalk(t->root);
	return 0;
}

void stampaStazione(pntNodo x){

	int i;

	printf("numero stazione aggiunta al kilometro %d, con le macchine:\n\t", x->km);
	for(i = 0; i < x->numCar; i++) {
		printf("%d ", x->car[i]);
	}
	printf("\ncon un numero tale di macchine = %d\n", x->numCar);
}
