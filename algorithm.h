// Header file for MAXREFDES117 algorithms
// Retrieved from https://www.analog.com/en/resources/reference-designs/maxrefdes117.html#rd-overview

#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include <stdint.h>

#define true 1
#define false 0
#define FS 100
#define BUFFER_SIZE (FS * 5)
#define BUFFER_LENGTH 100
#define HR_FIFO_SIZE 7
#define MA4_SIZE 4     // DO NOT CHANGE
#define HAMMING_SIZE 5 // DO NOT CHANGE
#define min(x, y) ((x) < (y) ? (x) : (y))

extern const uint16_t auw_hamm[31];
extern const uint8_t uch_spo2_table[184];
extern int32_t an_dx[BUFFER_SIZE - MA4_SIZE];
extern int32_t an_x[BUFFER_SIZE];
extern int32_t an_y[BUFFER_SIZE];

void maxim_heart_rate_and_oxygen_saturation(uint32_t *pun_ir_buffer, int32_t n_ir_buffer_length, uint32_t *pun_red_buffer, int32_t *pn_spo2, int8_t *pch_spo2_valid, int32_t *pn_heart_rate, int8_t *pch_hr_valid);
void maxim_find_peaks(int32_t *pn_locs, int32_t *pn_npks, int32_t *pn_x, int32_t n_size, int32_t n_min_height, int32_t n_min_distance, int32_t n_max_num);
void maxim_peaks_above_min_height(int32_t *pn_locs, int32_t *pn_npks, int32_t *pn_x, int32_t n_size, int32_t n_min_height);
void maxim_remove_close_peaks(int32_t *pn_locs, int32_t *pn_npks, int32_t *pn_x, int32_t n_min_distance);
void maxim_sort_ascend(int32_t *pn_x, int32_t n_size);
void maxim_sort_indices_descend(int32_t *pn_x, int32_t *pn_indx, int32_t n_size);

#endif /* ALGORITHM_H_ */
