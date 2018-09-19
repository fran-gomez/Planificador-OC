#include <../lib/planificador.h>
#include <stdio.h>

static TCiudad leer_ciudad(FILE *fp);


void mostrar_ascendente(FILE *fp) {

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
		if (!eof(fp) && leida->nombre != NULL)
			fscanf(fp, "%s;%d;%d", leida->nombre, &(leida->pos_x), &(leida->pos_y));
		else
			free(leida);
	}

	return leida;
}
