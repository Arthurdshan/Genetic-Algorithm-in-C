/**
 * @file helpers.h
 * @author Arthur Han
 * @brief Header file for the helper functions to the genetic algorithm.
 * @version 0.1
 * @date 2021-12-10
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef __HELPERS_H__
#define __HELPERS_H__

/**
 * @brief Merge sort function used to get the fittest individual and / or perform elitist if needed
 *
 * @param array Array of individuals
 * @param left Use 0
 * @param right Use size - 1
 */
void merge_sort(Individual **array, int left, int right);

/**
 * @brief Function to create the log file
 *
 */
void start_file();

/**
 * @brief Function to put into the file all the log from every generation.
 *
 * @param population Pointer to the old population
 * @param new_population Pointer to the new population, pass NULL if there's no new population.
 * @param generation Current generation of the algorithm
 */
void output_to_file(Population *population, Population *new_population, int generation);

#endif