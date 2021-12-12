/**
 * @file ga.h
 * @author Arthur Han
 * @brief The header file with the ADT for the genetic algorithm implementation.
 * @version 0.1
 * @date 2021-12-10
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef __GA_H__
#define __GA_H__

#include "types.h"

struct individual
{
    char *genome;
    int fitness;
};

struct population
{
    Individual **population;
    int pop_size;
    int dna_size;
};

/**
 * @brief Function that generates a random genome based on the rand_char function
 *
 * @param size Size of the genome to be generated
 * @param rand_char Pointer to the function that generates a random char
 * @return char*
 */
char *generate_genome(int size, char (*rand_char)(void));

/**
 * @brief Function that generates an empty population, without initializing the members of it
 *
 * @param size The size of the population
 * @return Population*
 */
Population *empty_population(int size);

/**
 * @brief Generates a population of genomes with its current fitness
 *
 * @param size Size of the population, the number of individuals
 * @param genome_length Size of the genome to be generated
 * @param rand_char Pointer to the function that generates a random char
 * @return Population*
 */
Population *generate_population(int size, int genome_length, char (*rand_char)(void));

/**
 * @brief Free the memory used by the population struct
 *
 * @param population Double pointer to the struct, pass the adress if using a single pointer
 */
void dealocate_population(Population **population);

/**
 * @brief Helper function to create a individual struct
 *
 * @param genome A pointer to the string to be used as the genome of the new individual
 * @param fitness The fitness value of the new individual
 * @return Individual*
 */
Individual *create_individual(const char *genome, int fitness);

/**
 * @brief Free the memory used by the invidivual passed by parameter
 *
 * @param idv Double pointer to the struct, pass the adress if using a single pointer
 */
void dealocate_individual(Individual **idv);

/**
 * @brief The function that simulates the selecion step of the genetic algorithm, you may change the function implementation
 * based on the genetic algorithm you are working on.
 *
 * @param population A pointer to the population of the current generation
 * @return Individual*
 */
Individual *selection(Population *population);

/**
 * @brief Function that simulates the mating / crossing over step of the genetic algorithm.
 *
 * @param p1 Pointer to the first parent
 * @param p2 Pointer to the second parent
 * @param rand_char Pointer to the function that generates a random char
 * @return char**
 */
char **single_point_crossing_over(Individual *p1, Individual *p2, char (*rand_char)(void));

/**
 * @brief Function that simulates the mutation on a single genome from the population.
 *
 * @param population Pointer to the struct population which contains the current generation
 * @param rand_char Pointer to the function that generates a random char
 */
void mutation(Population *population, char (*rand_char)(void));

/**
 * @brief Function that evaluates the population, setting the fitness for each one
 *
 * @param population
 * @param fitness_func
 */
void evaluation(Population *population, int (*fitness_func)(const char *genome, const char *target), const char *target);

/**
 * @brief Genetic algorithm
 *
 * @param population_size
 * @param target The target string to be generated
 * @param rand_char Pointer to the function that generates a random char
 * @param desired_fitness The value of fitness to be encountered
 * @param fitness_func Pointer to the function that calculates the fitness
 */
void genetic_algorithm(
    int population_size,
    const char *target,
    char (*rand_char)(void),
    int desired_fitness,
    int (*fitness_func)(const char *genome, const char *target));

#endif