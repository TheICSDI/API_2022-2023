#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define b 'b'
#define r 'r'
#define COST 128

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

pntNodo treeSucc(pntNodo x)
{
	pntNodo y;

	if(x->right != nil)
		return treeMinimum(x->right);

	y = x->p;

	while(y != nil && x == y->right) {
		x = y;
		y = y->p;
	}
	
	return y;
}

pntNodo searchStazione(int x) {
	pntNodo pnt = t->root;

	while(pnt != nil) {
		
		if(pnt->km < x) pnt = pnt->right;
		if(pnt->km > x) pnt = pnt->left;

		if(pnt->km == x) return pnt;
	}
	return nil;
}

void rbDeleteFixup(pntNodo x){
	pntNodo w;

	while (x != t->root && x->color == b) {
		if (x == x->p->left) {
			w = x->p->right;

			if (w->color == r) {
				w->color = b;
				x->p->color = r;
				leftRotate(x->p);
				w = x->p->right;
			}
			if (w->left->color == b && w->right->color == b) {
				w->color = r;
				x = x->p;
			}
			else {
				if (w->right->color == b) {
					w->left->color = b;
					w->color = r;
					rightRotate(w);
					w = x->p->right;
				}
				w->color = x->p->color;
				x->p->color = b;
				w->right->color = b;
				leftRotate(x->p);
				x = t->root;
			}
		}
		else {
			w = x->p->left;

			if (w->color == r) {
				w->color = b;
				x->p->color = r;
				leftRotate(x->p);
				w = x->p->left;
			}
			if (w->right->color == b && w->left->color == b) {
				w->color = r;
				x = x->p;
			}
			else {
				if (w->left->color == b) {
					w->right->color = b;
					w->color = r;
					rightRotate(w);
					w = x->p->left;
				}
				w->color = x->p->color;
				x->p->color = b;
				w->left->color = b;
				leftRotate(x->p);
				x = t->root;
			}
		}
	}
	x->color = b;
}

void deleteStation(pntNodo z) {
	pntNodo x, y;

	if (z->left == nil || z->right == nil)
		y = z;
	else 
		y = treeSucc(z);
	if (y->left != nil) 
		x = y->left;
	else
		x = y->right;

	x->p = y->p;
	if (y->p == nil)
		t->root = x;
	else if (y == y->p->left)
		y->p->left = x;
	else
		y->p->right = x;
	if (y != z)
		z->km = y->km;
	if (y->color == b)
		rbDeleteFixup(x);

	free(y);
}

bool removeCar(pntNodo s, int c) {
	int i;

	for (i = 0; i < s->numCar; i++) {
		if (s->car[i] == c) {
			// Swap with the last element
			s->car[i] = s->car[s->numCar - 1];
			// se c'è un prolema con macchina fanstama togli veramente quella che rimuovi
			s->numCar--;
			return true;
		}
	}
	return false;
}

void inorderTreeWalk(pntNodo x);
void stampaStazione(pntNodo x);

int main()
{
	int i, num_stazione, num, car, new_size;
	bool is_stazione, esiste;
	char tmp;
	pntNodo stazione, rm, tmp_stazione;

	// nodo sentinella NULL
	nil = malloc(sizeof(Nodo));
	nil->color = b;
	nil->p = NULL;
	nil->right = NULL;
	nil->left = NULL;
	nil->numCar = 0;
	nil->km = -1;

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
				while ((tmp = getc_unlocked(stdin)) != '\n') {

					if(is_stazione == true) {
						if (tmp == ' ') {
							is_stazione = false;
							if ((tmp_stazione = searchStazione(num_stazione)) != nil) {
								printf("non aggiunta\n");
								break;
							}
							else {
								//printf("aggiunta stazione num = %d\n", num_stazione);
								printf("aggiunta\n");
								stazione = malloc(sizeof(Nodo));
								stazione->km = num_stazione;
								// array car è grande COST
								stazione->car = calloc(COST, sizeof(int));
								stazione->numCar = 0;
								rbInsert(stazione);
							}
						}
						else num_stazione = num_stazione * 10 + (tmp - '0');
					}
					else {
						if (tmp == ' ') {
							if (stazione->numCar % COST == 0) {
								new_size = stazione->numCar + COST;
								stazione->car = realloc(stazione->car, new_size * sizeof(int));
							}
							stazione->car[stazione->numCar] = car;
							stazione->numCar++;
							car = 0;
						}
						else {
							car = car * 10 + (tmp - '0');
						}
					}
				}
				// stampaStazione(stazione);
			}
			// caso aggiungi-auto
			else if(tmp == 'a'){
				// scorre fino alla fine del comando
				while((tmp = getc_unlocked(stdin)) != ' ');

				is_stazione = true;
				num_stazione = 0;
				esiste = true;
				car = 0;
				while((tmp = getc_unlocked(stdin)) != '\n' && esiste == true) {

					if(is_stazione == true) {
						if (tmp == ' ') {
							is_stazione = false;
							if ((tmp_stazione = searchStazione(num_stazione)) == nil) {
								//printf("stazione) non aggiunta\n");
								printf("non aggiunta\n");
								esiste = false;
							}
						}
						else num_stazione = num_stazione * 10 + (tmp - '0');
					}
					else car = car * 10 + (tmp - '0');
				}
				if (esiste == true) {
					if (stazione->numCar % COST == 0) {
						new_size = stazione->numCar + COST;
						stazione->car = realloc(stazione->car, new_size * sizeof(int));
					}
					stazione->car[stazione->numCar] = car;
					stazione->numCar++;
					printf("aggiunta\n");
				}
			}
		}
		// rottama
		else if (tmp == 'r'){
			// scorre fino alla fine del comando
			while((tmp = getc_unlocked(stdin)) != ' ');

			is_stazione = true;
			num_stazione = 0;
			esiste = true;
			car = 0;
			while((tmp = getc_unlocked(stdin)) != '\n' && esiste == true) {

				if(is_stazione == true) {
					if (tmp == ' ') {
						is_stazione = false;
						if ((tmp_stazione = searchStazione(num_stazione)) == nil) {
							//printf("stazione) non rottamata\n");
							printf("non rottamata\n");
							esiste = false;
							//printf("esiste = %s\n", esiste ? "true" : "false");
						}
					}
					else num_stazione = num_stazione * 10 + (tmp - '0');
				}
				else car = car * 10 + (tmp - '0');
			}

			if (esiste == true) { 
				if (removeCar(tmp_stazione, car) == true)
					printf("rottamata\n");

				else 
				//printf("auto) non rottamata\n");
				printf("non rottamata\n");
			}
		}
		// demolisci
		else if (tmp == 'd') {
			// scorre fino alla fine del comando
			while((tmp = getc_unlocked(stdin)) != ' ');

			num_stazione = 0;
			while((tmp = getc_unlocked(stdin)) != '\n') {

				num_stazione = num_stazione * 10 + (tmp - '0');
			}
			rm = searchStazione(num_stazione);
			if (rm == nil) printf("non demolita\n");
			else {
				deleteStation(rm);
				printf("demolita\n");
			}
		}
		// pianifica
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
// DEBUG
void stampaStazione(pntNodo x){

	int i;

	printf("numero stazione aggiunta al kilometro %d.\ncon le macchine:\t", x->km);
	for(i = 0; i < x->numCar; i++) {
		printf("%d ", x->car[i]);
	}
	putchar_unlocked('\n');
}

void inorderTreeWalk(pntNodo x) {
	if(x != nil){
		inorderTreeWalk(x->left);
		printf("%d\t", x->km);
		inorderTreeWalk(x->right);
	}
}
