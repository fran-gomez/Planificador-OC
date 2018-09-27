#include "../lib/planificador.h"

#include <stdio.h>
#include <stdlib.h>

struct punto {
	float x;
	float y;
};

static TCiudad leer_ciudad(FILE *fp);

void mostrar(FILE *fp, int (*comp)(TEntrada, TEntrada)) {

	int i = 0;
	struct punto p;
	TCiudad c;

	TEntrada entry = (TEntrada) malloc(sizeof(struct entrada));
	TColaCP cola_ascendente;

	cola_ascendente = crear_cola_cp(comp);
	if (cola_ascendente != NULL) {
		c = leer_ciudad(fp);
		while (c != NULL) {
			p.x = c->pos_x;
			p.y = c->pos_y;

			entry->clave = &p;
			entry->valor = c->nombre;

			cp_insertar(cola_ascendente, entry);
			c = leer_ciudad(fp);
		}

		while (cp_size(cola_ascendente) > 0) {
			entry = cp_eliminar(cola_ascendente);
			fprintf(stdout, "%d. %s\n", ++i, entry->valor);
		}
	}
}

float reducir_horas_manejo(FILE *fp) {

	float distancia = 0.0;
	struct punto pos_actual;
	TCiudad c;
	TLista lista_destinos;
	TColaCP cola;

	// Obtengo la posicion actual del viajero
	rewind(fp);
	if (!feof(fp))
		fscanf(fp, "%f;%f\n", &(pos_actual.x), &(pos_actual.y));

	// Armamos la lista de destinos
	lista_destinos = crear_lista();
	c = leer_ciudad(fp);
	while (c != NULL) {

	}

	// Para cada destino de la lista de destinos, buscamos el que esta a menor distancia
	// y li agregamos a un heap que usa las distancias como clave
	// No olvidar: Sumar la distancia para retornarla al final
	return distancia;
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
