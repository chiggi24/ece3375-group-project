// Includes
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include "algorithm.h"
#include "utility.h"

// USER IS ASKED FOR PERSONAL HEALTH INFORMATION
// FOR DEMONSTRATION PURPOSES ASSUME THESE ARE THE VALUES THAT ARE ENTERED AND SAVED
#define AGEINPUT 20       // Years
#define HEIGHTINPUT 185.0 // cm
#define WEIGHTINPUT 185.0 // lb

// USER PLACES HEART-BEAT SENSOR ON FINGER
// FOR DEMONSTRATION PURPOSES ASSUME THESE ARE THE DIGITAL SIGNALS RECIEVED DURING A SINGLE READING
uint32_t red_buffer[BUFFER_SIZE];
uint32_t ir_buffer[BUFFER_SIZE];


// Beginning of execution
int main()
{
    // Seed the random number generator
    srand(time(NULL));

    generateBuffers(ir_buffer, red_buffer);

    // Print buffers
    printBuffers(ir_buffer, red_buffer);

    // Call the heart rate calculation function with the generated fake input data
    int32_t spo2;       // Spo2 value (output)
    int8_t spo2_valid;  // Spo2 validity (output)
    int32_t heart_rate; // Heart rate value (output)
    int8_t hr_valid;    // Heart rate validity (output)

    // Call the function to calculate heart rate and SpO2 using the generated fake input data
    maxim_heart_rate_and_oxygen_saturation(ir_buffer, BUFFER_SIZE, red_buffer,
                                           &spo2, &spo2_valid, &heart_rate, &hr_valid);

    // Display the calculated heart rate and SpO2 values
    printf("Calculated SpO2: %d, Valid: %d\n", spo2, spo2_valid);
    printf("Calculated Heart Rate: %d, Valid: %d\n", heart_rate, hr_valid);

    return 0;
}