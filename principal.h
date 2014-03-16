/**
 *	PROYECTO: ESTRUCTURAS DIN�MICAS
 *	FUNDAMENTOS DE LA PROGRAMACI�N II
 *
 *	Archivo:		principal.h
 *	Autor:			Marcos Bjorkelund (login: marbjo1)
 *	Fecha creaci�n:	17/02/2013 13:30
 *	�ltima modif.:	19/04/2013 13:50
 *	Notas:			En este archivo contendremos todas las
 *					declaraciones de constantes y tipos
 */

#ifndef __DEF_PRINCIPAL__
#define __DEF_PRINCIPAL__

/**
 * Definici�n de constantes
 */
// Numero de subindices de una IP
#define NUM_RANG 9

// Rango de n�meros de una direcci�n IP
#define MIN_IP 0
#define MAX_IP 255

// Error y no error, para la variable e
#define ERROR   1
#define NOERROR 0

// El n�mero de argumentos necesarios para la aplicaci�n
#define NUM_ARGS 4

// Posici�n de cada fichero
#define POS_CON 1
#define POS_ENT 2
#define POS_SAL 3

// Rango de valores del coste
#define MIN_COSTE		0
#define MAX_COSTE		1024
#define COSTE_INFINITO	9999

// Longitud m�xima de una IP en formato cadena (=> sumar 1 por
// estar en formato tabla). Supongamos el peor caso
#define MAX_IP_LONG 16

/**
 * Definici�n de constantes
 */
// Identificaci�n de los errores
#define ERR_ARGS "argumentos incorrectos"
#define ERR_ARGS_ID 1

#define ERR_CONF_LEC "el fichero de configuracion no se puede leer"
#define ERR_CONF_LEC_ID 2

#define ERR_CONF_INC "el fichero de configuracion es incorrecto"
#define ERR_CONF_INC_ID 3

#define ERR_ENT "el fichero de entrada no se puede leer"
#define ERR_ENT_ID 4

#define ERR_SAL "el fichero de salida no se puede abrir"
#define ERR_SAL_ID 5

#define ERR_MEM "error de memoria"
#define ERR_MEM_ID 6

// Definici�n de la cadena de cuerpo del error
#define ERR_STR "Error %d: %s.\n"

// M�ximo no. de caracteres para ficheros de configuraci�n
// Nos aseguramos de cubrir de sobra la l�nea
#define MAX_FICH_CONF 256

// M�ximo no. de caracteres para ficheros de entrada
// Nos aseguramos de cubrir de sobra la l�nea
#define MAX_FICH_ENT 256

/**
 * Definici�n de los tipos asociados
 */

// Tipo que contendr� una direccion IP (en principio, tipo IPv4)
typedef int direccion[NUM_RANG];

// El tipo que usaremos para identificar a cada IP
typedef struct estructuraNodo {
	// Conjunto info
	int coste;		// Coste sumado desde primer nodo en soluci�n
	direccion ip;	// La direcci�n IP
	
	// Enlace anterior, hace que act�e como un �rbol
	struct estructuraNodo * pred; // El nodo
	
	// El siguiente nodo en el conjunto de ellos, para recorrer
	// la lista
	struct estructuraNodo * sigEnganche;
	
	// El siguiente nodo de la SOLUCI�N FINAL
	// Deber�a dar, desde el nodo origen, los pasos hasta el final
	struct estructuraNodo * sig;
} nodo;

// El tipo "enlace", para enlaces entre nodos
typedef struct estructuraEnlace {
	// El peso del enlace
	int peso;
	
	// Los nodos destino e origen
	nodo * origen;
	nodo * destino;
	
	// El siguiente enlace (para recorrer la lista de enlaces)
	struct estructuraEnlace * sig;
} enlace;

#endif
