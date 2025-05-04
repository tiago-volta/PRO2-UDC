/*
* TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Tiago da Costa Teixeira Veloso e Volta LOGIN 1: tiago.velosoevolta
 * AUTHOR 2: Jaime Martínez Váquez  LOGIN 2: j.mvazquez
 * GROUP: 3.3
 * DATE: 02/ 04 / 2025
 */

#include "bid_stack.h"

//Crea una pila vacía
void createEmptyStack(tStack *stack) {
    stack->top = SNULL;  //inicializa la cima de la pila a SNULL
}

//Inserta un elemento en la cima de la pila.
//Devuelve un valor true si el elemento fue apilado
//false en caso contrario
bool push(tItemS item, tStack *stack) {
    if (stack->top == MAX_PILA - 1)
        return false; //Si la pila está llena
    else {
        stack->top++;  //incrementa el cima de la pila
        stack->data[stack->top] = item;  //inserta el nuevo elemento en la cima
        return true;
    }
}

//Elimina de la pila el elemento situado en la cima
void pop(tStack *stack) {
        stack->top--;  //decrementa la cima de la pila
}

//Recupera el elemento de la cima de la pila sin eliminarlo
tItemS peek(tStack stack) {
    return stack.data[stack.top];  //devuelve el elemento de la cima de la pila
}

//Determina si una pila esta vacia o no
bool isEmptyStack(tStack stack) {
    return stack.top == SNULL;  //devuelve true si la pila está vacía
}