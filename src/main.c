/*
 * main.c
 *
 *  Created on: Sep 12, 2018
 *      Author: user
 */
#include <stdio.h>

#include "../lib/planificador.h"

char mostrar_menu();

int main(int argc, char **argv) {

	char op;
	FILE *fp;

	if (argc != 2) {
		fprintf(stderr, "Error.Invocacion invalida.\n"
				"\t\tplanificador <archivo_texto>\n");
		return 32;
	}

	op = mostrar_menu();

	fp = fopen(argv[1], 'r');
	if (!fp)
		return 32;

	switch (op) {
	case 'A': case 'a': // Mostrar ascendente
		mostrar_ascendente(fp);
		break;
	case 'D': case 'd': // Mostrar descendente
		mostrar_descendente(fp);
		break;
	case 'R': case 'r': // Reducir horas de manejo
		reducir_horas_manejo(fp);
		break;
	case 'S': case 's':

		break;
	default:
		fprintf(stderr, "Error. Operacion invalida.\n");
		return 33;
	}


	return 0;
}


char mostrar_menu() {

	char opcion;

	fscanf(stdin, "%c", &opcion);

	return opcion;
}
