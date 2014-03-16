# Macros que usaremos
# Compilación con avisos de errores y depuración
c = gcc -W -Wall -g
s = ./src
b = ./bin

# Creamos el directorio bin
.PHONY: bin
bin:
	@mkdir -p $(b)
	@make enlazado

# Enlazado de ficheros objeto, eliminando estos después
enlazado: $(b)/principal.o $(b)/calculo.o $(b)/nodos.o $(b)/enlaces.o $(b)/io.o $(b)/miscelaneos.o
	@$(c) -o ./trabjun2013 $(b)/principal.o $(b)/calculo.o $(b)/nodos.o $(b)/enlaces.o $(b)/io.o $(b)/miscelaneos.o
#	make limpiar

# Compilación de principal.c
$(b)/principal.o: $(s)/principal.c $(s)/principal.h $(s)/calculo.h $(s)/enlaces.h $(s)/io.h $(s)/miscelaneos.h $(s)/nodos.h
	@$(c) -c $(s)/principal.c -o $(b)/principal.o

# Compilación de io.c
$(b)/io.o: $(s)/io.c $(s)/principal.h $(s)/nodos.h $(s)/enlaces.h $(s)/io.h
	@$(c) -c $(s)/io.c -o $(b)/io.o

# Compilación de nodos.c
$(b)/nodos.o: $(s)/nodos.c $(s)/principal.h $(s)/nodos.h $(s)/miscelaneos.h
	@$(c) -c $(s)/nodos.c -o $(b)/nodos.o

# Compilación de enlaces.c
$(b)/enlaces.o: $(s)/enlaces.c $(s)/principal.h $(s)/nodos.h $(s)/enlaces.h $(s)/miscelaneos.h
	@$(c) -c $(s)/enlaces.c -o $(b)/enlaces.o

# Compilación de calculo.c
$(b)/calculo.o: $(s)/calculo.c $(s)/principal.h $(s)/calculo.h $(s)/nodos.h
	@$(c) -c $(s)/calculo.c -o $(b)/calculo.o

# Compilación de miscelaneos.c
$(b)/miscelaneos.o: $(s)/miscelaneos.c $(s)/principal.h $(s)/miscelaneos.h
	@$(c) -c $(s)/miscelaneos.c -o $(b)/miscelaneos.o

# Eliminar los ficheros objeto
limpiar:
	@rm $(b)/*.o
