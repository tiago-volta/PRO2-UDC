/*
* TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Tiago da Costa Teixeira Veloso e Volta LOGIN 1: tiago.velosoevolta
 * AUTHOR 2: Jaime Martínez Váquez  LOGIN 2: j.mvazquez
 * GROUP: 3.3
 * DATE: 03/ 03 / 2025
 */

#include "static_list.h"

//Crea una lista vacía
void createEmptyList(tList* list) {
    list->lastPos = LNULL;
}

//Determina si una lista está vacía
bool isEmptyList(tList list) {
    return list.lastPos==LNULL;
}

//Posición del primer elemento de la lista
tPosL first(tList list) {
    return 0;
}

//Posición del último elemento de la lista
tPosL last(tList list) {
    return list.lastPos;
}

//Posición del siguiente elemento en la lista
tPosL next(tPosL pos, tList list) {
    if(pos==list.lastPos)
        return LNULL; //Si última posición
    else
        return ++pos;
}

//Posición del elemento anterior en la lista
tPosL previous(tPosL pos, tList list) {
    if(pos == 0)
        return LNULL; //Si es la primera posicion no hay anterior
    else
        return --pos;
}

//Insertar un nuevo elemento en la lista
bool insertItem(tItemL item, tPosL pos, tList* list) {
    tPosL i;
    if(list->lastPos==MAX_LIST-1)
        return false; //Si la lista está llena
    else {
        list->lastPos++;
        if (pos==LNULL){ //Si se inserta al final
            list->data[list->lastPos] = item;
        }else {
            for(i = list->lastPos; i >=pos; i--) {  //si no inserta al final, mueve todos uno a la derecha para poder insertar
                list->data[i] = list->data[i - 1];
            }
            list->data[pos] = item;
        }
        return true;
    }
}

//Borrar el elemento de la lista en una posición dada
void deleteAtPosition(tPosL pos, tList* list) {
    tPosL i;
    for(i=pos;i <=list->lastPos; i++) {
        list->data[i] = list->data[i + 1]; //mueve todos los elementos uno a la izquierda
    }
    list->lastPos--;
}

//Obtener un elemento de una posición dada de la lista
tItemL getItem(tPosL pos, tList list) {
    return list.data[pos];
}

//Modifica el valor de un item en la lista
void updateItem(tItemL item, tPosL pos, tList* list) {
    list->data[pos]=item;
}

//Obtener la posicion de un elemento en la lista
tPosL findItem(tConsoleId consoleId, tList list) {
    if(isEmptyList(list))
        return LNULL; //Si la lista está vacía
    else {
        for(tPosL pos = first(list); pos <= list.lastPos; pos++) { //recorre la lista
            if(strcmp(list.data[pos].consoleId, consoleId) == 0) {  //compara el id de la consola en la lista con el id de la consola a buscar
                return pos;  //si encuentra, lo devuelve
            }
        }
        return LNULL; //si no se encuentra el elemento
    }
}