#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <unistd.h>

#include "algorithm.h" // Include header file for algorithms
#include "utility.h"   // Include header file for utility functions

#define AGEINPUT 20         // Define constant for age input
#define REPLACEMENT_SIZE 25 // Define constant for buffer replacement size

uint32_t red_buffer[BUFFER_LENGTH]; // Define buffer for red data
uint32_t ir_buffer[BUFFER_LENGTH];  // Define buffer for infrared data

// Main function
int main()
{
    // Seed the random number generator with current time
    srand(time(NULL));

    // Generate initial buffers
    generateInitialBuffers(ir_buffer, red_buffer);

    // Calculate and display initial heart rate and SpO2 values
    int32_t spo2;       // Spo2 value (output)
    int8_t spo2_valid;  // Spo2 validity (output)
    int32_t heart_rate; // Heart rate value (output)
    int8_t hr_valid;    // Heart rate validity (output)

    // Calculate heart rate and SpO2
    maxim_heart_rate_and_oxygen_saturation(ir_buffer, BUFFER_LENGTH, red_buffer,
                                           &spo2, &spo2_valid, &heart_rate, &hr_valid);

    // Print calculated heart rate and validity
    printf("Calculated Heart Rate: %d, Valid: %d\n", heart_rate, hr_valid);

    // Calculate cardiovascular state based on age and heart rate
    int state = calculateCardiovascularZone(AGEINPUT, heart_rate);

    // Display heart rate and cardiovascular state on a hexadecimal display
    displayOnHex(heart_rate, state);

    // Add delay to control the rate of buffer replacement and calculation
    sleep(1);

    // Infinite loop to continuously replace oldest entries and recalculate heart rate and SpO2
    while (1)
    {
        // Replace oldest entries in buffers with new data
        replaceOldestEntries(ir_buffer, red_buffer, REPLACEMENT_SIZE);

        // Calculate and display updated heart rate and SpO2 values
        maxim_heart_rate_and_oxygen_saturation(ir_buffer, BUFFER_LENGTH, red_buffer,
                                               &spo2, &spo2_valid, &heart_rate, &hr_valid);
        printf("Calculated Heart Rate: %d, Valid: %d\n", heart_rate, hr_valid);

        // Calculate cardiovascular state
        int state = calculateCardiovascularZone(AGEINPUT, heart_rate); // Calculate cardiovascular state based on age and heart rate

        // Display updated heart rate and cardiovascular state on a hexadecimal display
        displayOnHex(heart_rate, state);

        // Add delay to control the rate of buffer replacement and calculation
        sleep(1);
    }

    return 0;
}
