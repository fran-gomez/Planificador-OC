
test-lista:
	echo "Construyendo tester lista"
	gcc test/lista-test.c src/lista.c -o lista_test

test-colacp:
	echo "Construyendo tester cola con prioridad"
	gcc test/colacp-test.c src/colacp.c -o colacp_test

all: src/*.c
	echo "Construyendo programa..."
	gcc -Wall src/*.c -o planificador >log.txt 2>&1

run: all
	./planificador viajes.txt

clean:
	rm -rf planificador log.txt
