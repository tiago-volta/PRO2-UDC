/*TITLE: PROGRAMMING II LABS                   SUBTITLE: P0

AUTHOR 1: Tiago da Costa Teixeira Veloso e Volta   LOGIN 1: tiago.velosoevolta

AUTHOR 2: Jaime Martínez Váquez   LOGIN 2: j.mvazquez

 GROUP: 3.3                                                            DATE: 09/02/2025
*/
#include "rational_pointer.h"
#include <stdlib.h>

// Operacion para crear un racional
Rational createRational(int n, int d) {
    Rational temp;
    temp= malloc(sizeof(*temp));
    temp->num= n;
    temp->den= d;
    return temp;
}

// Operacion que retorna el numerador de un racional
int numerator(Rational r) {
    return r->num;
}

// Operacion que retorna el denominador de un racional
int denominator(Rational r) {
    return r->den;
}

// Operacion que retorna la suma de dos racionales
Rational sum(Rational r1, Rational r2) {
    Rational s;
    s= malloc(sizeof(*s));
    s->num= r1->num * r2->den + r2->num * r1->den;
    s->den= r1->den * r2->den;
    return s;
}
