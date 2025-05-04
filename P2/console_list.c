/*
* TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Tiago da Costa Teixeira Veloso e Volta LOGIN 1: tiago.velosoevolta
 * AUTHOR 2: Jaime Martínez Váquez  LOGIN 2: j.mvazquez
 * GROUP: 3.3
 * DATE: 02/ 04 / 2025
 */

#include "console_list.h"

// Función: createNode.
// Objetivo: Crear un node con una dirección de memoria correcta.
// Entradas:tPosL *pos (Dirección de memoria de un puntero tipo tPosL)
// Salidas: tPosL *pos con la dirección de memoria asigndada
// Precondiciones: Ninguna.
// Postcondiciones: Ninguna.
bool createNode(tPosL *pos) {
    *pos=malloc(sizeof(struct tNode));  //asigna memoria para un nuevo nodo
    return *pos != LNULL;  //si la asignación de memoria ha sido correcta devuelve true
}

// Función: findPosition.
// Objetivo: Busca la posición en una lista enlazada donde debería insertarse un nuevo elemento para mantener el orden.
// Entradas: tItemL item (datos del item a insertar),
//           tList list (lista de consolas)
// Salidas: tPosL pos (posición donde debería insertarse el nuevo elemento)
// Precondiciones: El elemento debe existir en la lista.
// Postcondiciones: Ninguna.
tPosL findPosition(tItemL item, tList list) {
    tPosL pos;
    pos = list;

    while (pos->next != LNULL && strcmp(pos->next->data.consoleId, item.consoleId) < 0)
        pos = pos->next;  //avanza hasta encontrar la posición correcta
    return pos;
}

//Crear una lista vacía
void createEmptyList(tList* list) {
    *list = LNULL;  //inicializa la lista a LNULL
}

//Determina si una lista está vacía
bool isEmptyList(tList list) {
    return list==LNULL;  //devuelve true si la lista está vacía
}

//Posición del primer elemento de la lista
tPosL first(tList list) {
    return list;  //la primera posicion es la cabeza de la lista
}

//Posición del último elemento de la lista
tPosL last(tList list) {
    tPosL pos;
    for(pos=list; pos->next != LNULL; pos=pos->next);  //avanza hasta el último elemento
    return pos;
}

//Posición del siguiente elemento en la lista
tPosL next(tPosL pos, tList list) {
    return pos->next;  //devuelve la posición siguiente a la indicada
}

//Posición del previo elemento en la lista
tPosL previous(tPosL pos, tList list) {
    tPosL i;
    if(pos==list)
        return LNULL; //si la posición es la primera no hay anterior
    else {
        for(i=list; i->next != pos; i=i->next);  //avanza hasta la posición anterior
        return i;
    }
}

//Insertar un nuevo elemento en la lista
bool insertItem(tItemL item, tList* list) {
    tPosL i,j;

    if(!createNode(&i))
        return false;  //crea un nodo y si no se ha podido crear el nodo, devuelve false
    else {
        i->data = item;
        i->next = LNULL;
        if (isEmptyList(*list)) { //lista vacia
            *list = i;
        }else if(strcmp(item.consoleId, (*list)->data.consoleId) < 0) {
            //insertar al principio
            i->next = *list;
            *list = i;
        }else { //insertar en medio o al final
            j = findPosition(item, *list);  //busca la posición donde insertar el nuevo elemento
            i->next = j->next;
            j->next = i;  //esto inserta el nuevo nuevo nodo i despues de j
        }
        return true;
    }
}

//Borrar el elemento de la lista en una posición dada
void deleteAtPosition(tPosL pos, tList* list) {
    tPosL i;

    if(pos == *list) { //si es la primera posición
        *list = (*list)->next;  //avanza la cabeza de la lista
    }else if(pos->next == LNULL) { //si es la última posición
        for (i = *list; i->next != pos; i = i->next);  //se recoore la lista hasta la posición anterior a la que se quiere borrar
        i->next = LNULL;  //se actualiza el puntero next del nodo anterior para que apunte a LNULL (se borra)
    }else { //si no es ni la primera ni la última posición
        i = pos->next;  //se guarda el nodo siguiente en i
        pos->data = i->data;  //se actualiza los datos del nodo i al nodo pos
        pos->next = i->next;  //se actualiza el puntero next de pos para que apunte al siguiente de i
        pos = i;  //pos se actualiza para que apunte a i
    }
    free(pos); //liberar memoria
}

//Obtener un elemento de una posición dada de la lista
tItemL getItem(tPosL pos, tList list) {
    return pos->data;  //devuelve los datos del nodo en la posición indicada
}

//Modifica valor de un item en la lista
void updateItem(tItemL item, tPosL pos, tList* list) {
    pos->data = item;  //actualiza los datos del nodo en la posición indicada
}

//Obtener la posicion de un elemento en la lista
tPosL findItem(tConsoleId consoleId, tList list) {
    tPosL pos;

    if(isEmptyList(list))
      return LNULL; //Si la lista está vacía
    else {  //busca la posicion del primer elemento que coincida con el consoleId, si no encuentra devuelve LNULL
        for(pos = list; strcmp(pos->data.consoleId, consoleId) < 0 && pos->next != LNULL; pos = pos->next);
        if(strcmp(pos->data.consoleId, consoleId) != 0)
            pos = LNULL;
        return pos;
    }
}
