#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "genetic_algorithm.h"

int main()
{
    const char *target = "Estou aprendendo algoritmos geneticos";

    genetic_algorithm(100, target, &random_char, &fitness);
}