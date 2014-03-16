/**
 *	PROYECTO: ESTRUCTURAS DINÁMICAS
 *	FUNDAMENTOS DE LA PROGRAMACIÓN II
 *
 *	Archivo:		miscelaneos.h
 *	Autor:			Marcos Bjorkelund (login: marbjo1)
 *	Fecha creación:	17/04/2013 19:31
 *	Última modif.:	19/04/2013 13:52
 */

#ifndef	__DEF_MISC__
#define	__DEF_MISC__

/**
 * Prototipos de funciones
 */
// Comprueba si una IP es correcta (según el rango de cada índice)
int ipCorrecta(direccion ip);

// Comprueba si una IP en formato cadena se puede comprobar
// Es decir, si no tiene errores que, en nuestro programa, podrían
// entrar en conflicto con sscanf
int ipStringComprobable(char * ip, int tam);

// Comprueba si dos IPs son las mismas
int mismaIP(direccion ip1, direccion ip2);

// Devuelve 0 si se encuentra en el rango: n es menor que min o mayor
// que max, 1 en caso contrario
int menorOMayor(int min, int max, int n);

#endif
