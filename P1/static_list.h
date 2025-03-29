/*
* TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Tiago da Costa Teixeira Veloso e Volta LOGIN 1: tiago.velosoevolta
 * AUTHOR 2: Jaime Martínez Váquez  LOGIN 2: j.mvazquez
 * GROUP: 3.3
 * DATE: 03/ 03 / 2025
 */

#ifndef STATIC_LIST_H
#define STATIC_LIST_H

#include "types.h"

#define LNULL -1 //Constante usada para indicar posiciones nulas
#define MAX_LIST 25  //Tamaño máximo de la lista

//Tipo de dato para la posicion de uin elemento de la lista
typedef int tPosL;

//Estructura de la lista
typedef struct {
    tItemL data[MAX_LIST];   //Item de la lista
    tPosL lastPos;            //Ultima posición de la lista
}tList;

//Función: createEmptyList.
// Objetivo: Crea una lista vacía.
// Entradas:tList *L(puntero del tipo tList).
// Salidas: ninguna.
// Precond: ninguna.
// Postcond: La lista queda inicializada y no contiene elementos.
void createEmptyList(tList* list);

//Función: isEmptyList.
// Objetivo:Determina si la lista está vacía.
// Entradas:tList L(Lista L de tipo tList).
// Salidas: true/false.
// Precond:ninguna.
// Postcond: ninguna.
bool isEmptyList(tList list);

//Función: first.
// Objetivo:Devuelve la posición del primer elemento de la lista.
// Entradas: tList L(Lista L de tipo tList).
// Salidas: primera posicion valida de la lista
// Precond: La lista no está vacía.
// Postcond: ninguna
tPosL first(tList list);

//Función: last.
// Objetivo: Devuelve la posición del último elemento de la lista.
// Entradas: tList L(Lista L de tipo tList).
// Salidas: L.lastPos
// Precond: La lista no está vacía.
// Postcond: ninguna.
tPosL last(tList list);

//Función: next.
// Objetivo: Devuelve la posición en la lista del elemento siguiente al de la posición indicada (o LNULL si la posición no tiene siguiente).
// Entradas: tPosL P(posicion P de tipo tPosL), tList L(Lista L de tipo tList).
// Salidas: LNULL/posicion siguiente a P.
// Precond:La posición indicada es una posición válida en la lista.
// Postcond: ninguna
tPosL next(tPosL p, tList list);

//Función: previous.
// Objetivo: Devuelve la posición en la lista del elemento anterior al de la posición indicada (o LNULL si la posición no tiene anterior).
// Entradas: tPosL P(posicion P de tipo tPosL), tList L(Lista L de tipo tList).
// Salidas: LNULL/posicion anterior a P
// Precond: La posición indicada es una posición válida en la lista.
// Postcond: ninguna
tPosL previous(tPosL p, tList list);

//Función: insertItem.
// Objetivo:Inserta un elemento en la lista antes de la posición indicada. Si la posición es LNULL, entonces se añade al final. Devuelve un valor true si el elemento fue insertado; false en caso contrario.
// Entradas: tItemL d(item d de tipo tItemL),tPosL P(posicion P de tipo tPosL), tList *L(puntero de referencia L de tipo tList).
// Salidas: true/false
// Precond: La posición indicada es una posición válida en la lista o bien nula (LNULL)
// Postcond: Las posiciones de los elementos de la lista posteriores a la del elemento insertado pueden haber variado.
bool insertItem(tItemL item, tPosL p, tList *list);

//Función: deleteAtPosition.
// Objetivo: Elimina de la lista el elemento que ocupa la posición indicada.
// Entradas: tPosL P(posicion P de tipo tPosL), tList *L(puntero de referencia L de tipo tList).
// Salidas : ninguna.
// Precond: La posición indicada es una posición válida en la lista.
// Postcond: Las posiciones de los elementos de la lista posteriores a la de la posición eliminada pueden haber variado.
void deleteAtPosition(tPosL p, tList *list);

//Función: getItem.
// Objetivo: Devuelve el contenido del elemento que ocupa la posición indicada.
// Entradas: tPosL P(posicion P de tipo tPosL), tList L(Lista L de tipo tList).
// Salidas: L.data[p](datos de la posicion p de la Lista).
// Precond: La posición indicada es una posición válida en la lista.
// Postcond: ninguna.
tItemL getItem(tPosL p, tList list);

//Función: updateItem.
// Objetivo: Modifica el contenido del elemento situado en la posición indicada.
// Entradas: tItemL d(item d de tipo tItemL),tPosL P(posicion P de tipo tPosL), tList *L(puntero de referencia L de tipo tList).
// Salidas: ninguna.
// Precond: La posición indicada es una posición válida en la lista.
// Postcond: El orden de los elementos de la lista no se ve modificado.
void updateItem(tItemL item, tPosL p, tList *list);

//Función: findItem.
// Objetivo: Devuelve la posición del primer elemento de la lista cuya la id de consola se corresponda con el indicado (o LNULL si no existe tal elemento)
// Entradas: tUserName d (usuario d de tipo tUserName) tList L(Lista L de tipo tList).
// Salidas: LNULL/i(posicion de tipo tPosL)
// Precond: ninguna.
// Postcond: ninguna.
tPosL findItem(tConsoleId consoleId, tList list);


#endif
