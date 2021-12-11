#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "genetic_algorithm.h"

int main()
{
    const char *target = "I love learning new things such as genetic algorithms";

    genetic_algorithm(1000, target, &random_char, &fitness);
}