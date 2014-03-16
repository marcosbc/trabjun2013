/**
 *	PROYECTO: ESTRUCTURAS DINÁMICAS
 *	FUNDAMENTOS DE LA PROGRAMACIÓN II
 *
 *	Archivo:		io.c
 *	Autor:			Marcos Bjorkelund (login: marbjo1)
 *	Fecha creación:	17/02/2013 20:50
 *	Última modif.:	20/04/2013 00:09
 *	Explicación:	Contiene todas las funciones relacionadas
 *					a la ENTRADA Y SALIDA para el programa
 */

/* Ficheros de inclusión del sistema */
#include <stdio.h>
#include <stdlib.h>

/* Ficheros de inclusión locales */
#include "principal.h"
#include "nodos.h"
#include "enlaces.h"
#include "io.h"

// Procesa el fichero de entrada, estableciendo el nodo inicial (origen)
// y el final (destino)
void procesarFichEnt(FILE * fich, nodo * nodos, nodo ** inicial,
					nodo ** final, int * e)
{
	int narg = 0;				// Núm. de argumentos para fscanf
	char * linea = NULL;		// Cadena para reservar dinámicamente
	char * eof_fgets = NULL;	// NULL si estaamos en EOF en fgets
	int ip_inicial_leida = 0;	// Banderas para comprobar
	int ip_final_leida = 0;		// Lo mismo que para el anterior
	direccion ipAux;			// Una variable tipo IP (auxiliar)
	
	// Realizar la reserva dinámica de memoria para la línea
	linea = (char *) calloc(MAX_FICH_ENT, sizeof(char));
	
	// Si se ha reservado bien podemos seguir
	if(linea != NULL)
	{
		// Comprobar que no hemos llegado a fin de fichero
		while((eof_fgets = fgets(linea, MAX_FICH_ENT, fich)) != NULL
			  && ! ip_final_leida)
		{
			// Procesamos la línea leída con sscanf para sacar datos
			narg = sscanf(linea, "%d.%d.%d.%d",
						  // Para el primer nodo (la IP origen)
						  &(ipAux[0]), &(ipAux[1]),
						  &(ipAux[2]), &(ipAux[3]));
							  
			// Si hemos encontrado una IP, asignar y marcar
			// Si no hemos encontrado una IP, pasar y repetir  ciclo
			if(narg == 4)
			{
				// Estamos ante la IP destino (nodo "final")
				if(ip_inicial_leida)
				{
					// Marcamos la bandera y asignamos la IP
					ip_final_leida = 1;
					
					*final = buscaNodo(ipAux, &nodos);
				}
				// Estamos ante la IP origen (nodo "inicial")
				else
				{
					// Marcamos la bandera y asignamos la IP
					ip_inicial_leida = 1;
					*inicial = buscaNodo(ipAux, &nodos);
				}
			}
		}
	}
	
	else
	{
		// Acticar la bandera de error al haber error de reserva
		// de memoria
		*e = ERROR;
	}
	
	// Liberamos de la memoria la linea de texto que hemos reservado
	free(linea);
}

