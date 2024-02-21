#include "sort.h"
#include <stdio.h>
#include <stdlib.h>

void bitonic_merge(int *array, size_t start, size_t size, int direction);
void bitonic_sort_recursive(int *array, size_t start, size_t size, int direction);
void bitonic_compare(int *array, size_t start, size_t size, int direction);
void print_array(const int *array, size_t size);

/**
 * bitonic_sort - Sorts an array of integers in ascending order using Bitonic sort
 * @array: Pointer to the array to sort
 * @size: Size of the array
 */
void bitonic_sort(int *array, size_t size)
{
    bitonic_sort_recursive(array, 0, size, 1);
}

/**
 * bitonic_sort_recursive - Recursively sorts a bitonic sequence
 * @array: Pointer to the array to sort
 * @start: Starting index of the sequence
 * @size: Size of the sequence
 * @direction: Sorting direction (1 for ascending, -1 for descending)
 */
void bitonic_sort_recursive(int *array, size_t start, size_t size, int direction)
{
    if (size > 1)
    {
        size_t half = size / 2;
        bitonic_sort_recursive(array, start, half, 1);
        bitonic_sort_recursive(array, start + half, half, -1);
        bitonic_merge(array, start, size, direction);
    }
}

/**
 * bitonic_merge - Merges two bitonic sequences
 * @array: Pointer to the array containing the sequences
 * @start: Starting index of the first sequence
 * @size: Size of the sequences
 * @direction: Sorting direction (1 for ascending, -1 for descending)
 */
void bitonic_merge(int *array, size_t start, size_t size, int direction)
{
    if (size > 1)
    {
        size_t half = size / 2;
        bitonic_compare(array, start, size, direction);
        bitonic_merge(array, start, half, direction);
        bitonic_merge(array, start + half, half, direction);
    }
}

/**
 * bitonic_compare - Compares and swaps elements in a bitonic sequence
 * @array: Pointer to the array containing the sequence
 * @start: Starting index of the sequence
 * @size: Size of the sequence
 * @direction: Sorting direction (1 for ascending, -1 for descending)
 */
void bitonic_compare(int *array, size_t start, size_t size, int direction)
{
    size_t i, half = size / 2;
    for (i = start; i < start + half; ++i)
    {
        if ((array[i] > array[i + half]) == direction)
        {
            int temp = array[i];
            array[i] = array[i + half];
            array[i + half] = temp;
            printf("Merging [%lu/%lu] (%s):\n", size, size, (direction == 1) ? "UP" : "DOWN");
            print_array(array, start + size);
        }
    }
}

/**
 * print_array - Prints an array of integers
 * @array: Pointer to the array to print
 * @size: Size of the array
 */
void print_array(const int *array, size_t size)
{
    size_t i;
    for (i = 0; i < size; ++i)
    {
        printf("%d", array[i]);
        if (i < size - 1)
            printf(", ");
    }
    printf("\n");
}
