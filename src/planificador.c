#include "../lib/planificador.h"
#include "../lib/const.h"
#include "../lib/lista.h"
#include "../lib/colacp.h"

#include "../lib/debug.h"
#define DEBUG 1

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
					entry->clave = (float *)malloc(sizeof(float));
					if (entry->clave != NULL) {
						entry->clave = distancia(mi_posicion, c);
						entry->valor = c->nombre;

						cp_insertar(cola, entry);
					} else
						cp_destruir(cola);
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

float reducir_horas_manejo(FILE *fp) {

	int counter = 0;
	float distancia_total = 0.0;

	TCiudad c, ciudad_actual, ciudad_mas_cercana;
	TLista lista_destinos;
	TPosicion pos;

	// Obtengo la posicion actual del viajero
	rewind(fp);
	if (!feof(fp)) {
		ciudad_actual = (TCiudad) malloc(sizeof(struct ciudad));
		if (ciudad_actual != NULL)
			fscanf(fp, "%f;%f\n", &(ciudad_actual->pos_x), &(ciudad_actual->pos_y));
	}

	// Armamos la lista de destinos
	lista_destinos = crear_lista();
	c = leer_ciudad(fp);
	pos = POS_NULA;
	while (c != NULL) {
		printf("Insertando el %d - esimo elemento", counter++);
		if (!l_insertar(&lista_destinos, pos , c))
			fprintf(stderr, "Error insertando elemento.\n");

		c = leer_ciudad(fp);
		pos = l_ultima(lista_destinos);
	}

	// Para cada destino de la lista de destinos, buscamos el que esta a menor distancia
	// y lo agregamos a un heap que usa las distancias como clave
	// luego, actualizamos la posicion actual a la posicion de la ultima ciudad visitada y seguimos
	// No olvidar: Sumar la distancia para retornarla al final
	ciudad_mas_cercana = c;
	while (l_size(lista_destinos) > 0) {
		// Busco la posicion mas cercana a la posicion actual
		for (pos = l_primera(lista_destinos); pos != POS_NULA; pos = l_siguiente(lista_destinos, pos)) {
			c = (TCiudad) pos->elemento;

			if (distancia(ciudad_actual, c) < distancia(ciudad_actual, ciudad_mas_cercana))
				ciudad_mas_cercana = c;
		}
		distancia_total += *distancia(ciudad_actual, ciudad_mas_cercana);
		fprintf(stdout, "%d. %s\n", ++counter, ((TCiudad) pos->elemento)->nombre);
		ciudad_actual = ciudad_mas_cercana;
		l_eliminar(&lista_destinos, pos);
	}

	return distancia_total;
}

void salir(void) {
	fprintf(stdout, "Adios %s!\n", getenv("USER"));
	exit(0);
}

// Funciones auxiliares
static TCiudad leer_ciudad(FILE *fp) {

	TCiudad leida = (TCiudad) malloc(sizeof(TCiudad));

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
	struct punto p1 = {c1->pos_x, c1->pos_y};
	struct punto p2 = {c2->pos_x, c2->pos_y};

	*dist = abs(p2.x - p1.x) + abs(p2.y - p1.y);

	return dist;
}
