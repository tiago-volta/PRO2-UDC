/*
* TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Tiago da Costa Teixeira Veloso e Volta LOGIN 1: tiago.velosoevolta
 * AUTHOR 2: Jaime Martínez Váquez  LOGIN 2: j.mvazquez
 * GROUP: 3.3
 * DATE: 03/ 03 / 2025
 */
#ifndef PRO2_2024_P1_TYPES_H
#define PRO2_2024_P1_TYPES_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define NAME_LENGTH_LIMIT 10

//Definición de tipos
typedef char tUserId[NAME_LENGTH_LIMIT];
typedef char tConsoleId[NAME_LENGTH_LIMIT];
typedef enum {nintendo, sega} tConsoleBrand;
typedef float tConsolePrice;
typedef int tBidCounter;

//Definición de estructura
typedef struct tItemL {
    tUserId seller;
    tConsoleId consoleId;
    tConsoleBrand consoleBrand;
    tConsolePrice consolePrice;
    tBidCounter bidCounter;
} tItemL;


#endif

