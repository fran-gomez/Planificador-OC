#include "../lib/planificador.h"

#include <stdio.h>
#include <stdlib.h>

static TCiudad leer_ciudad(FILE *fp);


void mostrar_ascendente(FILE *fp) {

	TCiudad c = (TCiudad) malloc(sizeof(TCiudad));

	while (c != NULL) {
		c = leer_ciudad(fp);
	}
}

void mostrar_descendente(FILE *fp) {

}

float reducir_horas_manejo(FILE *fp) {

	float horas = 0.0;


	return horas;
}


// Funciones auxiliares
static TCiudad leer_ciudad(FILE *fp) {

	TCiudad leida = (TCiudad) malloc(sizeof(TCiudad));

	if (leida != NULL) {
		leida->nombre = (char *) malloc(sizeof(char) * 15);
		if (!feof(fp) && leida->nombre != NULL)
			fscanf(fp, "%s;%f;%f", leida->nombre, &(leida->pos_x), &(leida->pos_y));
		else
			free(leida);
	}

	return leida;
}
