// Includes
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

// USER IS ASKED FOR PERSONAL HEALTH INFORMATION
// FOR DEMONSTRATION PURPOSES ASSUME THESE ARE THE VALUES THAT ARE ENTERED AND SAVED
#define AGEINPUT 20       // Years
#define HEIGHTINPUT 185.0 // cm
#define WEIGHTINPUT 185.0 // lb

// USER PLACES HEART-BEAT SENSOR ON FINGER
// FOR DEMONSTRATION PURPOSES ASSUME THESE ARE THE DIGITAL SIGNALS RECIEVED DURING A SINGLE READING
#define BUFFER_LENGTH 100
uint32_t red_buffer[BUFFER_LENGTH];
uint32_t ir_buffer[BUFFER_LENGTH];

// Generates random values for the IR buffer and red buffer based on previous values
void generateBuffers(uint32_t *ir_buffer, uint32_t *red_buffer)
{
    // Seed the random number generator
    srand(time(NULL));

    // Define the initial values
    uint32_t ir_initial = 120000; // Initial value for IR buffer
    uint32_t red_initial = 65000; // Initial value for red buffer

    // Generate random values for IR buffer and red buffer based on previous values
    for (int i = 0; i < BUFFER_LENGTH; ++i)
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
    for (int i = 0; i < BUFFER_LENGTH; ++i)
    {
        printf("%d", ir_buffer[i]);
        if (i < BUFFER_LENGTH - 1)
        {
            printf(", ");
        }
    }
    printf("]\n");

    // Print Red buffer
    printf("Red Buffer:\n");
    printf("[");
    for (int i = 0; i < BUFFER_LENGTH; ++i)
    {
        printf("%d", red_buffer[i]);
        if (i < BUFFER_LENGTH - 1)
        {
            printf(", ");
        }
    }
    printf("]\n");
}

// Function prototype
void maxim_heart_rate_and_oxygen_saturation(uint32_t *pun_ir_buffer, int32_t n_ir_buffer_length,
                                            uint32_t *pun_red_buffer, int32_t *pn_spo2,
                                            int8_t *pch_spo2_valid, int32_t *pn_heart_rate,
                                            int8_t *pch_hr_valid)
{
}

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
    maxim_heart_rate_and_oxygen_saturation(ir_buffer, BUFFER_LENGTH, red_buffer,
                                           &spo2, &spo2_valid, &heart_rate, &hr_valid);

    // Display the calculated heart rate and SpO2 values
    printf("Calculated SpO2: %d, Valid: %d\n", spo2, spo2_valid);
    printf("Calculated Heart Rate: %d, Valid: %d\n", heart_rate, hr_valid);

    return 0;
}