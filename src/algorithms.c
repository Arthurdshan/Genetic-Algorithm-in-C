#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

#include "algorithms.h"
#include "ga.h"
#include "types.h"
#include "helpers.h"

char random_binary_char()
{
    int n = rand() % 2;
    return n == 0 ? '0' : '1';
}

int fitness(const char *genome)
{
    const char *target = "1001100101";

    int fit = 0;

    for (int i = 0; i < strlen(genome); i++)
    {
        if (genome[i] != target[i])
        {
            fit++;
        }
    }

    return fit;
}