// Comprueba si el fich. de configuración es correcto y crea los nodos,
// es decir, las IPs que aparezcan en ellos si no se han creado ya
// fich NO puede ser false (debe hacerse la comprobación antes)
int procesarFichConf(FILE * fich, enlace ** enlaces,
					 nodo ** nodos, int * e)
{
	int narg = 0;				// Núm. de argumentos para fscanf
	char * linea = NULL;		// Cadena para reservar dinámicamente
	int devolucion = 1;			// Valor para devolver
	
	// Cadenas para almacenar las IPs
	char ip1[MAX_IP_LONG];
	char ip2[MAX_IP_LONG];
	int enlaceOK;
	int ipCorrectas;

	// Nodos auxiliares
	nodo * nodo1 = NULL;
	nodo * nodo2 = NULL;
	enlace * enlaceAInsertar = NULL;
	
	// Comprobamos que podemos abrir el fichero en modo "sólo lectura"
	// Reserva dinámica de memoria para almacenar líneas completas
	linea = (char *) calloc(MAX_FICH_CONF, sizeof(char));
	
	// Si se ha reservado bien podemos seguir
	if(linea != NULL)
	{
		// Comprobar que no hemos llegado a fin de fichero
		while(fgets(linea, MAX_FICH_CONF, fich) != NULL
			  && devolucion != 0)
		{
			// Reestablecer el valor de enlaceOK e ipCorrectas
			enlaceOK = 0;
			ipCorrectas = 0;

			// Crear los nodos
			nodo1 = creaNodo();
			nodo2 = creaNodo();
			
			// Crear el enlace
			enlaceAInsertar = creaEnlace();
			
			// Si se ha reservado bien las memorias
			if(enlaceAInsertar != NULL && nodo1 != NULL && nodo2 != NULL)
			{
				// Procesamos la línea leída con sscanf para sacar
				// los datos
				narg = sscanf(linea, "%s %s %d",
							  ip1, ip2, &(enlaceAInsertar->peso));

				if(narg == 3)
				{
					// Almacenar las IPs en los nodos, con ipCorrectas
					// como bandera de error (1: correctas, 0: no)
					ipCorrectas = insertaIPEnNodo(ip1, MAX_IP_LONG, &nodo1)
								&& insertaIPEnNodo(ip2, MAX_IP_LONG, &nodo2);
					
					if(ipCorrectas)
					{
						// Si existen ya alguno de los nodos creados,
						// usaremos una función que hará el trabajo de
						// liberar uno de la memoria y devolver puntero
						// Si no existe, se insertará en la lista nodos
						// NOTA: la lista de nodos hasta aquí es NULL
						// y se modificará su valor
						manejaNodo(&nodo1, nodos);
						manejaNodo(&nodo2, nodos);
					
						// No lo juntamos para simplificar el if-else,
						// pues el else depende de enlaceOK
						enlaceOK = configuraEnlace(nodo1, nodo2,
													enlaces,
													&enlaceAInsertar);
					}
				}
			}
			else
			{
				*e = ERROR;
				devolucion = 0;
			}

			// No se ha usado los nodos, así que liberarlos
			if(! ipCorrectas)
			{
				liberaNodo(nodo1);
				liberaNodo(nodo2);
			}

			// No se han usado los enlaces o bien el fichero de
			// configuración está mal
			if(! enlaceOK)
			{
				// No se ha usado el enlace: Liberarlo
				liberaEnlace(enlaceAInsertar);

				// Error de fichero de configuración: No ha habido
				// datos suficientes (argumentos para sscanf)
				if(narg >= 0)
					// Se devuelve 0 al ser utilizado en expresión if
					devolucion = 0;
			}
		}
	}
	
	// Si no se ha podido reservar, activamos la bandera de errores
	// Se producirá un ERROR DE RESERVA DE MEMORIA
	else
	{
		*e = ERROR;
		devolucion = 0;
	}
	
	// Liberamos de la memoria la linea de texto que hemos reservado
	free(linea);
	
	return devolucion;
}

// Imprime el resultado final: La distancia mínima entre dos nodos
void salidaFichSal(FILE * fich, nodo * inicial, nodo * final, enlace * enlaces)
{
	// Declaración de variables
	nodo * ant = NULL;		// El nodo anterior
	nodo * act = inicial;	// El nodo actual
		
	// El coste total para la primera línea
	int costeTotal = final->coste;
		
	// Imprimir las primeras líneas (las cabeceras)
	fprintf(fich, "%d.%d.%d.%d\t%d.%d.%d.%d\t%d\n\nCamino\n",
			// La IP del nodo inicial
			inicial->ip[0], inicial->ip[1],
			inicial->ip[2], inicial->ip[3],
				
			// La IP del nodo final
			final->ip[0], final->ip[1],
			final->ip[2], final->ip[3],
				
			// El coste total
			costeTotal);
	
	// Recorrer el bucle para la impresión siempre que se pueda
	while(act != NULL)
	{
		// Realizar la impresión
		fprintf(fich, "%d.%d.%d.%d\t%d\t%d\n",
				// La IP del nodo inicial
				act->ip[0], act->ip[1],
				act->ip[2], act->ip[3],
				
				// Los costes: Lo que se sumará y lo sumado
				consiguePesoDeEnlace(ant, act, enlaces), act->coste);
			
		// Actualizar el nodo inicial para recorrer
		ant = act;
		act = act->sig;
	}
}

// Imprime un error según texto descriptivo e ID. Sigue una estructura básica
void imprimirError(int id)
{
	switch(id)
	{
		// Error de número de argumentos
		case ERR_ARGS_ID :
			fprintf(stderr, ERR_STR, id, ERR_ARGS);
			break;
		// Error de lectura del fichero de configuración
		case ERR_CONF_LEC_ID :
			fprintf(stderr, ERR_STR, id, ERR_CONF_LEC);
			break;
		// Error en el fichero de configuración
		case ERR_CONF_INC_ID :
			fprintf(stderr, ERR_STR, id, ERR_CONF_INC);
			break;
		// Error de lectura del fichero de entrada
		case ERR_ENT_ID :
			fprintf(stderr, ERR_STR, id, ERR_ENT);
			break;
		// Error de lectura/escritura en el fichero de salida
		case ERR_SAL_ID :
			fprintf(stderr, ERR_STR, id, ERR_SAL);
			break;
		// Error de reserva de memoria
		case ERR_MEM_ID :
			fprintf(stderr, ERR_STR, id, ERR_MEM);
	}
}
