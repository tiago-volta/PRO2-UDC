/*
* TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Tiago da Costa Teixeira Veloso e Volta LOGIN 1: tiago.velosoevolta
 * AUTHOR 2: Jaime Martínez Váquez  LOGIN 2: j.mvazquez
 * GROUP: 3.3
 * DATE: 03/ 03 / 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#define MAX_BUFFER 255

#ifdef DYNAMIC_LIST
#include "dynamic_list.h"
#endif
#ifdef STATIC_LIST
#include "static_list.h"
#endif

/*Función: Transformar
 *Objetivo: Convertir la categoria de tipo tConsoleBrand en un char
 *Entradas: tConsoleBrand consoleBrand(marca de la consola)
 *Salidas: char(nintendo/sega)
 *Precond: Introducir un tConsoleBrand válido.
 *Postcond: ninguna.
 */
const char *transformar(tConsoleBrand consoleBrand){
    if(consoleBrand == nintendo)
        return "nintendo";
    else
        return "sega";
}

/*Función: stringToBrand
 *Objetivo: Pasa a tipo tConsoleBrand a un char*
 *Entrada: category el string a transformar
 *Salida: tConsoleBrand con la equivalencia o -1 si no existe
 */
tConsoleBrand stringToBrand(char* consoleBrand){
    if(strcmp(consoleBrand, "nintendo") == 0)
        return nintendo;
    if(strcmp(consoleBrand, "sega") == 0)
        return sega;
    return -1;
}

/*Función: new
 *Objetivo: Añadir una nueva consola a la lista
 *Entradas: tList *list(lista de consolas), char *consoleId(identificador de la consola), char *seller(vendedor de la consola), char *consoleBrand(marca de la consola), char *consolePrice(precio de la consola)
 *Salidas: se añade una nueva consola a la lista
 *Precond: La lista debe estar inicializada
 *Postcond: La lista se verá modificada
 */
void new(tList *list, char *consoleId, char *seller, char *consoleBrand, char *consolePrice) {
    tPosL pos;
    tItemL titem;

    //si la consola ya esta en la lista
    pos = findItem(consoleId, *list);
    if (pos != LNULL) {
        printf("+ Error: New not possible\n");
        return;
    }

    //incicializamos los datos de la nueva consola
    strcpy(titem.consoleId, consoleId);
    strcpy(titem.seller, seller);
    titem.consoleBrand = stringToBrand(consoleBrand);
    titem.consolePrice = atof(consolePrice);
    titem.bidCounter = 0;

    //insertamos el nuevo elemento
    if (insertItem(titem, LNULL, list)) {
        printf("* New: console %s seller %s brand %s price %.2f\n", titem.consoleId, titem.seller, titem.consoleBrand == nintendo ? "nintendo" : "sega", titem.consolePrice);

    //si no es posible insertar el nuevo elemento, mostramos un error
    }else
        printf("Error: New not possible\n");
}

/*Función: delete
 *Objetivo: Eliminar una consola de la lista
 *Entradas: tList *list(lista de consolas), char *consoleId(identificador de la consola)
 *Salidas: se elimina la consola de la lista
 *Precond: La lista debe estar inicializada
 *Postcond: La lista se verá modificada
 */
void delete(tList *list, char *consoleId){
    tPosL pos;
    tItemL titem;

    //si lo encontramos eliminamos
    if ((pos =findItem(consoleId, *list)) != LNULL) {
        titem = getItem(pos, *list);
        deleteAtPosition(pos, list);
        printf("* Delete: console %s seller %s brand %s price %.2f bids %d\n",titem.consoleId, titem.seller, titem.consoleBrand == nintendo ? "nintendo" : "sega", titem.consolePrice, titem.bidCounter);
    }else
        printf("+ Error: Delete not possible\n");
}

/*Función: bid
 *Objetivo: Pujar por una consola
 *Entradas: tList *list(lista de consolas), char *consoleId(identificador de la consola), char *bidder(pujador), char *consolePrice(precio de la consola)
 *Salidas: se actualiza la puja de la consola
 *Precond: La lista debe estar inicializada
 *Postcond: La lista se verá modificada
 */
