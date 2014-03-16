trabjun2013
===========

Project created for the subject Programming Fundamentals II (Fundamentos de Programación II) in the University of Seville during the first semester of 2013.

This project finds the optimal route between two determine IPs, given a list of links (between two given IPs).

How to use
----------

First, execute the following command:

```
make
```

We'll need three files (all in plain text format):
* A configuration file (e.g. configuracion.txt). This file will contain all links between two IPs.
* An input file (e.g. entrada.txt). Contains the initial and final point, in the same order.
* An output file (e.g. salida.txt). Once executed the program, it will contain the result. If no result available, it will display that.

These will be passed to the shell in the following way:
```
./trabjun2013 configuracion.txt entrada.txt salida.txt
```

File examples
-------------

Given the following configuration file:
```
1.1.1.1 2.2.2.2 1 
1.1.1.1 3.3.3.3 4 
2.2.2.2 3.3.3.3 1 
2.2.2.2 4.4.4.4 8 
3.3.3.3 2.2.2.2 2 
3.3.3.3 5.5.5.5 2 
4.4.4.4 5.5.5.5 2 
5.5.5.5 4.4.4.4 4
```

And the following input file:
```
1.1.1.1 
4.4.4.4
```

The output would be:
```
1.1.1.1 4.4.4.4 8 
 
Camino 
1.1.1.1 0 0 
2.2.2.2 1 1 
3.3.3.3 1 2 
5.5.5.5 2 4 
4.4.4.4 4 8
```
