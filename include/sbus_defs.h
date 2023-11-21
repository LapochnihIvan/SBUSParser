#ifndef SBUS_DEFS_H
#define SBUS_DEFS_H


#include <stdint.h>
#include <stdbool.h>


#define SBUS_HEADER ((uint8_t)0x0FU)
#define SBUS_FOOTER ((uint8_t)0x00U)

#define SBUS_INPUT_SIZE ((uint8_t)25U)
#define SBUS_CHANNELS_BYTES ((uint8_t)(SBUS_INPUT_SIZE - 2U))

#define SBUS_CHANNELS_COUNT ((uint8_t)18U)
#define SBUS_CHANNEL_BIT_SIZE ((uint8_t)11U)

#define SBUS_DIGITAL_CHANNELS_BYTE_NUM ((uint8_t)23U)
#define SBUS_17_CHANNEL_MASK ((uint8_t)0x01U)
#define SBUS_18_CHANNEL_MASK ((uint8_t)0x02U)


typedef struct sbus_decode
{
    uint16_t channels_val[SBUS_CHANNELS_COUNT];
    bool trust_flag; //true if channels_val are completed
} sbus_decode_t;


#endif //!SBUS_DEFS_H
