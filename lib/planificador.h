#include <stdio.h>

#include "colacp.h"

typedef struct ciudad {
	char *nombre;
	float pos_x;
	float pos_y;
} * TCiudad;

char mostrar_menu();

void mostrar(FILE *fp, int(*comp)(TEntrada, TEntrada));
float reducir_horas_manejo(FILE *fp);
void salir();

