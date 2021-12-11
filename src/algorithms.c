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

char random_char()
{
    const char *charset = "abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ 1234567890, .-;:_!\"#&/()=?@${[]}";

    int len = strlen(charset);

    return charset[rand() % len];
}

int fitness(const char *genome, const char *target)
{
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