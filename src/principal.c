/**
 *	PROYECTO: ESTRUCTURAS DINÁMICAS
 *	FUNDAMENTOS DE LA PROGRAMACIÓN II
 *
 *	Archivo:		principal.c
 *	Autor:			Marcos Bjorkelund (login: marbjo1)
 *	Fecha creación:	17/02/2013 13:30
 *	Última modif.:	19/04/2013 13:50
 *	Explicación:	Contiene la función main
 */
/* Ficheros de inclusión del sistema */
#include <stdio.h>
#include <stdlib.h>

/* Ficheros de inclusión locales */
#include "principal.h"		// Siempre primero
#include "miscelaneos.h"
#include "nodos.h"
#include "enlaces.h"
#include "io.h"
#include "calculo.h"

/* Función principal */
int main(int argc, char * argv[])
{
	/**
	 * DECLARACIÓN DE VARIABLES
	 */
	int e = NOERROR;   	// Si se produce error, se activa (e = 1)
	FILE * fcon = NULL; // Fichero de configuración
	FILE * fent = NULL; // Fichero de entrada
	FILE * fsal = NULL;	// Fichero de salida
	
	// La lista de los enlaces existentes
	enlace * enlaces = NULL;
	
	// Los nodos que usaremos
	nodo * nodoInicial = NULL;	// Nodo inicial (origen)
	nodo * nodoFinal = NULL;	// Nodo final (destino)
	nodo * nodos = NULL;		// La lista de los nodos que se
								// usará para recorrer e insertar
	
	/**
	 * COMPROBACIONES OPORTUNAS (Y CONFIGURACIÓN DE ERRORES)
	 * Una vez todo haya ido bien se ejecutará el código relevante
	 * de cálculo de caminos y salida de la solución
	 */
	// ¿Es el número de argumentos correcto?
	if(argc == NUM_ARGS)
	{
		// Abrir el fichero de configuración
		fcon = fopen(argv[POS_CON], "r");
		
		// ¿Se ha abierto?
		if(fcon != NULL)
		{
			// Procesar el fichero de configuración
			if(procesarFichConf(fcon, &enlaces, &nodos, &e))
			{
				// Abrir el fichero de entrada
				fent = fopen(argv[POS_ENT], "r");
				
				if(fent != NULL)
				{
					// Abrir el fichero de salida
					fsal = fopen(argv[POS_SAL], "w");
					
					// Error de lectura del fichero de salida
					if(fsal == NULL)
					{
						// Si no se ha podido abrir: Error
						imprimirError(ERR_SAL_ID);
					}
					
					// TODO ESTÁ YENDO BIEN
					else
					{
						// Procesar el fichero de entrada, activa la
						// bandera de error
						procesarFichEnt(fent, nodos, &nodoInicial,
											 &nodoFinal, &e);
						
						if(e == NOERROR)
						{
							/**
							 * Ahora que todo va bien, nos centraremos
							 * en el funcionamiento de la aplicación,
							 * en el cálculo de caminos y salida
							 */
							// Cálculo de costes entre todas las rutas posibles
							calculoCaminos(nodoInicial, &nodos,
											&enlaces);

							// Ahora, sacar lo que nos interesa: la mejor ruta entre
							// el nodo nodoInicial y nodoFinal
							// Devuelve 1 si hay solución, pero en principio no se usará
							caminoOptimo(nodoInicial, &nodoFinal);
							
							// Imprimir la solución en el fichero de salida
							salidaFichSal(fsal, nodoInicial,
											nodoFinal, enlaces);
						}
						
						// Si se da la condición hay ERR. RESERVA DE MEMORIA
						else
						{
							imprimirError(ERR_MEM_ID);
						}
					}
				}
				
				// Si no se ha abierto: Error
				else
					imprimirError(ERR_ENT_ID);
			}
			
			// No se ha podido reservar memoria dinámicamente:
			// ERROR DE RESERVA DINÁMICA DE MEMORIA
			// En este caso, e está activado: e == ERROR, y la
			// devolución ha sido 0
			else if(e == ERROR)
				imprimirError(ERR_MEM_ID);
			
			// El fichero de configuración es incorrecto:
			// ERROR DE FICHERO DE CONFIGURACIÓN
			// En este otro caso, la bandera e no está activada
			// PERO la devolución, como en el caso anterior, fue 0
			else
				imprimirError(ERR_CONF_INC_ID);
		}
		
		// No se ha podido abrir: Error
		else
			imprimirError(ERR_CONF_LEC_ID);
	}
	
	else
		// Dar error: argumentos incorrectos
		imprimirError(ERR_ARGS_ID);
	
	/**
	 * Finalización del programa
	 */
	// Libera de la memoria los nodos (la lista)
	liberaLista(&nodos);
	
	// Libera todos los enlaces
	liberaEnlaces(&enlaces);
	
	// Cerrar los ficheros abiertos
	if(fcon != NULL)
		fclose(fcon);
	if(fent != NULL)
		fclose(fent);
	if(fsal != NULL)
		fclose(fsal);

	return e;
}
