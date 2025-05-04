/*
* TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Tiago da Costa Teixeira Veloso e Volta LOGIN 1: tiago.velosoevolta
 * AUTHOR 2: Jaime Martínez Váquez  LOGIN 2: j.mvazquez
 * GROUP: 3.3
 * DATE: 02/ 04 / 2025
 */

#ifndef CONSOLE_LIST_H
#define CONSOLE_LIST_H

#include "types.h"
#include "bid_stack.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define LNULL NULL  //Constante usada para indicar posiciones nulas

//estructura de los datos de un elemento de la lista (una consola)
typedef struct tItemL {
    tUserId seller;  //Vendedor
    tConsoleId consoleId;  //Identificador de la consola
    tConsoleBrand consoleBrand;  //Marca de la consola
    tConsolePrice consolePrice;  //Precio de la consola
    tBidCounter bidCounter;  //Contador de pujas
    tStack bidStack;  //pila con las pujas recibidas por la consola
} tItemL;

typedef struct tItemL *tNode; //Tipo de dato para la posición de un elemento de la lista

struct tNode {
    tItemL data;
    struct tNode *next;  //Puntero para el siguiente nodo
};

typedef struct tNode *tPosL;  //Tipo de dato para la posición de un elemento de la lista
typedef struct tNode *tList;  //Tipo de dato para un nodo de la lista

// Función: createEmptyList.
// Objetivo: Crea una lista vacía.
// Entradas: tList *list (puntero del tipo tList).
// Salidas: ninguna.
// Precondiciones: Ninguna.
// Postcondiciones: La lista queda inicializada y no contiene elementos.
void createEmptyList (tList *list);

// Función: isEmptyList.
// Objetivo:Determina si la lista está vacía.
// Entradas:tList list (Lista list de tipo tList).
// Salidas: true (si la lista está vacía),
//          false (si la lista no está vacía).
// Precondiciones: Ninguna.
// Postcondiciones: Ninguna.
bool isEmptyList(tList list);

// Función: first.
// Objetivo:Devuelve la posición del primer elemento de la lista.
// Entradas: tList list (Lista list de tipo tList).
// Salidas: tPosL (primera posición válida de la lista).
// Precondiciones: La lista no está vacía.
// Postcondiciones: Ninguna./
tPosL first(tList list);

// Función: last.
// Objetivo: Devuelve la posición del último elemento de la lista.
// Entradas: tList list (Lista list de tipo tList).
// Salidas: tPosL (puntero al último elemento de la lista).
// Precondiciones: La lista no está vacía.
// Postcondiciones: Ninguna.
tPosL last(tList list);

// Función: next.
// Objetivo: Devuelve la posición en la lista del elemento siguiente al de la posición indicada (o LNULL si la posición no tiene siguiente).
// Entradas: tPosL pos (posicion pos de tipo tPosL),
//           tList list (Lista list de tipo tList).
// Salidas: tPosL (posición siguiente a pos o LNULL).
// Precondiciones: La posición indicada es una posición válida en la lista.
// Postcondiciones: Ninguna.
tPosL next(tPosL p, tList list);

// Función: previous.
// Objetivo: Devuelve la posición en la lista del elemento anterior al de la posición indicada (o LNULL si la posición no tiene anterior).
// Entradas: tPosL pos (posicion pos de tipo tPosL),
//           tList list (Lista list de tipo tList).
// Salidas: tPosL (posición anterior a pos o LNULL).
// Precondiciones: La posición indicada es una posición válida en la lista.
// Postcondiciones: Se debe recorrer la lista desde el inicio para encontrar la posición anterior, ya que la estructura de la lista no mantiene referencias al nodo previo.
tPosL previous(tPosL p, tList list);

// Función: insertItem.
// Objetivo:Inserta un elemento en la lista antes de la posición indicada. Si la posición es LNULL, entonces se añade al final. Devuelve un valor true si el elemento fue insertado; false en caso contrario.
// Entradas: tItemL d(item d de tipo tItemL),
//           tList *L(puntero de referencia L de tipo tList).
// Salidas: true (si el elemento fue insertado),
//          false (si el elemento no fue insertado).
// Precondiciones: Ninguna.
// Postcondiciones: Las posiciones de los elementos de la lista posteriores a la del elemento insertado pueden haber variado.
bool insertItem(tItemL item, tList *list);

// Función: deleteAtPosition.
// Objetivo: Elimina de la lista el elemento que ocupa la posición indicada.
// Entradas: tPosL pos (posicion pos de tipo tPosL),
//           tList *list (puntero de referencia list de tipo tList).
// Salidas : ninguna.
// Precondiciones: La posición indicada es una posición válida en la lista y la consola en dicha posición tiene una pila de pujas vacía.
// Postcondiciones: Las posiciones de los elementos de la lista posteriores a la del elemento eliminado pueden haber variado.
void deleteAtPosition(tPosL p, tList *list);

// Función: getItem.
// Objetivo: Devuelve el contenido del elemento que ocupa la posición indicada.
// Entradas: tPosL pos (posicion pos de tipo tPosL),
//           tList list (Lista list de tipo tList).
// Salidas: p->data (datos de la posicion p de la Lista).
// Precondiciones: La posición indicada es una posición válida en la lista.
// Postcondiciones: Ninguna.
tItemL getItem(tPosL p, tList list);

// Función: updateItem.
// Objetivo: Modifica el contenido del elemento situado en la posición indicada.
// Entradas: tItemL item (item item de tipo tItemL),
//           tPosL pos (posicion pos de tipo tPosL),
//           tList *list (puntero de referencia list de tipo tList).
// Salidas: ninguna.
// Precondiciones: La posición indicada es una posición válida en la lista.
// Postcondiciones: El orden de los elementos de la lista no se ve modificado.
void updateItem(tItemL item, tPosL pos, tList *list);

// Función: findItem.
// Objetivo: Devuelve la posición del primer elemento de la lista cuyo id de consoola se corresponda con el indicado (o LNULL si no existe tal elemento)
// Entradas: tConsoleId consoleId (id de la consola de tipo tConsoleId),
//           tList list (Lista list de tipo tList).
// Salidas: LNULL
//          pos (posicion de tipo tPosL)
// Precondiciones: Ninguna.
// Postcondiciones: Ninguna.
tPosL findItem(tConsoleId consoleId, tList list);

#endif