void bid(tList *list, char *consoleId, char *bidder, char *consolePrice) {
    tPosL pos;
    tItemL titem;
    float newprice;
    newprice = atof(consolePrice);

    //buscamos el elemento a eliminar
    pos = findItem(consoleId, *list);

    //si existe el producto, error
    if (pos == LNULL) {
        printf("+ Error: Bid not possible\n");
        return;
    }
    //obtenemos el elemento
    titem = getItem(pos, *list);

    //verificamos si el vendedor es el mismo que el pujador o si el precio de la puja no es superior al precio actual, si se verifica uno, error
    if (strcmp(titem.seller, bidder) == 0 || newprice <= titem.consolePrice) {
        printf("+ Error: Bid not possible\n");
        return;
    }

    //actualizamos el contador de pujas y el precio de la consola
    titem.consolePrice = newprice;
    titem.bidCounter ++;

    //actualizamos el elemento en la lista
    updateItem(titem, pos, list);

    printf("* Bid: console %s seller %s brand %s price %.2f bids %d\n", titem.consoleId, titem.seller, titem.consoleBrand == nintendo ? "nintendo" : "sega", titem.consolePrice, titem.bidCounter);

}

/*Función: stats
 *Objetivo: Mostrar las estadísticas de las consolas
 *Entradas: tList *list(lista de consolas)
 *Salidas: se muestran las estadísticas de las consolas
 *Precond: La lista debe estar inicializada
 *Postcond: ninguna
 */
void stats(tList *list) {
    tPosL pos;
    tItemL titem;
    //variables para las stats
    int nintendoConsoles = 0, segaConsoles = 0;
    float nintendoSumPrices = 0, segaSumPrices = 0;
    float nintendoAvgPrice = 0, segaAvgPrice = 0;

    //verificamos si la lista esta vacia, si esta, error
    if (isEmptyList(*list)) {
        printf("+ Error: Stats not possible\n");
        return;
    }

    //imprimimos los elementos de la lista
    for (pos = first(*list); pos != LNULL; pos = next(pos, *list)) {
        titem = getItem(pos, *list);
        printf("Console %s seller %s brand %s price %.2f bids %d\n", titem.consoleId, titem.seller, titem.consoleBrand == nintendo ? "nintendo" : "sega", titem.consolePrice, titem.bidCounter);

        //contamos y sumamos los precios de las consolas de cada marca
        if (titem.consoleBrand == nintendo) {
            nintendoConsoles++;
            nintendoSumPrices += titem.consolePrice;
        } else if (titem.consoleBrand == sega) {
            segaConsoles++;
            segaSumPrices += titem.consolePrice;
        }
    }

    //calculamos el precio medio
    nintendoAvgPrice = (nintendoConsoles > 0) ? ((float)nintendoSumPrices / (float)nintendoConsoles) : 0;   //(nintendoConsoles > 0) ? haz con que no haya division por 0
    segaAvgPrice = (segaConsoles > 0) ? ((float)segaSumPrices / (float)segaConsoles) : 0;

    //imprimimos las stats de las consolas
    printf("\nBrand     Consoles    Price  Average\n");
    printf("Nintendo  %8d %8.2f %8.2f\n", nintendoConsoles, nintendoSumPrices, nintendoAvgPrice);
    printf("Sega      %8d %8.2f %8.2f\n", segaConsoles, segaSumPrices, segaAvgPrice);
}

/*Función: processCommand
 *Objetivo: Procesar los comandos de entrada y llamar a las funciones correspondientes
 *Entradas: char *commandNumber(número del comando), char command(comando), char *param1(primer parámetro), char *param2(segundo parámetro), char *param3(tercer parámetro), char *param4(cuarto parámetro), tList *list(lista de consolas)
 *Precond: La lista debe estar inicializada
 *Postcond: Se llamará a la función correspondiente
 */
void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, char *param4, tList *list) {

    printf("********************\n");

    switch (command) {
        case 'N':
            printf("%s %c: console %s seller %s brand %s price %s\n", commandNumber, command, param1, param2, param3, param4);
            new(list, param1, param2, param3, param4);
        break;
        case 'D':
            printf("%s %c: console %s\n", commandNumber, command, param1);
            delete(list, param1);
        break;
        case 'B':
            printf("%s %c: console %s bidder %s price %s\n", commandNumber, command, param1, param2, param3);
            bid(list, param1, param2, param3);
        break;
        case 'S':
            printf("%s %c\n", commandNumber, command);
            stats(list);
        break;
        default:
            printf("Command: %s %c is not recognized\n", commandNumber, command);
        break;
    }
}

/*Función: readTasks
 *Objetivo: Leer cada linea de los ficheros y procesar los comandos en ellas
 *Entradas: char *filename(nombre del fichero)
 */
void readTasks(char *filename) {
    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2, *param3, *param4;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];

    f = fopen(filename, "r");
    //creamos la lista
    tList list;
    createEmptyList(&list);

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

    char *file_name = "new.txt";

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






