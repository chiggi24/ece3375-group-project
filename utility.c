#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "algorithm.h"

// Generates random values for the IR buffer and red buffer based on previous values
void generateBuffers(uint32_t *ir_buffer, uint32_t *red_buffer)
{
    // Seed the random number generator
    srand(time(NULL));

    // Define the initial values
    uint32_t ir_initial = 120000; // Initial value for IR buffer
    uint32_t red_initial = 65000; // Initial value for red buffer

    // Generate random values for IR buffer and red buffer based on previous values
    for (int i = 0; i < BUFFER_SIZE; ++i)
    {
        // Calculate the range for fluctuation around the previous value
        int ir_fluctuation = rand() % 1001 - 500; // Random value between -500 and 500
        int red_fluctuation = rand() % 201 - 100; // Random value between -100 and 100

        // Update the next value based on the previous value and fluctuation
        ir_buffer[i] = ir_initial + ir_fluctuation;    // Update IR buffer value
        red_buffer[i] = red_initial + red_fluctuation; // Update red buffer value

        // Update the initial values for the next iteration
        ir_initial = ir_buffer[i];   // Update IR buffer initial value
        red_initial = red_buffer[i]; // Update red buffer initial value
    }
}

// Printing buffers
void printBuffers(uint32_t *ir_buffer, uint32_t *red_buffer)
{
    // Print IR buffer
    printf("IR Buffer:\n");
    printf("[");
    for (int i = 0; i < BUFFER_SIZE; ++i)
    {
        printf("%d", ir_buffer[i]);
        if (i < BUFFER_SIZE - 1)
        {
            printf(", ");
        }
    }
    printf("]\n");

    // Print Red buffer
    printf("Red Buffer:\n");
    printf("[");
    for (int i = 0; i < BUFFER_SIZE; ++i)
    {
        printf("%d", red_buffer[i]);
        if (i < BUFFER_SIZE - 1)
        {
            printf(", ");
        }
    }
    printf("]\n");
}