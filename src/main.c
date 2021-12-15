#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "genetic_algorithm.h"

int main()
{
    Options option;
    int size;

start:
    printf("Chose an option:\n");
    printf("0. Eight queens\n");
    printf("1. Maximize a math function\n");
    scanf("%d", &option);

    printf("Insert the population size:");
    scanf("%d", &size);

    if (size < 0 || size % 2 != 0)
        goto start;

    switch (option)
    {
    case QUEENS:
        genetic_algorithm(size, 8, 28.0, option, &random_char_eight_queens, &eight_queen_fitness);
        break;

    case MAXIMIZE:
        genetic_algorithm(size, 8, 1.0, option, &random_binary_char, &maximize_function_fitness);
        break;

    default:
        goto start;
    }
}