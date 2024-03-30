#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "algorithm.h"
#include "address_map_arm.h"

volatile int *hex_ptr = (int *)HEX3_HEX0_BASE;
volatile int *hex_ptr2 = (int *)HEX5_HEX4_BASE;
#define SEG_DASH (1 << 6)

// Function to initialize buffers with initial data
void generateInitialBuffers(uint32_t *ir_buffer, uint32_t *red_buffer)
{
    // Define initial values
    uint32_t ir_initial = 9000;   // Initial value for IR buffer
    uint32_t red_initial = 54000; // Initial value for red buffer

    // Set initial values for the first element of the buffers
    ir_buffer[0] = ir_initial;
    red_buffer[0] = red_initial;

    // Generate subsequent values based on previous values
    for (int i = 1; i < BUFFER_LENGTH; i++)
    {
        ir_buffer[i] = ir_buffer[i - 1] + (rand() % 600) - 300;
        red_buffer[i] = red_buffer[i - 1] + (rand() % 400) - 200;
    }
}

// Function to replace oldest entries in buffers with new data
void replaceOldestEntries(uint32_t *ir_buffer, uint32_t *red_buffer, int replacement_size)
{
    // Shift the existing data to make room for new data for IR buffer
    for (int i = 0; i < BUFFER_LENGTH - replacement_size; i++)
    {
        ir_buffer[i] = ir_buffer[i + replacement_size];
    }
    // Generate and add new data to the end of the IR buffer
    for (int i = BUFFER_LENGTH - replacement_size; i < BUFFER_LENGTH; i++)
    {
        ir_buffer[i] = ir_buffer[i - 1] + rand() % 600 - 300;
    }

    // Shift the existing data to make room for new data for Red buffer
    for (int i = 0; i < BUFFER_LENGTH - replacement_size; i++)
    {
        red_buffer[i] = red_buffer[i + replacement_size];
    }
    // Generate and add new data to the end of the Red buffer
    for (int i = BUFFER_LENGTH - replacement_size; i < BUFFER_LENGTH; i++)
    {
        red_buffer[i] = red_buffer[i - 1] + (rand() % 400) - 200;
    }
}

// Function to print buffers
void printBuffers(uint32_t *ir_buffer, uint32_t *red_buffer)
{
    printf("IR Buffer: [");
    for (int i = 0; i < BUFFER_LENGTH; i++)
    {
        printf("%d, ", ir_buffer[i]);
    }
    printf("]\n");

    printf("Red Buffer: [");
    for (int i = 0; i < BUFFER_LENGTH; i++)
    {
        printf("%d, ", red_buffer[i]);
    }
    printf("]\n");
}

// Function to calculate cardiovascular zone based on max heart rate
int calculateCardiovascularZone(int age, int heartRate)
{
    // Calculate max heart rate using Fox formula
    int maxHeartRate = 220 - age;

    // Calculate percentage of max heart rate
    double percentage = ((double)heartRate / maxHeartRate) * 100;

    // Determine cardiovascular zone
    if (percentage >= 50 && percentage < 60)
    {
        return 1;
    }
    else if (percentage >= 60 && percentage < 70)
    {
        return 2;
    }
    else if (percentage >= 70 && percentage < 80)
    {
        return 3;
    }
    else if (percentage >= 80 && percentage < 90)
    {
        return 4;
    }
    else if (percentage >= 90 && percentage <= 100)
    {
        return 5;
    }
    else
    {
        return 0;
    }
}

// Function to get the display value for a single digit
int getDisplayValue(int digit)
{
    // Define segment patterns for digits 0 to 9
    int segments[10] = {
        0x3F, // 0
        0x06, // 1
        0x5B, // 2
        0x4F, // 3
        0x66, // 4
        0x6D, // 5
        0x7D, // 6
        0x07, // 7
        0x7F, // 8
        0x67  // 9
    };
    return segments[digit];
}

void displayOnHex(int heartRate, int state)
{
    if (state == 0)
    {
        // Construct the value to display "Error" on HEX5 to HEX2
        int hex3_hex0_value = 0x0 |          // HEX0: Blank
                              (0x50 << 8) |  // HEX1: r
                              (0x5C << 16) | // HEX2: o
                              (0x50 << 24);  // HEX3: r

        // Write to HEX5 to HEX2 using a word-sized store
        *hex_ptr = hex3_hex0_value;

        // Construct the value to be written to HEX5_HEX4_BASE
        int hex5_hex4_value = (0x50) |     // HEX4: r
                              (0x79 << 8); // HEX5: E

        // Write to HEX5_HEX4_BASE using a word-sized store
        *hex_ptr2 = hex5_hex4_value;
    }
    else
    {
        // Calculate individual digits of heart rate
        int hundred = heartRate / 100;
        int ten = (heartRate / 10) % 10;
        int single = heartRate % 10;

        // Construct the value to be written to HEX3_HEX0_BASE
        int hex3_hex0_value = (getDisplayValue(single) & 0xFF) |          // HEX0: Single of heart rate
                              ((getDisplayValue(ten) & 0xFF) << 8) |      // HEX1: Ten of heart rate
                              ((getDisplayValue(hundred) & 0xFF) << 16) | // HEX2: Hundred of heart rate
                              (SEG_DASH << 24);                           // HEX3: Dash

        // Write to HEX3_HEX0_BASE using a word-sized store
        *hex_ptr = hex3_hex0_value;

        // Construct the value to be written to HEX5_HEX4_BASE
        int hex5_hex4_value = (getDisplayValue(state) & 0xFF) | // HEX4: State
                              (0x06 << 8);                      // HEX5: Blank

        // Write to HEX5_HEX4_BASE using a word-sized store
        *hex_ptr2 = hex5_hex4_value;
    }
}
