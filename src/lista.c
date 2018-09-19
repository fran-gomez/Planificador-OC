#include "../lib/lista.h"
#include "../lib/const.h"

#include <stdio.h>
#include <stdlib.h>

TLista crear_lista() {

	TLista nueva = malloc(sizeof(TLista));

	if (nueva != NULL) {
		nueva->celda_anterior = NULL;
		nueva->celda_siguiente = NULL;
		nueva->elemento = NULL;
	}

	return nueva;
}

int l_destruir(TLista *lista) {

	TPosicion p = *lista, aux;

	while (p != NULL) {
		aux = p;
		p = p->celda_siguiente;

		free(aux->celda_anterior);
		free(aux->elemento);
		free(aux);
	}

	free(lista);

	return TRUE;
}

int l_insertar(TLista *lista, TPosicion pos, TElemento elem) {

	// Agregamos el elemento en la primer posicion de la lista
	if (pos == POS_NULA) {
		TPosicion nueva = malloc(sizeof(TPosicion));
		if (nueva == NULL)
			return FALSE;

		nueva->elemento = elem;
		nueva->celda_anterior = NULL;
		nueva->celda_siguiente = *lista;
	}

	return TRUE;
}

int l_eliminar(TLista *lista, TPosicion pos) {

	TPosicion anterior, siguiente;

	// Acomodamos la lista, enganchando los elementos que rodean al eliminado
	anterior = pos->celda_anterior;
	siguiente = pos->celda_siguiente;

	anterior->celda_siguiente = siguiente;
	siguiente->celda_anterior = anterior;

	// Liberamos la memoria asignada al elemento a eliminar
	free(pos->elemento);
	free(pos);

	return TRUE;
}

TPosicion l_primera(TLista lista) {

	TPosicion primera = lista;

	if (primera->celda_anterior != NULL)
		while (primera->celda_anterior != NULL)
			primera = primera->celda_anterior;

	return primera;
}

TPosicion l_ultima(TLista lista) {

	TPosicion ultima = lista;

	if (ultima->celda_siguiente != NULL)
		while (ultima->celda_siguiente != NULL)
			ultima = ultima->celda_siguiente;

	return ultima;
}

TPosicion l_anterior(TLista lista, TPosicion pos) {

	TPosicion anterior;

	if (pos->celda_anterior == NULL)
		anterior = POS_NULA;
	else
		anterior = pos->celda_anterior;

	return anterior;
}

TPosicion l_siguiente(TLista lista, TPosicion pos) {

	TPosicion siguiente;

	if (pos->celda_siguiente == NULL)
		siguiente = POS_NULA;
	else
		siguiente = pos->celda_siguiente;

	return siguiente;
}

TElemento l_recuperar(TLista lista, TPosicion pos) {

	TElemento elem;

	if (pos == POS_NULA)
		elem = ELE_NULO;
	else
		elem = pos->elemento;

	return elem;
}

int l_size(TLista lista) {

	int cant_elem = 0;
	TPosicion p = lista;

	while (p != NULL) {
		cant_elem++;
		p = p->celda_siguiente;
	}

	return cant_elem;
}
