/*
* TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Tiago da Costa Teixeira Veloso e Volta LOGIN 1: tiago.velosoevolta
 * AUTHOR 2: Jaime Martínez Váquez  LOGIN 2: j.mvazquez
 * GROUP: 3.3
 * DATE: 02/ 04 / 2025
 */

#ifndef BID_STACK_H
#define BID_STACK_H

#include <stdbool.h>
#include "types.h"

#define SNULL -1 //Constante usada para indicar posiciones nulas
#define MAX_PILA 25 //Tamaño máximo de la pila

//Estructura de los datos de un elemento de la pila, es decir una puja
typedef struct tItemS{ //nombre del struct
 tUserId bidder;  //Pujador
 tConsolePrice consolePrice;  //Precio de la consola
} tItemS; //nombre del tipo que se esta creando con typedef

typedef int tPosS; //Tipo de dato para la posición de un elemento de la pila

//Estructura de la pila
typedef struct Stack {
 tItemS data[MAX_PILA];
 tPosS top;
} tStack;

// Función: createEmptyStack.
// Objetivo: Crea una pila vacía.
// Entradas: tStack *stack (puntero del tipo tStack).
// Salidas: ninguna.
// Precondiciones: Ninguna.
// Postcondiciones: La pila no tiene elementos.
void createEmptyStack(tStack *stack);

// Función: push.
// Objetivo: Inserta un elemento en la cima de la pila.
// Entradas: tItemS item (elemento a insertar),
//           tStack *stack (puntero de la pila).
// Salidas: true (si el elemento fue insertado),
//          false (si el elemento no fue insertado).
// Precondiciones: Ninguna.
// Postcondiciones: Ninguna.
bool push(tItemS item, tStack *stack);

// Función: pop.
// Objetivo: Elimina de la pila el elemento situado en la cima.
// Entradas: tStack *stack (puntero de la pila).
// Salidas: ninguna.
// Precondiciones: La pila no está vacía.
// Postcondiciones: Ninguna.
void pop(tStack *stack);

// Función: peek.
// Objetivo: Recupera el elemento de la cima de la pila sin eliminarlo.
// Entradas: tStack stack (pila).
// Salidas: tItemS (elemento de la cima de la pila).
// Precondiciones: La pila no está vacía.
// Postcondiciones: Ninguna.
tItemS peek(tStack stack);

// Función: isEmptyStack.
// Objetivo: Determina si una pila está vacía.
// Entradas: tStack stack (pila).
// Salidas: true (si la pila está vacía),
//          false (si la pila no está vacía).
// Precondiciones: Ninguna.
// Postcondiciones: Ninguna.
bool isEmptyStack(tStack stack);

#endif
