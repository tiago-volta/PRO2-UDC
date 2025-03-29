/*
* TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Tiago da Costa Teixeira Veloso e Volta LOGIN 1: tiago.velosoevolta
 * AUTHOR 2: Jaime Martínez Váquez  LOGIN 2: j.mvazquez
 * GROUP: 3.3
 * DATE: 03/ 03 / 2025
 */

#include "dynamic_list.h"

//Crea un nodo
bool createNode(tPosL *pos) {
    *pos = malloc(sizeof(struct tNode));
    return *pos != LNULL;
}

//Crear una lista vacía
void createEmptyList(tList* list) {
    *list = LNULL;
}

//Determina si una lista está vacía
bool isEmptyList(tList list) {
    return list==LNULL;
}

//Posición del primer elemento de la lista
tPosL first(tList list) {
    return list;
}

//Posición del último elemento de la lista
tPosL last(tList list) {
    tPosL pos;
    for(pos = list; pos->next != LNULL; pos = pos->next);
    return pos;
}

//Posición del siguiente elemento en la lista
tPosL next(tPosL pos, tList list) {
    return pos->next;
}

//Posición del previo elemento en la lista
tPosL previous(tPosL pos, tList list) {
    tPosL i;
    if(pos == list) return LNULL; //si la posición es la primera no hay anterior
    else {
        for(i=list;i->next != pos; i = i->next);
        return i;
    }
}

//Insertar un nuevo elemento en la lista
bool insertItem(tItemL item, tPosL pos, tList* list) {
    tPosL i,j;
    if(!createNode(&i))
        return false;
    else {
        i->data = item;
        i->next = LNULL;
        if (isEmptyList(*list)) { //lista vacía
            *list = i;
        }else if(pos == LNULL) { //posicion final en lista no vacia
            for(j=*list; j->next != LNULL; j= j->next);
            j->next = i;
        }else if(pos == *list) { //insertar de primero
            i->next = pos;
            *list = i;
        }else { //caso general (insertar en medio)
            i->next = pos->next;
            pos->next = i;
            i->data = pos->data;
            pos->data = item;
        }
        return true;
    }
}

//Borrar el elemento de la lista en una posición dada
void deleteAtPosition(tPosL pos, tList* list) {
    tPosL i;
    if(pos == *list) { //si primera posición
        *list = (*list)->next;
    }else if(pos->next == LNULL) { //si última posición
        for (i = *list; i->next != pos; i = i->next);
        i->next = LNULL;
    }else {
        i = pos->next;
        pos->data = i->data;
        pos->next = i->next;
        pos = i;
    }
    free(pos); //liberar memoria
}

//Obtener un elemento de una posición dada de la lista
tItemL getItem(tPosL pos, tList list) {
    return pos->data;
}

//Modifica valor de un item en la lista
void updateItem(tItemL item, tPosL pos, tList* list) {
    pos->data = item;
}

//Obtener la posicion de un elemento en la lista
tPosL findItem(tConsoleId consoleId, tList list) {
    tPosL pos;
    if(isEmptyList(list))
      return LNULL; //Si la lista está vacía
    else {
        for(pos = list; strcmp(pos->data.consoleId, consoleId) != 0 && pos->next != LNULL;
            pos = pos->next);
        if(strcmp(pos->data.consoleId, consoleId) != 0)
          pos = LNULL;
        return pos;
    }
}