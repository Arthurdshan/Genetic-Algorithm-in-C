#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
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

Individual *create_individual(const char *genome, int fitness)
{
    Individual *idv = malloc(sizeof(Individual));
    idv->genome = malloc(strlen(genome) + 1);

    strcpy(idv->genome, genome);
    idv->fitness = fitness;

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
    int total_sum = 0;

    for (int i = 0; i < population->pop_size; i++)
    {
        total_sum += population->population[i]->fitness;
    }

    int index = rand() % total_sum;
    int sum = 0;
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

char **single_point_crossing_over(Individual *p1, Individual *p2)
{
    int size = strlen(p1->genome);

    char **offsprings = malloc(2 * sizeof(char *));
    offsprings[0] = malloc(size + 1);
    offsprings[1] = malloc(size + 1);

    int point = rand() % size;

    if (point == 0)
    {
        point++;
    }

    for (int i = 0; i < point; i++)
    {
        offsprings[0][i] = p1->genome[i];
        offsprings[1][i] = p2->genome[i];
    }

    for (int i = point; i < size; i++)
    {
        offsprings[0][i] = p2->genome[i];
        offsprings[1][i] = p1->genome[i];
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

void evaluation(Population *population, int (*fitness_func)(const char *genome))
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
    int (*fitness_func)(const char *genome))
{
    srand(time(NULL));

    int generation = 0;

    start_file();

    Population *population = generate_population(population_size, genome_size, rand_char);
    evaluation(population, fitness_func);

    while (1)
    {
        merge_sort(population->population, 0, population->pop_size - 1);

        if (population->population[0]->fitness == 0)
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

            char **offsprings = single_point_crossing_over(p1, p2);

            new_generation->population[j++] = create_individual(offsprings[0], -1);
            new_generation->population[j++] = create_individual(offsprings[1], -1);

            free(offsprings[0]);
            free(offsprings[1]);
            free(offsprings);

            free(p1->genome);
            free(p2->genome);

            free(p1);
            free(p2);
        }

        mutation(new_generation, rand_char);
        evaluation(new_generation, fitness);

        output_to_file(population, new_generation, generation);

        dealocate_population(&population);
        population = new_generation;

        generation++;
    }

    printf("Best fitting genome encountered in generation: %d\n", generation);

    output_to_file(population, NULL, generation);
    dealocate_population(&population);
}