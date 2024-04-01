#ifndef UTILITY_H_  // Header guard: prevents multiple inclusion of this header file
#define UTILITY_H_  // Definition of UTILITY_H_ to signal that this header file has been included

#include <stdint.h>  // Include necessary header for standard integer types

// Function to generate random values for IR buffer and red buffer
void generateInitialBuffers(uint32_t *ir_buffer, uint32_t *red_buffer);

// Function to replace oldest entries in buffers with new data
void replaceOldestEntries(uint32_t *ir_buffer, uint32_t *red_buffer, int replacement_size);

// Function to calculate cardiovascular zone based on max heart rate
int calculateCardiovascularZone(int age, int heartRate);

// Function to display heart rate and state on a hex display
void displayOnHex(int heartRate, int state);

#endif // End of header guard
