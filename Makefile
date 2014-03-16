# Macros que usaremos
# Compilación con avisos de errores y depuración
c = gcc -W -Wall -g

# Enlazado de ficheros objeto, eliminando estos después
enlazado: principal.o calculo.o nodos.o enlaces.o io.o miscelaneos.o
	$(c) -o trabjun2013 principal.o calculo.o nodos.o enlaces.o io.o miscelaneos.o
	make limpiar

# Compilación de principal.c
principal.o: principal.c principal.h calculo.h enlaces.h io.h miscelaneos.h nodos.h
	$(c) -c principal.c

# Compilación de io.c
io.o: io.c principal.h nodos.h enlaces.h io.h
	$(c) -c io.c

# Compilación de nodos.c
nodos.o: nodos.c principal.h nodos.h miscelaneos.h
	$(c) -c nodos.c

# Compilación de enlaces.c
enlaces.o: enlaces.c principal.h nodos.h enlaces.h miscelaneos.h
	$(c) -c enlaces.c

# Compilación de calculo.c
calculo.o: calculo.c principal.h calculo.h nodos.h
	$(c) -c calculo.c

# Compilación de miscelaneos.c
miscelaneos.o: miscelaneos.c principal.h miscelaneos.h
	$(c) -c miscelaneos.c

# Eliminar los ficheros objeto
limpiar:
	rm *.o
