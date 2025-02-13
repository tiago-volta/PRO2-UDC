/*TITLE: PROGRAMMING II LABS                   SUBTITLE: P0

AUTHOR 1: Tiago da Costa Teixeira Veloso e Volta   LOGIN 1: tiago.velosoevolta

AUTHOR 2: Jaime Martínez Váquez   LOGIN 2: j.mvazquez

 GROUP: 3.3                                                            DATE: 09/02/2025
*/
#ifndef RATIONAL_POINTER_H
#define RATIONAL_POINTER_H

typedef struct Data* Rational;
struct Data {
    int num;
    int den;
};

Rational createRational(int n, int d);
int numerator(Rational r);
int denominator(Rational r);
Rational sum(Rational r1, Rational r2);

#endif // RATIONAL_POINTER_H
