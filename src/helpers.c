#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>

#include "algorithms.h"
#include "types.h"
#include "helpers.h"
#include "ga.h"

static void merge(Individual **array, int initial_position, int middle, int final_position)
{
    int i, j, k;

    int left_quantity = middle - initial_position + 1;
    int right_quantity = final_position - middle;
    
    Individual **left = (Individual **)malloc((left_quantity + 1) * sizeof(Individual *));
    Individual **right = (Individual **)malloc((right_quantity + 1) * sizeof(Individual *));

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

    left[left_quantity] = create_individual("sentinel", INT_MIN);
    right[right_quantity] = create_individual("sentinel", INT_MIN);

    i = j = 0;

    for (k = initial_position; k <= final_position; k++)
    {
        if (left[i]->fitness >= right[j]->fitness)
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

    for (int i = 0; i < left_quantity + 1; i++)
    {
        dealocate_individual(&left[i]);
    }

    free(left);

    for (int i = 0; i < right_quantity + 1; i++)
    {
        dealocate_individual(&right[i]);
    }

    free(right);
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
        fprintf(f, "DNA: %s\t Fitness:%f\n", population->population[i]->genome, population->population[i]->fitness);
    }

    fprintf(f, "\n");

    if (new_population != NULL)
    {
        fprintf(f, "AFTER CROSSING OVER\n\n");

        for (int i = 0; i < new_population->pop_size; i++)
        {
            fprintf(f, "DNA: %s\t Fitness:%f\n", new_population->population[i]->genome, new_population->population[i]->fitness);
        }

        fprintf(f, "\n");
    }
    else
    {
        fprintf(f, "Perfect genome encountered at generation: %d\n\n", generation);
    }

    fclose(f);
}

int compare_float(float f1, float f2)
{
    float precision = 0.00001;
    if (((f1 - precision) < f2) && ((f1 + precision) > f2))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int bstoi(const char *str)
{
    int value = 0;
    int index_counter = 0;

    for (int i = strlen(str) - 1; i >= 0; i--)
    {
        if (str[i] == '1')
        {
            value += pow(2, index_counter);
        }
        index_counter++;
    }
    return value;
}

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

char random_char_eight_queens()
{
    int n = rand() % 8;
    char c = n + '0';

    return c;
}

void print_board(const char *genome)
{
    bool board[8][8] = {{false}};
    
    for (int i = 0; i < 8; i++)
    {
        int pos = genome[i] - '0';
        board[pos][i] = true;
    }

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            printf("%c ", board[i][j] ? 'X' : '-');
        }
        printf("\n");
    }
}

void output_board_to_file(int size, const char *genome)
{
    FILE *f = fopen("data.txt", "a+");

    if (f == NULL)
        exit(1);

    bool board[8][8] = {{false}};
    
    for (int i = 0; i < size; i++)
    {
        int pos = genome[i] - '0';
        board[pos][i] = true;
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            fprintf(f, "%c ", board[i][j] ? 'X' : '-');
        }
        fprintf(f, "\n");
    }

    fclose(f);
}