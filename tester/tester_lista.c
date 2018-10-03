/*
 * lista_tester.c
 *
 *  Created on: Sep 20, 2018
 *      Author: user
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../lib/const.h"
#include "../lib/lista.h"

struct test {
	int i;
	char c;
};

static void inicializar(struct test *t);
static void print(struct test *t);

int main(void) {

	int i, j;
	TLista nueva;
	TPosicion aux;
	struct test *t;

	for (i = 0; i < 2; i++) {
		nueva = crear_lista();
		aux = POS_NULA;

		for (j = 0; j < 20; j++) {
			t = (struct test *) malloc(sizeof(struct test));
			inicializar(t);
			l_insertar(&nueva, aux, t);
			printf("Insertado el elemento ");
			print(t);
			aux = l_ultima(nueva);
		}
		printf ("Size: %i\n", l_size(nueva));

		aux = l_primera(nueva);
		print(l_recuperar(nueva, aux));
		aux = l_siguiente(nueva, aux);
		print(aux->elemento);
		aux = l_ultima(nueva);
		print(aux->elemento);
		aux = l_anterior(nueva, aux);
		print(aux->elemento);

		printf("Lista destruida\n");
		l_destruir(&nueva);
	}
/*
	aux = l_primera(nueva);
	for (i = 0; i < 20; i++) {
		print(aux->elemento);
		aux = l_siguiente(nueva, aux);
	}*/
	return 0;
}

static char rand_char() {
	//srand(time(NULL));
	int r = rand();

	while ((r <= 65 && r >= 90) || (r <= 97 && r >= 122))
		r = rand();

	return r;
}

static void inicializar(struct test *t) {

	time_t t2;
	time(&t2);
	srand(t2);

	if (t != NULL) {
		t->c = rand_char();
		t->i = rand();
	} else
		printf("Error. Elemento nulo\n");
}

static void print(struct test *t) {
	if (t != NULL)
		printf("%c -> %i\n", t->c, t->i);
	else
		printf("Error. Elemento nulo\n");
}
