#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

#include "algorithms.h"
#include "ga.h"
#include "types.h"
#include "helpers.h"

#define PI 3.142857

static inline float equation(int x)
{
    float v = PI * x;
    float v2 = v / 256;

    return sin(v2);
}

float maximize_function_fitness(const char *genome)
{
    return equation(bstoi(genome));
}

static int uniques(int *a, int n)
{
    int i, j, count = 1;
    for (i = 1; i < n; i++)
    {
        for (j = 0; j < i; j++)
        {
            if (a[i] == a[j])
            {
                break;
            }
        }
        if (i == j)
        {
            count++;
        }
    }
    return count;
}

float eight_queen_fitness(const char *genome)
{
    float fitness = 28.0;

    int aux[8];
    
    for (int i = 0; i < 8; i++)
    {
        int pos = genome[i] - '0';
        aux[i] = pos;
    }

    int rc = 8 - uniques(aux, 8);
    fitness -= (float)rc;

    for (int i = 0; i < 8; i++)
    {
        for (int j = i; j < 8; j++)
        {
            if (i != j)
            {
                int x = abs(i - j);
                int y = abs(aux[i] - aux[j]);
                if (x == y)
                {
                    fitness -= 1.0;
                }
            }
        }
    }    
    return fitness;
}