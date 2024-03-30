#ifndef UTILITY_H_
#define UTILITY_H_

#include <stdint.h>

// Function to generate random values for IR buffer and red buffer
void generateInitialBuffers(uint32_t *ir_buffer, uint32_t *red_buffer);

// Function to replace oldest entries in buffers with new data
void replaceOldestEntries(uint32_t *ir_buffer, uint32_t *red_buffer, int replacement_size);

// Function to print IR buffer and red buffer
void printBuffers(uint32_t *ir_buffer, uint32_t *red_buffer);

// Function to calculate cardiovascular zone based on max heart rate
int calculateCardiovascularZone(int age, int heartRate);

void displayOnHex(int heartRate, int state);

#endif /* UTILITY_H_ */
