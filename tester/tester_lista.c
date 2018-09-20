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

	int i;
	TLista nueva;
	TPosicion aux;
	struct test *t;

	nueva = crear_lista();

	for (i = 0; i < 2; i++) {
		for (i = 0; i < 20; i++) {
			t = (struct test *) malloc(sizeof(struct test));
			inicializar(t);
			l_insertar(&nueva, POS_NULA, t);
			printf("Insertado el elemento ");
			print(t);
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
