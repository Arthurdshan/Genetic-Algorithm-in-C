#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "genetic_algorithm.h"

int main()
{
    const char *target = "I like genetic algorithms";

    genetic_algorithm(1000, target, &random_char, (int)strlen(target), &fitness);
}