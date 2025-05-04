/*
* TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Tiago da Costa Teixeira Veloso e Volta LOGIN 1: tiago.velosoevolta
 * AUTHOR 2: Jaime Martínez Váquez  LOGIN 2: j.mvazquez
 * GROUP: 3.3
 * DATE: 01/ 05 / 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "console_list.h"
#include "bid_stack.h"

#define MAX_BUFFER 255


//Función: stringToBrand
//Objetivo: Convertir un char* a un tConsoleBrand
//Entrada: el tipo tConsoleBrand a transformar
//Salida: tConsoleBrand con la equivalencia (nintendo o sega)
//        o -1 como valor de error si no existe
tConsoleBrand stringToBrand(char* consoleBrand){
    if(strcmp(consoleBrand, "nintendo") == 0)
        return nintendo;
    if(strcmp(consoleBrand, "sega") == 0)
        return sega;
    return -1;
}

//Función: new
//Objetivo: Añadir una nueva consola a la lista
//Entradas: tList *list(lista de consolas)
//          char *consoleId(identificador de la consola)
//          char *seller(vendedor de la consola)
//          char *consoleBrand(marca de la consola)
//          char *consolePrice(precio de la consola)
//Salidas: se añade una nueva consola a la lista
//Precond: La lista debe estar inicializada
//Postcond: La lista se verá modificada
void New(tList *list, char* consoleId, char* seller, char* consoleBrand, char* consolePrice) {//se usa char* para luego poder usar funciones como strcmp
    tPosL p; tItemL titem;  //p para manejar posiciones en la lista y titem para manejar los datos del elemento

    //verificamos si la consola ya esta en la lista
    p=findItem(consoleId, *list); //con un puntero porque asi desreferenciamos el puntero y tenemos lo que findItem espera recibir que es un tList
    if (p != LNULL) { //si esta en la lista, error
        printf("+ Error: New not possible\n");
        return;
    }

    //inicializamos los datos de la nueva consola
    strcpy(titem.consoleId, consoleId);  //su correspondiente identificador de consolas
    strcpy(titem.seller, seller);  //identificador de usuario de su vendedor
    titem.consoleBrand = stringToBrand(consoleBrand);  //su marca
    titem.consolePrice = atof(consolePrice);  //su precio (atof convierte un string a float, porque usamos char arriba)
    titem.bidCounter = 0;  //el contador de pujas inicializado a 0
    createEmptyStack(&titem.bidStack); //se le asocia una nueva pila de pujas vacia

    //verificamos si la marca es válida y si se puede insertar, e insertamos
    if ((titem.consoleBrand != nintendo && titem.consoleBrand != sega) || !insertItem(titem, list)) {
        printf("+ Error: New not possible\n");
    } else {
        printf("* New: console %s seller %s brand %s price %.2f\n", consoleId, seller, consoleBrand, atof(consolePrice));
    }

}

//Función: bid
//Objetivo: Pujar por una consola
//Entradas: tList *list(lista de consolas)
//          char *consoleId(identificador de la consola)
//          char *bidder(pujador)
//          char *consolePrice(precio de la consola)
//Salidas: se anade la nueva puja a la pila
//         se actualiza el contador de pujas
//Precond: La lista debe estar inicializada
//Postcond: La lista se verá modificad
void Bid(tList *list, char *consoleId, char *userId, char *consolePrice) {
    tPosL p; tItemL titem;
    tItemS bid;  //estructura de la puja
    float newBidPrice = atof(consolePrice);  //convierte el precio de la puja a float

    //buscamos el elemento
    p = findItem(consoleId, *list);

    //verificamos si existe la consola
    if (p == LNULL) {
        //si no existe, error
        printf("+ Error: Bid not possible\n");
        return;
    }

    //obtenemos el elemento
    titem = getItem(p, *list);

    //calculamos el precio actual (precio original o de la puja más alta)
    float precioActual = titem.bidCounter > 0 ? peek(titem.bidStack).consolePrice : titem.consolePrice;  //si hay por lo menos una puja, obtenemos el precio de la puja más alta con el peek, sino el precio original

    //verificamos si el vendedor es el mismo que el pujador o si el precio de la nueva puja no es superior al precio actual, si se verifica uno, error
    if (strcmp(titem.seller, userId) == 0 || newBidPrice <= precioActual) {
        printf("+ Error: Bid not possible\n");
        return;
    }

    //creamos la nueva puja
    strcpy(bid.bidder, userId);  //identificador del pujador
    bid.consolePrice = newBidPrice;  //precio de la puja

    //anadimos la puja a la pila y se actualiza el contador de pujas
    if (push(bid, &(titem.bidStack))) {
        titem.bidCounter++;
        updateItem(titem,p , list);
        printf("* Bid: console %s bidder %s brand %s price %.2f bids %d\n", titem.consoleId, userId, titem.consoleBrand == nintendo ? "nintendo" : "sega", newBidPrice, titem.bidCounter);
    }

}

//Función: stats
//Objetivo: Imprimir las estadisticas de las consolas
//Entradas: tList *list(lista de consolas)
//Salidas: se imprimen las estadisticas de las consolas
//Precond: La lista debe estar inicializada
//Postcond: La lista no se verá modificada
void Stats(tList *list) {
    tPosL p;
    tItemL titem, maxItem;  //maxItem para guardar la consola con el mayor incremento porcentual
    tItemS topBid;  //puja más alta

    //inicializamos todas las variables
    int nintendoConsoles = 0, segaConsoles = 0;
    float nintendoSumPrices = 0, segaSumPrices = 0;
    float nintendoAvgPrice = 0, segaAvgPrice = 0;
    float incremento = 0, incrementoMAX = 0;

    //verificamos si la lista esta vacia
    if (isEmptyList(*list)) {
        printf("+ Error: Stats not possible\n");
        return;
    }

    //recorremos toda la lista
    for (p = first(*list); p != NULL; p = next(p, *list)) {
        titem = getItem(p, *list);

        //verificamos si la consola tiene pujas
        if (titem.bidCounter > 0) {
            topBid = peek(titem.bidStack); //obtenemos la puja mas alta
            printf("Console %s seller %s brand %s price %.2f bids %d top bidder %s\n", titem.consoleId, titem.seller, titem.consoleBrand == nintendo ? "nintendo" : "sega", titem.consolePrice, titem.bidCounter, topBid.bidder);

            //calcualamosel incremento en porcentaje
            incremento = (topBid.consolePrice - titem.consolePrice) / titem.consolePrice * 100;

            //verificamos si es el mayor incremento, si lo es, lo guardamos
            if (incremento > incrementoMAX) {
                incrementoMAX = incremento;
                maxItem = titem;
            }
        } else {
            //si no hay pujas, se imprime el mensaje
            printf("Console %s seller %s brand %s price %.2f. No bids\n", titem.consoleId, titem.seller, titem.consoleBrand == nintendo ? "nintendo" : "sega", titem.consolePrice);
        }
        //contamos y sumamos los precios de las consolas de cada marca
        if (titem.consoleBrand == nintendo) {
            nintendoConsoles++;
            nintendoSumPrices += titem.consolePrice;
        }else if (titem.consoleBrand == sega) {
            segaConsoles++;
            segaSumPrices += titem.consolePrice;
        }
    }

    //calculamos el precio medio
    nintendoAvgPrice = (nintendoConsoles > 0) ? ((float)nintendoSumPrices / (float)nintendoConsoles) : 0;   //(nintendoConsoles > 0) ? haz con que no haya division por 0, asegura que haya al menos una consola
    segaAvgPrice = (segaConsoles > 0) ? ((float)segaSumPrices / (float)segaConsoles) : 0;

    //imprimimos las stats de las consolas
    printf("\nBrand     Consoles    Price  Average\n");
    printf("Nintendo  %8d %8.2f %8.2f\n", nintendoConsoles, nintendoSumPrices, nintendoAvgPrice);
    printf("Sega      %8d %8.2f %8.2f\n", segaConsoles, segaSumPrices, segaAvgPrice);

    //imprimimos la puja con el mayor incremento
    if (incrementoMAX > 0) {
          topBid = peek(maxItem.bidStack);
          printf("Top bid: console %s seller %s brand %s price %.2f bidder %s top price %.2f increase %.2f%%\n", maxItem.consoleId, maxItem.seller, maxItem.consoleBrand == nintendo ? "nintendo" : "sega", maxItem.consolePrice, topBid.bidder, topBid.consolePrice, incrementoMAX);
    }else
        printf("Top bid not possible\n");
}

//Función: delete
//Objetivo: Eliminar una consola de la lista, eliminando tambien todas las existentes
//Entradas: tList *list(lista de consolas)
//          char *consoleId(identificador de la consola)
//Salidas: la lista sin la consola eliminada
//Precond: La lista debe estar inicializada
//Postcond: La lista se verá modificada
void Delete(tList *list, char *consoleId){
    tPosL p;
    tItemL titem;

    //buscamos el elemento a eliminar
    if ((p=findItem(consoleId, *list)) != LNULL) {
        titem = getItem(p, *list);
        //eliminamos todas las pujas de la pila antes de eliminar la consola
        while (!isEmptyStack(titem.bidStack))
            pop(&titem.bidStack);
        deleteAtPosition(p, list);
        printf("* Delete: console %s seller %s brand %s price %.2f bids %d\n", titem.consoleId, titem.seller, titem.consoleBrand == nintendo ? "nintendo" : "sega" , titem.consolePrice, titem.bidCounter);
    }else
        printf("+ Error: Delete not possible\n");
}

//Función: award
//Objetivo: Buscar una consola que ha sido vendida y eliminarla de la lista
//Entradas: tList *list(lista de consolas)
//          char *consoleId(identificador de la consola)
//Salidas: la lista sin la consola vendida
//Precond: La lista debe estar inicializada
//Postcond: La lista se verá modificada
void Award(tList *list, char *consoleId) {
    tPosL p;
    tItemL titem;
    tItemS topBid;

    //buscamos la consola
    p = findItem(consoleId, *list);
    //verificamos si ya existe la consola
    if (p == LNULL) {
        printf("+ Error: Award not possible\n");
        return;
    }

    titem = getItem(p, *list);

    //verificamos si hay pujas
    if (isEmptyStack(titem.bidStack)) {
        printf("+ Error: Award not possible\n");
        return;
    }

    //obtenemos la puja mas alta
    topBid = peek(titem.bidStack);

    //vaciamos la pila de pujas
    while (!isEmptyStack(titem.bidStack))
        pop(&titem.bidStack);
    //eliminamos la consola de la lista
    deleteAtPosition(p ,list);

    printf("* Award: console %s bidder %s brand %s price %.2f\n", titem.consoleId, topBid.bidder, titem.consoleBrand == nintendo ? "nintendo" : "sega", topBid.consolePrice);

}

//Función: remove
//Objetivo: Eliminar las consolas que no tengan pujas
//Entradas: tList *list(lista de consolas)
//Salidas: la lista sin las consolas sin pujas
//Precond: La lista debe estar inicializada
//Postcond: La lista se verá modificada
void Remove(tList *list) {
    tPosL p;
    tItemL titem;
    int removed = 0; //para saber si se removio alguna consola

    // Verificamos si la lista está vacía
    if (isEmptyList(*list)) {
        printf("+ Error: Remove not possible\n");
        return;
    }

    //recorremos la lista
    for (p = first(*list); p != LNULL; p = next(p, *list)) {
        titem = getItem(p, *list);  //obtenemos el elemento

        //verificamos si la pila de pujas está vacía
        if (titem.bidCounter == 0) {
            printf("Removing console %s seller %s brand %s price %.2f bids %d\n", titem.consoleId, titem.seller, titem.consoleBrand == nintendo ? "nintendo" : "sega", titem.consolePrice, titem.bidCounter);
            //elimianmos la consola
            deleteAtPosition(p, list);
            removed++;
        }
    }

    //si no se removio ninguna consola, error
    if (removed == 0)
        printf("+ Error: Remove not possible\n");
}

//Función: invalidateBids
//Objetivo: Invalidar las pujas de las consolas cuyo numero de pujas sea superior a dos veces la media del numero de pujas de todas las consolas de la lista
//Entradas: tList *list(lista de consolas)
//Salidas: la lista sin las pujas invalidas
//Precond: La lista debe estar inicializada
//Postcond: La lista se verá modificada
void InvalidateBids(tList *list) {
    tPosL p;
    tItemL titem;
    float avgBids = 0;
    int totalConsoles = 0, totalBids = 0;
    bool invalidado = false;  //flag para saber si se ha invalidado

    //verificamos si la lista esta vacia
    if (isEmptyList(*list)) {
        printf("+ Error: InvalidateBids not possible\n");
        return;
    }

    //numero de consolas y el numero total de bids
    for (p =first(*list); p != LNULL; p = next(p, *list)) {
        titem = getItem(p, *list);
        totalConsoles++;
        totalBids += titem.bidCounter;
    }

    //media total
    avgBids = (totalConsoles > 0) ? ((float)totalBids / totalConsoles) : 0;

    //recorremos la lista para invalidar las pujas
    for (p = first(*list); p != LNULL; p = next(p, *list)) {
        titem = getItem(p, *list);
        //invalidamos solo las consolas que cumplen la condicion para eliminar las pujas
        if (titem.bidCounter > 2 * avgBids) {
            //guardamos el numero original de pujas para imprimirlo posteriormente
            int originalBids = titem.bidCounter;
            //vaciamos la pila de pujas
            while (!isEmptyStack(titem.bidStack))
                pop(&titem.bidStack);

            //tenemos que poner el contador de pujas a 0
            titem.bidCounter = 0;
            updateItem(titem, p, list);

            printf("* InvalidateBids: console %s seller %s brand %s price %.2f bids %d average bids %.2f\n", titem.consoleId, titem.seller, titem.consoleBrand == nintendo ? "nintendo" : "sega", titem.consolePrice, originalBids, avgBids);

            //se pone la flag a true porque se invalido por lo menos una consola
            invalidado = true;
        }
    }

    //si no fue posible invalidar por lo menos una consola
    if (!invalidado)
        printf("+ Error: InvalidateBids not possible\n");
}

void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, char *param4, tList *list) {

    printf("********************\n");

    switch (command) {
        case 'N':
            printf("%s %c: console %s seller %s brand %s price %s\n", commandNumber, command, param1, param2, param3, param4);
            New(list, param1, param2, param3, param4);
            break;
        case 'D':
            printf("%s %c: console %s\n", commandNumber, command, param1);
            Delete(list, param1);
            break;
        case 'B':
            printf("%s %c: console %s bidder %s price %s\n", commandNumber, command, param1, param2, param3);
            Bid(list, param1, param2, param3);
            break;
        case 'A':
            printf("%s %c: console %s\n", commandNumber, command, param1);
            Award(list, param1);
            break;
        case 'R':
            printf("%s %c\n", commandNumber, command);
            Remove(list);
            break;
        case 'S':
            printf("%s %c\n", commandNumber, command);
            Stats(list);
            break;
        case 'I':
            printf("%s %c\n", commandNumber, command);
            InvalidateBids(list);
            break;
        default:
            break;
    }
}


void readTasks(char *filename) {

    //inicializamos la lista
    tList list;

    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2, *param3, *param4;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];

    //creamos la lista vacia
    createEmptyList((&list));

    f = fopen(filename, "r");

    if (f != NULL) {



        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);
            param3 = strtok(NULL, delimiters);
            param4 = strtok(NULL, delimiters);

            processCommand(commandNumber, command[0], param1, param2, param3, param4, &list);
        }

        fclose(f);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}


int main(int nargs, char **args) {

    char *file_name = "invalidate.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
        #ifdef INPUT_FILE
        file_name = INPUT_FILE;
        #endif
    }

    readTasks(file_name);

    return 0;
}