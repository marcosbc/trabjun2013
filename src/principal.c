/**
 *	PROYECTO: ESTRUCTURAS DIN�MICAS
 *	FUNDAMENTOS DE LA PROGRAMACI�N II
 *
 *	Archivo:		principal.c
 *	Autor:			Marcos Bjorkelund (login: marbjo1)
 *	Fecha creaci�n:	17/02/2013 13:30
 *	�ltima modif.:	19/04/2013 13:50
 *	Explicaci�n:	Contiene la funci�n main
 */
/* Ficheros de inclusi�n del sistema */
#include <stdio.h>
#include <stdlib.h>

/* Ficheros de inclusi�n locales */
#include "principal.h"		// Siempre primero
#include "miscelaneos.h"
#include "nodos.h"
#include "enlaces.h"
#include "io.h"
#include "calculo.h"

/* Funci�n principal */
int main(int argc, char * argv[])
{
	/**
	 * DECLARACI�N DE VARIABLES
	 */
	int e = NOERROR;   	// Si se produce error, se activa (e = 1)
	FILE * fcon = NULL; // Fichero de configuraci�n
	FILE * fent = NULL; // Fichero de entrada
	FILE * fsal = NULL;	// Fichero de salida
	
	// La lista de los enlaces existentes
	enlace * enlaces = NULL;
	
	// Los nodos que usaremos
	nodo * nodoInicial = NULL;	// Nodo inicial (origen)
	nodo * nodoFinal = NULL;	// Nodo final (destino)
	nodo * nodos = NULL;		// La lista de los nodos que se
								// usar� para recorrer e insertar
	
	/**
	 * COMPROBACIONES OPORTUNAS (Y CONFIGURACI�N DE ERRORES)
	 * Una vez todo haya ido bien se ejecutar� el c�digo relevante
	 * de c�lculo de caminos y salida de la soluci�n
	 */
	// �Es el n�mero de argumentos correcto?
	if(argc == NUM_ARGS)
	{
		// Abrir el fichero de configuraci�n
		fcon = fopen(argv[POS_CON], "r");
		
		// �Se ha abierto?
		if(fcon != NULL)
		{
			// Procesar el fichero de configuraci�n
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
					
					// TODO EST� YENDO BIEN
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
							 * en el funcionamiento de la aplicaci�n,
							 * en el c�lculo de caminos y salida
							 */
							// C�lculo de costes entre todas las rutas posibles
							calculoCaminos(nodoInicial, &nodos,
											&enlaces);

							// Ahora, sacar lo que nos interesa: la mejor ruta entre
							// el nodo nodoInicial y nodoFinal
							// Devuelve 1 si hay soluci�n, pero en principio no se usar�
							caminoOptimo(nodoInicial, &nodoFinal);
							
							// Imprimir la soluci�n en el fichero de salida
							salidaFichSal(fsal, nodoInicial,
											nodoFinal, enlaces);
						}
						
						// Si se da la condici�n hay ERR. RESERVA DE MEMORIA
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
			
			// No se ha podido reservar memoria din�micamente:
			// ERROR DE RESERVA DIN�MICA DE MEMORIA
			// En este caso, e est� activado: e == ERROR, y la
			// devoluci�n ha sido 0
			else if(e == ERROR)
				imprimirError(ERR_MEM_ID);
			
			// El fichero de configuraci�n es incorrecto:
			// ERROR DE FICHERO DE CONFIGURACI�N
			// En este otro caso, la bandera e no est� activada
			// PERO la devoluci�n, como en el caso anterior, fue 0
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
	 * Finalizaci�n del programa
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
