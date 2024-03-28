#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateFakeInput(uint32_t *ir_buffer, int32_t *ir_buffer_length,
                       uint32_t *red_buffer)
{
    // Generate fake IR sensor data buffer
    *ir_buffer_length = 100; // Example buffer length
    for (int i = 0; i < *ir_buffer_length; ++i)
    {
        ir_buffer[i] = rand() % 1024; // Assuming values range from 0 to 1023
    }

    // Generate fake Red sensor data buffer (same length as IR buffer)
    for (int i = 0; i < *ir_buffer_length; ++i)
    {
        red_buffer[i] = rand() % 1024; // Assuming values range from 0 to 1023
    }
}

// Beginning of execution
int main()
{
    // USER IS ASKED FOR PERSONAL HEALTH INFORMATION
    // FOR DEMONSTRATION PURPOSES ASSUME THESE ARE THE VALUES THAT ARE ENTERED AND SAVED
    const int AGEINPUT = 20;       // Years
    const float HEIGHTINPUT = 185; // cm
    const float WEIGHTINPUT = 185; // lb
    // USER PLACES HEART-BEAT SENSOR ON FINGER
    // FOR DEMONSTRATION PURPOSES ASSUME THESE ARE THE DIGITAL SIGNALS RECIEVED DURING A SINGLE READING
    const int BUFFERLENGTH = 50;

    uint32_t irBuffer[BUFFER_LENGTH] = {100, 110, 120, 130, 140, 150, 160, 170, 180, 190};

    // Assign input values
    int age = AGEINPUT;
    float height = HEIGHTINPUT;
    float weight = WEIGHTINPUT;

    // Seed the random number generator
    srand(time(NULL));

    // Define variables to hold fake input data
    uint32_t ir_buffer[100];
    int32_t ir_buffer_length;
    uint32_t red_buffer[100];

    // Generate fake input data
    generateFakeInput(ir_buffer, &ir_buffer_length, red_buffer);

    // Call the heart rate calculation function with the generated fake input data
    uint32_t spo2;      // Spo2 value (output)
    int8_t spo2_valid;  // Spo2 validity (output)
    int32_t heart_rate; // Heart rate value (output)
    int8_t hr_valid;    // Heart rate validity (output)

    // Call the function to calculate heart rate and SpO2 using the generated fake input data
    maxim_heart_rate_and_oxygen_saturation(ir_buffer, ir_buffer_length, red_buffer,
                                           &spo2, &spo2_valid, &heart_rate, &hr_valid);

    // Display the calculated heart rate and SpO2 values
    printf("Calculated SpO2: %d, Valid: %d\n", spo2, spo2_valid);
    printf("Calculated Heart Rate: %d, Valid: %d\n", heart_rate, hr_valid);

    return 0;
}
