#include "../lib/planificador.h"
#include "../lib/const.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static TCiudad leer_ciudad(FILE *fp);
float distancia(struct punto p1, struct punto p2);

void mostrar(FILE *fp, int (*comp)(TEntrada, TEntrada)) {

	int i = 0;
	struct punto pos_actual, pos_ciudad_actual;
	TCiudad c;

	TEntrada entry;
	TColaCP cola_ascendente;

	cola_ascendente = crear_cola_cp(comp);
	if (cola_ascendente != NULL) {

		fscanf(fp, "%f;%f\n", &(pos_actual.x), &(pos_actual.y));

		// Armamos la lista de ciudades (Orden ascendente o descendente)
		c = leer_ciudad(fp);
		while (c != NULL) {
			pos_ciudad_actual.x = c->pos_x;
			pos_ciudad_actual.y = c->pos_y;

			entry = (TEntrada) malloc(sizeof(struct entrada));
			if (entry != NULL) {
				entry->clave = (float *)malloc(sizeof(float));
				*(entry->clave) = distancia(pos_actual, pos_ciudad_actual);
				entry->valor = c->nombre;

				cp_insertar(cola_ascendente, entry);
				c = leer_ciudad(fp);
			}
		}

		while (cp_size(cola_ascendente) > 0) {
			entry = cp_eliminar(cola_ascendente);
			fprintf(stdout, "%d. %s\n", ++i, entry->valor);
		}
	}
}

float reducir_horas_manejo(FILE *fp) {

	int counter = 0;
	float distancia_total = 0.0;

	struct punto pos_actual;
	TCiudad c, ultima_ciudad, ciudad_mas_cercana;
	TLista lista_destinos;
	TPosicion pos;
	TColaCP cola;

	// Obtengo la posicion actual del viajero
	rewind(fp);
	if (!feof(fp))
		fscanf(fp, "%f;%f\n", &(pos_actual.x), &(pos_actual.y));

	// Armamos la lista de destinos
	lista_destinos = crear_lista();
	c = leer_ciudad(fp);
	pos = POS_NULA;
	while (c != NULL) {
		l_insertrar(&lista_destinos, pos , c);

		c = leer_ciudad(fp);
		pos = l_ultima(lista_destinos);
	}

	// Para cada destino de la lista de destinos, buscamos el que esta a menor distancia
	// y lo agregamos a un heap que usa las distancias como clave
	// luego, actualizamos la posicion actual a la posicion de la ultima ciudad visitada y seguimos
	// No olvidar: Sumar la distancia para retornarla al final
	while (l_size(lista_destinos) > 0) {
		// Busco la posicion mas cercana a la posicion actual
		for (pos = l_primera(lista_destinos); pos != POS_NULA; pos = l_siguiente(pos)) {
			c = (TCiudad) pos->elemento;

			if (distancia(ultima_ciudad, c) < distancia(ultima_ciudad, ciudad_mas_cercana))
				ciudad_mas_cercana = c;
		}

		fprintf(stdout, "%d. %s\n", ++counter, ((TCiudad) pos->elemento)->nombre);
		ultima_ciudad = ciudad_mas_cercana;
		l_eliminar(lista_destinos, pos);
	}

	return distancia_total;
}

char mostrar_menu(void) {

	char c;

	fprintf(stdout, "Bienvenido %s!\n", getenv("USER"));
	fprintf(stdout, "Ingrese la opcion que desea...\n"
			"1. Mostrar las ciudades en orden ascendente\n"
			"2. Mostrar las ciudades en orden descendente\n"
			"3. Motrar la ruta de menor tiempo al volante\n"
			"4. Salir del programa: ");

	fscanf(stdin, "%c", &c);

	return c;
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
		if (!feof(fp) && leida->nombre != NULL)
			fscanf(fp, "%s;%f;%f\n", leida->nombre, &(leida->pos_x), &(leida->pos_y));
		else
			free(leida);
	} else
		leida = NULL;

	return leida;
}

float distancia(TCiudad c1, TCiudad c2) {
	return 0;
}
