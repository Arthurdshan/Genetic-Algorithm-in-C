/**
 * @file algorithms.h
 * @author Arthur Han
 * @brief Header file containing all the extra functions to the genetic algorithm, here
 * contains the base genome generator, fitness functions, etc..
 * @version 0.1
 * @date 2021-12-10
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef __ALGORITHMS_H__
#define __ALGORITHMS_H__

#include "types.h"

/**
 * @brief Function that generates either 0 or 1
 *
 * @return char
 */
char random_binary_char();

/**
 * @brief Function that generates a random char
 * 
 * @return char 
 */
char random_char();

/**
 * @brief Binary string to int
 * 
 * @param str 
 * @return int 
 */
int bstoi(const char *str);

/**
 * @brief Function that calculates the fitness for a given genome 
 * 
 * @param genome 
 * @return double 
 */
float equation_fitness(const char *genome);

#endif