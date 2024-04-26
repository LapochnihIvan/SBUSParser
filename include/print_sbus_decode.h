#ifndef PRINT_SBUS_DECODE
#define PRINT_SBUS_DECODE


#include "sbus_defs.h"


typedef enum sbus_dbg_port
{
    uart,
    xbee,
    usb,
    terminal
} sbus_dbg_port_t;


/**
 * @brief Print SBUS parsing result
 * @details This function print SBUS parsing result to one of debug ports
 * @param decode SBUS parsing result
 * @param port Debug port to printing
 * @retval None
 */
void print_sbus_decode(const sbus_decode_t* decode, sbus_dbg_port_t port);


#endif //!PRINT_SBUS_DECODE
