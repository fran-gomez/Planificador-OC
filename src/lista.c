#include "../lib/lista.h"
#include "../lib/const.h"

#include <stdio.h>
#include <stdlib.h>

TLista crear_lista() {
	return POS_NULA;
}

int l_destruir(TLista *lista) {

	TPosicion p = l_primera(*lista), aux;

	while (p != NULL) {
		aux = p;
		p = p->celda_siguiente;
		free(aux);
	}

	free(*lista);

	return TRUE;
}

static void agregar_entre(TPosicion prev, TPosicion succ, TPosicion nueva) {
	if (prev != POS_NULA)
		prev->celda_siguiente = nueva;
	if (succ != POS_NULA)
		succ->celda_anterior = nueva;

	nueva->celda_anterior = prev;
	nueva->celda_siguiente = succ;
}

int l_insertar(TLista *lista, TPosicion pos, TElemento elem) {

	TPosicion nueva = (TPosicion) malloc(sizeof(struct celda));
	if (nueva == NULL)
		return FALSE;

	nueva->elemento = elem;

	if (*lista == POS_NULA)
		*lista = nueva;
	else {
		if (pos == POS_NULA) {
			nueva->celda_siguiente = *lista;
			(*lista)->celda_anterior = nueva;
			*lista = nueva;
		} else
			agregar_entre(pos->celda_anterior, pos, nueva);
	}

	return TRUE;
}

int l_eliminar(TLista *lista, TPosicion pos) {

	if (*lista == POS_NULA)
		return FALSE;

	TPosicion anterior, siguiente;

	// Acomodamos la lista, enganchando los elementos que rodean al eliminado
	anterior = pos->celda_anterior;
	siguiente = pos->celda_siguiente;

	anterior->celda_siguiente = siguiente;
	siguiente->celda_anterior = anterior;

	// Liberamos la memoria asignada al elemento a eliminar
	free(pos);

	return TRUE;
}

TPosicion l_primera(TLista lista) {

	TPosicion primera = lista;

	while (primera->celda_anterior != POS_NULA)
		primera = primera->celda_anterior;

	return primera;
}

TPosicion l_ultima(TLista lista) {

	TPosicion ultima = lista;

	while (ultima->celda_siguiente != POS_NULA)
		ultima = ultima->celda_siguiente;

	return ultima;
}

TPosicion l_anterior(TLista lista, TPosicion pos) {

	TPosicion anterior;

	if (pos->celda_anterior == POS_NULA)
		anterior = POS_NULA;
	else
		anterior = pos->celda_anterior;

	return anterior;
}

TPosicion l_siguiente(TLista lista, TPosicion pos) {

	TPosicion siguiente;

	if (pos->celda_siguiente == POS_NULA)
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
	TPosicion p = l_primera(lista);

	while (p->celda_siguiente != POS_NULA) {
		++cant_elem;
		p = p->celda_siguiente;
	}

	return cant_elem;
}
