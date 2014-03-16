/**
 *	PROYECTO: ESTRUCTURAS DIN�MICAS
 *	FUNDAMENTOS DE LA PROGRAMACI�N II
 *
 *	Archivo:		miscelaneos.h
 *	Autor:			Marcos Bjorkelund (login: marbjo1)
 *	Fecha creaci�n:	17/04/2013 19:31
 *	�ltima modif.:	19/04/2013 13:52
 */

#ifndef	__DEF_MISC__
#define	__DEF_MISC__

/**
 * Prototipos de funciones
 */
// Comprueba si una IP es correcta (seg�n el rango de cada �ndice)
int ipCorrecta(direccion ip);

// Comprueba si una IP en formato cadena se puede comprobar
// Es decir, si no tiene errores que, en nuestro programa, podr�an
// entrar en conflicto con sscanf
int ipStringComprobable(char * ip, int tam);

// Comprueba si dos IPs son las mismas
int mismaIP(direccion ip1, direccion ip2);

// Devuelve 0 si se encuentra en el rango: n es menor que min o mayor
// que max, 1 en caso contrario
int menorOMayor(int min, int max, int n);

#endif
