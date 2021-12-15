/**
 * @file algorithms.h
 * @author Arthur Han
 * @brief Header file containing all fitness functions for its problems
 * @version 0.1
 * @date 2021-12-10
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef __ALGORITHMS_H__
#define __ALGORITHMS_H__

#include "genetic_algorithm.h"

/**
 * @brief Function that calculates the fitness for a given genome 
 * 
 * @param genome 
 * @return double 
 */
float maximize_function_fitness(const char *genome);

/**
 * @brief 
 * 
 * @param genome 
 * @return float 
 */
float eight_queen_fitness(const char *genome);

#endif