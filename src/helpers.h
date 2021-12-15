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

/**
 * @brief Function to compare two float numbers
 * 
 * @param f1 
 * @param f2 
 * @return int 1 if its equal, 0 if its not
 */
int compare_float(float f1, float f2);

/**
 * @brief Binary string to int
 * 
 * @param str 
 * @return int 
 */
int bstoi(const char *str);

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
 * @brief Generate numbers between 0 and 7 for the eight queens problem
 * 
 * @return char 
 */
char random_char_eight_queens();

/**
 * @brief Output the genome in the format of a chess board on the console
 * 
 * @param genome
 */
void print_board(const char *genome);

/**
 * @brief Output the genome to the log file 
 * @param size The size of the board
 * @param genome 
 */
void output_board_to_file(int size, const char *genome);

#endif