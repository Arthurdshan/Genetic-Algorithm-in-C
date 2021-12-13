#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <time.h>

#include "algorithms.h"
#include "ga.h"
#include "helpers.h"

char *generate_genome(int size, char (*rand_char)(void))
{
    char *genome = malloc(size + 1);

    for (int i = 0; i < size; i++)
    {
        genome[i] = rand_char();
    }
    genome[size] = '\0';

    return genome;
}

Population *empty_population(int size)
{
    Population *population = malloc(sizeof(Population));
    population->population = malloc(size * sizeof(Individual *));
    population->pop_size = size;

    return population;
}

Population *generate_population(int size, int genome_length, char (*rand_char)(void))
{
    Population *population = empty_population(size);

    population->dna_size = genome_length;

    for (int i = 0; i < size; i++)
    {
        population->population[i] = malloc(sizeof(Individual));
        population->population[i]->genome = generate_genome(genome_length, rand_char);
        population->population[i]->fitness = -1;
    }

    return population;
}

void dealocate_population(Population **population)
{
    Population *pop = *population;

    for (int i = 0; i < pop->pop_size; i++)
    {
        free(pop->population[i]->genome);
        free(pop->population[i]);
    }
    free(pop->population);
    free(pop);
    pop = NULL;
}

Individual *create_individual(const char *genome, float fitness)
{
    Individual *idv = malloc(sizeof(Individual));
    idv->genome = malloc(strlen(genome) + 1);

    idv->fitness = fitness;

    for (int i = 0; i < strlen(genome); i++)
    {
        idv->genome[i] = genome[i];
    }
    idv->genome[strlen(genome)] = '\0';

    return idv;
}

void dealocate_individual(Individual **idv)
{
    Individual *i = *idv;
    free(i->genome);
    free(i);
    i = NULL;
}

Individual *selection(Population *population)
{
    float total_sum = 0;

    for (int i = 0; i < population->pop_size; i++)
    {
        total_sum += population->population[i]->fitness;
    }

    float index = rand() * (total_sum / RAND_MAX);
    float sum = 0;
    int i = 0;

    while (sum < index)
    {
        sum += population->population[i++]->fitness;
    }

    if (i >= population->pop_size)
    {
        i = population->pop_size - 1;
    }

    return create_individual(population->population[i]->genome, population->population[i]->fitness);
}

char **single_point_crossing_over(Individual *p1, Individual *p2, char (*rand_char)(void))
{
    int size = strlen(p1->genome);

    char **offsprings = malloc(2 * sizeof(char *));
    offsprings[0] = malloc(size + 1);
    offsprings[1] = malloc(size + 1);

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < size; j++)
        {
            float p = (float)(rand() % 100) / 100;

            if (p < 0.50)
            {
                offsprings[i][j] = p1->genome[j];
            }
            else if (p < 0.90)
            {
                offsprings[i][j] = p2->genome[j];
            }
            else
            {
                offsprings[i][j] = rand_char();
            }
        }
    }

    offsprings[0][size] = '\0';
    offsprings[1][size] = '\0';

    return offsprings;
}

void mutation(Population *population, char (*rand_char)(void))
{
    int m = rand() % (int)(population->pop_size * population->dna_size);

    for (int i = 0; i < population->pop_size; i++)
    {
        for (int j = 0; j < population->dna_size; j++)
        {
            if ((i * population->dna_size + j) == m)
            {
                population->population[i]->genome[j] = rand_char();
            }
        }
    }
}

void evaluation(Population *population, float (*fitness_func)(const char *genome))
{
    for (int i = 0; i < population->pop_size; i++)
    {
        population->population[i]->fitness = fitness_func(population->population[i]->genome);
    }
}

void genetic_algorithm(
    int population_size,
    int genome_size,
    char (*rand_char)(void),
    float desired_fitness,
    float (*fitness_func)(const char *genome))
{
    srand(time(NULL));

    int generation = 0;

    start_file();

    clock_t time = clock();

    Population *population = generate_population(population_size, genome_size, rand_char);
    evaluation(population, fitness_func);

    while (1)
    {
        merge_sort(population->population, 0, population->pop_size - 1);

        if (compare_float(population->population[0]->fitness, desired_fitness))
        {
            break;
        }

        Population *new_generation = empty_population(population_size);
        new_generation->dna_size = genome_size;

        int elitism_range = (10 * population->pop_size) / 100;

        for (int i = 0; i < elitism_range; i++)
        {
            new_generation->population[i] = create_individual(
                population->population[i]->genome,
                population->population[i]->fitness);
        }

        int k = (90 * population->pop_size) / 100;

        for (int i = (population->pop_size - k) / 2, j = elitism_range; i < (population_size / 2); i++)
        {
            Individual *p1 = selection(population);
            Individual *p2 = selection(population);

            char **offsprings = single_point_crossing_over(p1, p2, rand_char);

            new_generation->population[j++] = create_individual(offsprings[0], -1.0);
            new_generation->population[j++] = create_individual(offsprings[1], -1.0);

            free(offsprings[0]);
            free(offsprings[1]);
            free(offsprings);

            free(p1->genome);
            free(p2->genome);

            free(p1);
            free(p2);
        }
        evaluation(new_generation, fitness_func);

        output_to_file(population, new_generation, generation);

        dealocate_population(&population);
        population = new_generation;

        generation++;
    }

    time = clock() - time;

    printf("\nGenerations: %d\n", generation);
    printf("Time: %lfs\n", ((float)time) / CLOCKS_PER_SEC);
    printf("Best solution: %s\n\n", population->population[0]->genome);

    output_to_file(population, NULL, generation);
    dealocate_population(&population);
}