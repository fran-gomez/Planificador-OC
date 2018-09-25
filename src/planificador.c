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

	TCiudad c = (TCiudad) malloc(sizeof(TCiudad));

	TEntrada entry = (TEntrada) malloc(sizeof(struct entrada));
	TColaCP cola_ascendente;

	cola_ascendente = crear_cola_cp(comp);
	if (cola_ascendente != NULL) {
		while (c != NULL) {
			c = leer_ciudad(fp);

			p.x = c->pos_x;
			p.y = c->pos_y;

			entry->clave = &p;
			entry->valor = c->nombre;

			cp_insertar(cola_ascendente, entry);
		}

		while (cp_size(cola_ascendente) > 0) {
			entry = cp_eliminar(cola_ascendente);
			fprintf(stdout, "%d. %s\n", ++i, entry->valor);
		}
	}
}

float reducir_horas_manejo(FILE *fp) {

	float horas = 0.0;
	struct punto pos_actual;

	// Obtengo la posicion actual del viajero
	if (!feof(fp))
		fscanf("%f;%f\n", &(pos_actual.x), &(pos_actual.y));

	// Armamos la lista de destinos


	return horas;
}


// Funciones auxiliares
static TCiudad leer_ciudad(FILE *fp) {

	TCiudad leida = (TCiudad) malloc(sizeof(TCiudad));

	if (!feof(fp) && leida != NULL) {
		leida->nombre = (char *) malloc(sizeof(char) * 15);
		if (!feof(fp) && leida->nombre != NULL)
			fscanf(fp, "%s;%f;%f", leida->nombre, &(leida->pos_x), &(leida->pos_y));
		else
			free(leida);
	} else
		leida = NULL;

	return leida;
}
