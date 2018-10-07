#include "planificador.h"
#include "const.h"
#include "lista.h"
#include "colacp.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static TCiudad leer_ciudad(FILE *fp);
float *distancia(TCiudad c1, TCiudad c2);

void mostrar(FILE *fp, int (*comp)(TEntrada, TEntrada)) {

	int i = 0;

	TCiudad c, mi_posicion;
	TEntrada entry;
	TColaCP cola;

	cola = crear_cola_cp(comp);
	if (cola != NULL) {
		// Obtengo la posicion actual del viajero
		mi_posicion = (TCiudad) malloc(sizeof(struct ciudad));
		if (mi_posicion != NULL) {
			fscanf(fp, "%f;%f\n", &(mi_posicion->pos_x), &(mi_posicion->pos_y));

			// Armamos la cola de ciudades (Orden ascendente o descendente)
			c = leer_ciudad(fp);
			while (c != NULL) {
				entry = (TEntrada) malloc(sizeof(struct entrada));
				if (entry != NULL) {
					entry->clave = distancia(mi_posicion, c);
					entry->valor = c->nombre;

					cp_insertar(cola, entry);
				} else {
					free(cola);
					return;
				}
				c = leer_ciudad(fp);
			}

			while (cp_size(cola) > 0) {
				entry = cp_eliminar(cola);
				fprintf(stdout, "%d. %s\n", ++i, ((char *)entry->valor));
			}
		} else
			cp_destruir(cola);
	}
}

float reducir_horas_manejo(FILE *fp, int (*comp_ascendente)(TEntrada, TEntrada)) {

	int counter = 0, lista_destinos_sz;
	float distancia_total = 0.0;
	TEntrada entry;

	TCiudad c, ciudad_actual, ciudad_mas_cercana;
	TLista lista_destinos;
	TPosicion pos;
	TColaCP *colas;

	// Obtengo la posicion actual del viajero
	rewind(fp);
	if (!feof(fp)) {
		ciudad_actual = (TCiudad) malloc(sizeof(struct ciudad));
		if (ciudad_actual != NULL)
			fscanf(fp, "%f;%f\n", &(ciudad_actual->pos_x), &(ciudad_actual->pos_y));
		else
			return -1.0;
	}

	// Armamos la lista de destinos
	lista_destinos = crear_lista();
	c = leer_ciudad(fp);
	while (c != NULL) {
		l_insertar(&lista_destinos, POS_NULA, c);
		c = leer_ciudad(fp);
		//pos = l_ultima(lista_destinos);
	}

	printf("Pase la creacion de la lista\n");

	//
	lista_destinos_sz = l_size(lista_destinos);
	colas = (TColaCP *) malloc(sizeof(struct cola_con_prioridad) * lista_destinos_sz);
	while (lista_destinos_sz > 0) {
		colas[counter] = crear_cola_cp(comp_ascendente);

		for (pos = l_primera(lista_destinos); pos != POS_NULA; pos = l_siguiente(lista_destinos, pos)) {
			entry = (TEntrada) malloc(sizeof(struct entrada));
			if (entry != NULL) {
				entry->clave = distancia(ciudad_actual, pos->elemento);
				entry->valor = pos;
				cp_insertar(colas[counter], entry);
			}
		}
	}

	return distancia_total;
}

void salir(void) {
	fprintf(stdout, "Adios %s!\n", getenv("USER"));
	exit(0);
}

// Funciones auxiliares
static TCiudad leer_ciudad(FILE *fp) {

	TCiudad leida = (TCiudad) malloc(sizeof(struct ciudad));

	if (!feof(fp) && leida != NULL) {
		leida->nombre = (char *) malloc(sizeof(char) * 15);
		if (leida->nombre != NULL)
			fscanf(fp, "%[^;];%f;%f\n", leida->nombre, &(leida->pos_x), &(leida->pos_y));
		else
			free(leida);
	} else
		leida = NULL;

	return leida;
}

float *distancia(TCiudad c1, TCiudad c2) {

	float *dist = (float *)malloc(sizeof(float));

	*dist = abs(c2->pos_x - c1->pos_x) + abs(c2->pos_y - c1->pos_y);

	return dist;
}
