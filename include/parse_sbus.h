#ifndef PARCE_SBUS_H
#define PARCE_SBUS_H


#include "sbus_defs.h"

/**
 * @brief Parse SBUS src function
 * @details This function take SBUS raw data buffers with different sizes and
 * write result to destination when SBUS footer was detected
 * @param src SBUS raw data buffer
 * @param length SBUS raw data buffer lenght
 * @retval None
 */
void parse_sbus(sbus_decode_t* dest, const uint8_t* src, uint8_t length);


#endif //!PARCE_SBUS_H
