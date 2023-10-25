#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define b 'b'
#define r 'r'
#define INF 999999999
#define COST 128

/*    node data structured    */
typedef struct RB {
	int km;
	int *car;
	int numCar;
	char color;
	struct RB *right;
	struct RB *left;
	struct RB *p;} Nodo, *pntNodo;

/*    tree root data structured    */
typedef struct tr {
	pntNodo root;} tree, *pntTree;

/*    simpler node for Dijkstra alg    */
typedef struct dst {
	int station;
	int numStation;
	int maxCar;
	bool seen;
	int prec;} dist;


/*     global variable     */
pntNodo nil;                // only null node for minimize the number of calls for malloc
pntTree t;                  // the only root

/*     DEBUG     */
void inorderTreeWalk(pntNodo x);
void stampaStazione(pntNodo x);

void leftRotate(pntNodo x) {
	pntNodo y = x->right;

	x->right = y->left;         // switch the y's left sub-tree with the x's right one

	if(y->left != nil)
		y->left->p = x;

	y->p = x->p;                // connect x's father to y
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

	x->left = y->right;    // switch the y's left sub-tree with the x's right one

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
	pntNodo y;

	while (z->p->color == r) {
		if (z->p == z->p->p->left) {
			y = z->p->p->right;

			if (y->color == r) {
				// Case 1
				z->p->color = b;
				y->color = b;
				z->p->p->color = r;
				z = z->p->p;
			} else if (z == z->p->right) {
				// Case 2
				z = z->p;
				leftRotate(z);
			} else {
				// Case 3
				z->p->color = b;
				z->p->p->color = r;
				rightRotate(z->p->p);
			}
		} else {
			y = z->p->p->left;

			if (y->color == r) {
				// Case 1
				z->p->color = b;
				y->color = b;
				z->p->p->color = r;
				z = z->p->p;
			} else if (z == z->p->left) {
				// Case 2
				z = z->p;
				rightRotate(z);
			} else {
				// Case 3
				z->p->color = b;
				z->p->p->color = r;
				leftRotate(z->p->p);
			}
		}
	}
	t->root->color = b;
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

	if(y == nil)   // case where t is an empty tree
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

pntNodo treePrecc(pntNodo x)
{
	pntNodo y;

	if(x->left != nil)
		return treeMax(x->left);

	y = x->p;

	while(y != nil && x == y->left) {
		x = y;
		y = y->p;
	}
	
	return y;
}

void rbDeleteFixup(pntNodo x){
	pntNodo w = nil;

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
			else if (w->right->color == b) {
				w->left->color = b;
				w->color = r;
				rightRotate(w);
				w = x->p->right;
			}
			else {
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
				rightRotate(x->p);
				w = x->p->left;
			}
			if (w->right->color == b && w->left->color == b) {
				w->color = r;
				x = x->p;
			}
			else if (w->left->color == b) {
				w->right->color = b;
				w->color = r;
				leftRotate(w);
				w = x->p->left;
			}
			else {
				w->color = x->p->color;
				x->p->color = b;
				w->left->color = b;
				rightRotate(x->p);
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
	if (y != z) {
		z->km = y->km;
		free(z->car);       // Free the existing car array of z
		z->car = y->car;
		y->car = NULL;      // Set y's car pointer to NULL
		z->numCar = y->numCar;
	}
	if (y->color == b)
		rbDeleteFixup(x);

	if(y->car != NULL)
		free(y->car);
	free(y);
}

/*  traverses the tree for the correct node from its km */
pntNodo searchStazione(int x) {
	pntNodo pnt = t->root;

	while(pnt != nil) {
		
		if(pnt->km < x) pnt = pnt->right;
		else if(pnt->km > x) pnt = pnt->left;

		else return pnt;
	}
	return nil;
}

/*  Add a car in the node sub-array with the policy of car[0] = max(car[])  */
void addCar(pntNodo s, int car){
	int new_size;

	if (s->numCar % COST == 0) {
		new_size = s->numCar + COST;
		s->car = realloc(s->car, new_size * sizeof(int));
	}
	if (s->car[0] > car)
		s->car[s->numCar] = car;    // move the ex-max car to last position
	else {
		s->car[s->numCar] = s->car[0];
		s->car[0] = car;
	}
	s->numCar++;
}

/*  Remove a car in the node sub-array with the policy of car[0] = max(car[])  */
bool removeCar(pntNodo s, int c) {
	int i;

	for (i = 0; i < s->numCar; i++) {
		if (s->car[i] == c) {
			if (i != 0) {
				// Swap with the last element
				s->car[i] = s->car[s->numCar - 1];
				s->car[s->numCar - 1] = 0;
				s->numCar--;
				return true;
			}
			else { 
				int j, i_max;
				for (j = 2, i_max = 1; j < s->numCar; j++){
					if (s->car[i_max] < s->car[j]) i_max = j;
				}
				s->car[0] = s->car[i_max];
				s->car[i_max] = s->car[s->numCar - 1];
				s->car[s->numCar - 1] = 0;
				s->numCar--;
				return true;
			}
		}
	}
	return false;
}

/*  Check if station x is adjacent to station y  Forward  */
bool isXAdjYFW(dist x, dist y) {
    if (y.station < x.station && y.station + y.maxCar >= x.station) return true;

    return false;
}

/*  A queueless implementation of Dijkstra algorithm Forward (start < finish) */
void planRouteFW(int start, int finish) {
    pntNodo s_start = searchStazione(start), curr;
    int i, size = 0, j, minIndex;
	bool okay = true;

	/*  Count all the possible station between start and finish  */
    curr = s_start;
    while(okay == true){
		if (curr->km == finish) okay = false;
        size++;
        curr = treeSucc(curr);
    }

    dist result[size];

	/* Initialize the elements of the array with only the station counted before  */
    for (i = 0, curr = s_start; i < size; i++, curr = treeSucc(curr)) {
        result[i].station = curr->km;
        result[i].maxCar = curr->car[0];
        result[i].numStation = (i == 0) ? 0 : INF;
        result[i].prec = INF;
        result[i].seen = false;
    }

	/* Actual search */
    for (i = 0; i < size; i++) {
        /* Find the node with the minimum distance */
        minIndex = -1;
        for (j = 0; j < size; j++) {
            if (!result[j].seen && (minIndex == -1 || result[j].numStation < result[minIndex].numStation)) {
                minIndex = j;
            }
        }

		/* All nodes have been visited */
        if (minIndex == -1) {
            break;
        }

        result[minIndex].seen = true;

		/* Update distances for all adjacent nodes */
		for (j = 0; j < size; j++) {
			if (!result[j].seen && isXAdjYFW(result[j], result[minIndex]) 
					&& result[minIndex].numStation + 1 < result[j].numStation) {

				result[j].numStation = result[minIndex].numStation + 1;
				result[j].prec = minIndex;
			}
		}
    }
	/* Print the shortest path */
	i = size - 1;
	if (result[i].numStation >= INF) {
		printf("nessun percorso\n");
	} 
	else {
		int stack[size];
		int top = -1;   // top of stack

		/* Push the path onto the stack */
		while(i != 0 && i != INF){
			stack[++top] = result[i].station;
			i = result[i].prec;
		}
		stack[++top] = result[0].station;

		/* Print the path in the correct order */
		while(top != -1) {
			printf("%d", stack[top--]);
			if(top != -1) {
				printf(" ");
			}
		}
		printf("\n");
	}
}

/*  Check if station x is adjacent to station y  BackWards  */
bool isXAdjYBW(dist x, dist y) {
    if (y.station > x.station && y.station - y.maxCar <= x.station) return true;

    return false;
}

/*  A queueless implementation of Dijkstra algorithm Forward (start > finish) */
void planRouteBW(int start, int finish) {
    pntNodo s_start = searchStazione(start), curr;
    int i, size = 0, j, minIndex;
	bool okay = true;

	/*  Count all the possible station between start and finish  */
    curr = s_start;
    while(okay == true){
		if (curr->km == finish) okay = false;
        size++;
        curr = treePrecc(curr);
    }

    dist result[size];

	/* Initialize the elements of the array with only the station counted before  */
    for (i = 0, curr = s_start; i < size; i++, curr = treePrecc(curr)) {
        result[i].station = curr->km;
        result[i].maxCar = curr->car[0];
        result[i].numStation = (i == 0) ? 0 : INF; // Initialize distances
        result[i].prec = INF;
        result[i].seen = false;
    }

	/* Actual search */
    for (i = 0; i < size; i++) {
        /* Find the node with the minimum distance with also the farthest from the start of the highway */
        minIndex = -1;
        for (j = 0; j < size; j++) {
            if (!result[j].seen 
					&& ((minIndex == -1 || result[j].numStation < result[minIndex].numStation)
					|| (minIndex != -1 && result[j].numStation == result[minIndex].numStation && result[j].station < result[minIndex].station))) {
                minIndex = j;
            }
        }

		/* All nodes have been visited */
        if (minIndex == -1) {
            break;
        }

        result[minIndex].seen = true;

		/* Update distances for all adjacent nodes */
		for (j = 0; j < size; j++) {
			if (!result[j].seen && isXAdjYBW(result[j], result[minIndex]) 
					&& result[minIndex].numStation + 1 < result[j].numStation) {

				result[j].numStation = result[minIndex].numStation + 1;
				result[j].prec = minIndex;
			}
		}
    }
	/* Print the shortest path */
	i = size - 1;
	if (result[i].numStation >= INF) {
		printf("nessun percorso\n");
	} else {
		int stack[size];
		int top = -1;   // top of stack

		/* Push the path onto the stack */
		while(i != 0 && i != INF){
			stack[++top] = result[i].station;
			i = result[i].prec;
		}
		stack[++top] = result[0].station;

		/* Print the path in the correct order */
		while(top != -1) {
			printf("%d", stack[top--]);
			if(top != -1) {
				printf(" ");
			}
		}
		printf("\n");
	}
}

int main()
{
	int num_stazione, car, start, finish;
	bool is_stazione, esiste, prima;
	char tmp;
	pntNodo stazione = nil, rm;

	// nodo sentinella NULL
	nil = malloc(sizeof(Nodo));
	nil->color = b;
	nil->p = NULL;
	nil->right = NULL;
	nil->left = NULL;
	nil->numCar = -1;
	nil->km = -1;

	/* root of the tree */
	t = malloc(sizeof(tree));
	t->root = nil;
	
	while((tmp = getc_unlocked(stdin)) != EOF)
	{
		/* case 'aggiungi' */
		if(tmp == 'a'){
			/* roll the input up to '-' */
			while((tmp = getc_unlocked(stdin)) != '-');
			/* case 'aggiungi-stazione' */
			if((tmp = getc_unlocked(stdin)) == 's'){
			 
				/* roll the input up to the end of the command */
				while((tmp = getc_unlocked(stdin)) != ' ');

				num_stazione = 0;
				is_stazione = true;
				car = 0;
				esiste = true;
				while ((tmp = getc_unlocked(stdin)) != '\n') {

					if(is_stazione == true) {
						if (tmp == ' ') {
							is_stazione = false;

							/* check if a station already exists */
							if ((stazione = searchStazione(num_stazione)) != nil) {
								esiste = false; // allora quella corrente che avrei creato non esiste
								printf("non aggiunta\n");
								break;
							}
							else {
								stazione = malloc(sizeof(Nodo));
								stazione->km = num_stazione;
								stazione->car = calloc(COST, sizeof(int));
								stazione->numCar = 0;
								rbInsert(stazione);
								prima = true;
								printf("aggiunta\n");
							}
						}
						else num_stazione = num_stazione * 10 + (tmp - '0');
					}
					else {
						if (tmp == ' ') {
							if(prima == true) prima = false;
							else
								addCar(stazione, car);
							car = 0;
						}
						else {
							car = car * 10 + (tmp - '0');
						}
					}
				}
				if (esiste == true)
					addCar(stazione, car);
			}
			/* case 'aggiungi-auto' */
			else if(tmp == 'a'){
				/* roll the input up to the end of the command */
				while((tmp = getc_unlocked(stdin)) != ' ');

				is_stazione = true;
				num_stazione = 0;
				esiste = true;
				car = 0;
				while((tmp = getc_unlocked(stdin)) != '\n') {

					if(is_stazione == true) {
						if (tmp == ' ') {
							is_stazione = false;
							if ((stazione = searchStazione(num_stazione)) == nil) {
								printf("non aggiunta\n");
								esiste = false;
							}
						}
						else num_stazione = num_stazione * 10 + (tmp - '0');
					}
					else car = car * 10 + (tmp - '0');
				}
				if (esiste == true) {
					addCar(stazione, car);
					car = 0;
					printf("aggiunta\n");
				}
			}
		}
		/* case 'rottama' */
		else if (tmp == 'r'){
			/* roll the input up to the end of the command */
			while((tmp = getc_unlocked(stdin)) != ' ');

			is_stazione = true;
			num_stazione = 0;
			esiste = true;
			car = 0;
			while((tmp = getc_unlocked(stdin)) != '\n') {

				if(is_stazione == true) {
					if (tmp == ' ') {
						is_stazione = false;

						if ((stazione = searchStazione(num_stazione)) == nil) {
							printf("non rottamata\n");
							esiste = false;
						}
					}
					else num_stazione = num_stazione * 10 + (tmp - '0');
				}
				else car = car * 10 + (tmp - '0');
			}

			if (esiste == true) { 
				if (removeCar(stazione, car) == true)
					printf("rottamata\n");

				else
				printf("non rottamata\n");
			}
		}
		/* case 'demolisci' */
		else if (tmp == 'd') {
			/* roll the input up to the end of the command */
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
		/* case 'pianifica' */
		else if (tmp == 'p') {
			/* roll the input up to the end of the command */
			while((tmp = getc_unlocked(stdin)) != ' ');
			start = 0;
			while((tmp = getc_unlocked(stdin)) != ' '){
				start = start * 10 + (tmp - '0');
			}
			finish = 0;
			while((tmp = getc_unlocked(stdin)) != '\n'){
				finish = finish * 10 + (tmp - '0');
			}
			if (start < finish)
				planRouteFW(start, finish);
			else
				planRouteBW(start, finish);
		}
	}
	//inorderTreeWalk(t->root); DEBUG
	return 0;
}
/*      DEBUG      */
void stampaStazione(pntNodo x){

	int i;

	printf("stazione al kilometro %d, con un totale di %d.\ncon le macchine:\t", x->km, x->numCar - 1);
	for(i = 0; i < x->numCar; i++) {
		printf("%d ", x->car[i]);
	}
	putchar_unlocked('\n');
}

void inorderTreeWalk(pntNodo x) {
	if(x != nil){
		inorderTreeWalk(x->left);
		//printf("%d\t", x->km);
		stampaStazione(x);
		inorderTreeWalk(x->right);
	}
}
