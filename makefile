
test-lista:
	echo "Construyendo tester lista"
	gcc test/lista-test.c src/lista.c -o lista_test

test-colacp:
	echo "Construyendo tester cola con prioridad"
	gcc test/colacp-test.c src/colacp.c -o colacp_test

run:
	./planificador viajero.txt

all: Fuentes/*.c run
	echo "Construyendo programa..."
	gcc -Wall Fuentes/*.c -o planificador >log.txt 2>&1
    run

clean:
	rm -rf planificador log.txt
