#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "genetic_algorithm.h"

int main()
{
    genetic_algorithm(8, 8, &random_binary_char, 1.0, &equation_fitness);
}