#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "genetic_algorithm.h"

int main()
{
    genetic_algorithm(100, 10, &random_binary_char, &fitness);
}