#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "algorithms.h"
#include "types.h"
#include "helpers.h"
#include "ga.h"

static void merge(Individual **array, int initial_position, int middle, int final_position)
{
    int i, j, k;

    int left_quantity = middle - initial_position + 1;
    int right_quantity = final_position - middle;

    Individual **left = malloc((left_quantity + 1) * sizeof(Individual *));
    Individual **right = malloc((right_quantity + 1) * sizeof(Individual *));

    for (i = 0; i < left_quantity; i++)
    {
        left[i] = create_individual(
            array[initial_position + i]->genome,
            array[initial_position + i]->fitness);
    }

    for (j = 0; j < right_quantity; j++)
    {
        right[j] = create_individual(
            array[middle + 1 + j]->genome,
            array[middle + 1 + j]->fitness);
    }

    left[left_quantity] = right[right_quantity] = create_individual("sentinel", INT_MAX);

    i = j = 0;

    for (k = initial_position; k <= final_position; k++)
    {
        if (left[i]->fitness <= right[j]->fitness)
        {
            dealocate_individual(&array[k]);
            array[k] = create_individual(
                left[i]->genome,
                left[i]->fitness);
            i++;
        }
        else
        {
            dealocate_individual(&array[k]);
            array[k] = create_individual(
                right[j]->genome,
                right[j]->fitness);
            j++;
        }
    }
}

void merge_sort(Individual **array, int left, int right)
{
    int middle = 0;
    if (left < right)
    {
        middle = ((left + right) / 2);
        merge_sort(array, left, middle);
        merge_sort(array, middle + 1, right);
        merge(array, left, middle, right);
    }
}

void start_file()
{
    FILE *f = fopen("data.txt", "w+");
    fclose(f);
}

void output_to_file(Population *population, Population *new_population, int generation)
{
    FILE *f = fopen("data.txt", "a+");

    if (f == NULL)
        exit(1);

    fprintf(f, "GENERATION: %d\n\n", generation);

    for (int i = 0; i < population->pop_size; i++)
    {
        fprintf(f, "DNA: %s\t Fitness:%d\n", population->population[i]->genome, population->population[i]->fitness);
    }

    fprintf(f, "\n");

    if (new_population != NULL)
    {
        fprintf(f, "AFTER CROSSING OVER\n\n");

        for (int i = 0; i < new_population->pop_size; i++)
        {
            fprintf(f, "DNA: %s\t Fitness:%d\n", new_population->population[i]->genome, new_population->population[i]->fitness);
        }

        fprintf(f, "\n");
    }
    else
    {
        fprintf(f, "Perfect genome encountered at generation: %d\n", generation);
    }

    fclose(f);
}