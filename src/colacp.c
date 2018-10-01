#include <stdio.h>
#include "../lib/colacp.h"

static int (*comparar)(TEntrada e1, TEntrada e2);

TColaCP crear_cola_cp(int (*f)(TEntrada, TEntrada)) {

	TColaCP nueva = malloc(sizeof(TColaCP));
	if (nueva == NULL)
		return -2;

	nueva->cantidad_elementos = 0;
	nueva->raiz = malloc(sizeof(struct nodo));
	if (nueva->raiz == NULL) {
		free(nueva);
		return -2;
	} else {
		nueva->raiz->padre = NULL;
		nueva->raiz->entrada = malloc(sizeof(struct entrada));
		if (nueva->raiz->entrada == NULL) {
			free(nueva->raiz);
			free(nueva);
		}
		nueva->raiz->hijo_derecho = NULL;
		nueva->raiz->hijo_izquierdo = NULL;
	}
	comparar = f;


	return nueva;
}
