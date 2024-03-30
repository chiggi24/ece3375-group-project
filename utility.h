#ifndef UTILITY_H_
#define UTILITY_H_

#include <stdint.h>

// Function to generate random values for IR buffer and red buffer
void generateBuffers(uint32_t *ir_buffer, uint32_t *red_buffer);

// Function to print IR buffer and red buffer
void printBuffers(uint32_t *ir_buffer, uint32_t *red_buffer);

#endif /* UTILITY_H_ */
