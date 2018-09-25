/*
 * main.c
 *
 *  Created on: Sep 12, 2018
 *      Author: user
 */
#include <stdio.h>

#include "../lib/planificador.h"
#include "../lib/const.h"

int (*orden_ascendente)(TEntrada, TEntrada);
int (*orden_descendente)(TEntrada, TEntrada);

int main(int argc, char **argv) {

	char op;
	FILE *fp;

	if (argc != 2) {
		fprintf(stderr, "Error.Invocacion invalida.\n"
				"\t\tplanificador <archivo_texto>\n");
		return BAD_ARGS;
	}

	op = mostrar_menu();

	fp = fopen(*argv[1], 'r');
	if (!fp)
		return FILE_ERR;

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

	fclose(fp);

	return 0;
}


char mostrar_menu() {

	char opcion;

	fscanf(stdin, "%c", &opcion);

	return opcion;
}
