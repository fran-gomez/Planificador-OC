#include <stdio.h>


typedef struct ciudad {
	char *nombre;
	float pos_x;
	float pos_y;
} * TCiudad;

char mostrar_menu();

void mostrar_asecendente(FILE *fp);
void mostrar_descendente(FILE *fp);
float reducir_horas_manejor(FILE *fp);
void salir();

