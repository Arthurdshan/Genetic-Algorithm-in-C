#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <math.h>

#include "algorithms.h"
#include "ga.h"
#include "types.h"
#include "helpers.h"

#define PI 3.142857

char random_binary_char()
{
    int n = rand() % 2;
    return n == 0 ? '0' : '1';
}

char random_char()
{
    const char *charset = "abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ 1234567890, .-;:_!\"#&/()=?@${[]}";

    int len = strlen(charset);

    return charset[rand() % len];
}

static inline float equation(int x)
{
    float v = PI * x;
    float v2 = v / 256;

    return sin(v2);
}

int fitness(const char *genome, const char *target)
{
    int fit = 0;

    for (int i = 0; i < strlen(genome); i++)
    {
        if (genome[i] == target[i])
        {
            fit++;
        }
    }

    return fit;
}

int bstoi(const char *str)
{
    int value = 0;
    int index_counter = 0;

    for (int i = strlen(str) - 1; i >= 0; i--)
    {
        if (str[i] == '1')
        {
            value += pow(2, index_counter);
        }
        index_counter++;
    }
    return value;
}

float equation_fitness(const char *genome)
{
    return equation(bstoi(genome));
}