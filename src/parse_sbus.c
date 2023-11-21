#include "parse_sbus.h"

#include <string.h>


#define BITS_IN_BYTE ((uint8_t)8U)

#define SBUS_MAX_CHANNEL_VAL ((uint16_t)0x07FFU)
#define SBUS_BIT_SHIFT_OFFSET (SBUS_CHANNEL_BIT_SIZE - BITS_IN_BYTE)


typedef struct parsed_channels
{
    uint16_t value[SBUS_CHANNELS_COUNT];
    uint8_t cur_parsed_byte_num;
} parsed_channels_t;


static uint16_t* parse_servo_channel_byte(uint16_t* cur_channel,
                                          const uint8_t cur_byte,
                                          uint8_t* cur_shift)
{
    *cur_channel |= cur_byte << *cur_shift;
    if (*cur_shift < SBUS_BIT_SHIFT_OFFSET)
    {
        *cur_shift += BITS_IN_BYTE;
    }
    else
    {
        *cur_channel++ &= SBUS_MAX_CHANNEL_VAL;
        if (*cur_shift != SBUS_BIT_SHIFT_OFFSET)
        {
            *cur_channel |= cur_byte >> (SBUS_CHANNEL_BIT_SIZE - *cur_shift);
        }
        *cur_shift -= SBUS_BIT_SHIFT_OFFSET;
    }

    return cur_channel;
}

static void parse_digital_channels(uint16_t* cur_channel,
                                   const uint8_t cur_byte)
{
    *cur_channel = SBUS_MAX_CHANNEL_VAL *
        (cur_byte & SBUS_17_CHANNEL_MASK);
    *++cur_channel = SBUS_MAX_CHANNEL_VAL *
        ((cur_byte & SBUS_18_CHANNEL_MASK) >> 1U);
}

void parse_sbus(sbus_decode_t* dest, const uint8_t* src, const uint8_t length)
{
    dest->trust_flag = false;

    static parsed_channels_t parsed_channels = { .cur_parsed_byte_num = 0 };

    uint16_t* cur_channel;
    uint8_t cur_shift;
    if (parsed_channels.cur_parsed_byte_num > 1U)
    {
        const uint8_t recorded_bits_count =
            (uint8_t)(parsed_channels.cur_parsed_byte_num - 1U) * BITS_IN_BYTE;

        cur_channel = parsed_channels.value +
            recorded_bits_count / SBUS_CHANNEL_BIT_SIZE;
        cur_shift = recorded_bits_count % SBUS_CHANNEL_BIT_SIZE;
    }

    const uint8_t* const parse_end_byte = src + length;
    for (; src != parse_end_byte; ++src)
    {
        if (*src == SBUS_HEADER)
        {
            memset(parsed_channels.value, 0U, SBUS_CHANNELS_COUNT * sizeof(uint16_t));
            parsed_channels.cur_parsed_byte_num = 0U;

            cur_channel = parsed_channels.value;
            cur_shift = 0U;
        }
        else if (parsed_channels.cur_parsed_byte_num == SBUS_INPUT_SIZE ||
            parsed_channels.cur_parsed_byte_num == 0)
        {
            continue;
        }
        else if (*src == SBUS_FOOTER)
        {
            if (parsed_channels.cur_parsed_byte_num == SBUS_INPUT_SIZE - 1U)
            {
                memcpy(dest->channels_val,
                        parsed_channels.value,
                        SBUS_CHANNELS_COUNT * sizeof(uint16_t));
                dest->trust_flag = true;
            }

            parsed_channels.cur_parsed_byte_num = SBUS_INPUT_SIZE;
            continue;
        }
        else if (parsed_channels.cur_parsed_byte_num == SBUS_DIGITAL_CHANNELS_BYTE_NUM)
        {
            parse_digital_channels(cur_channel, *src);
        }
        else
        {
           cur_channel = parse_servo_channel_byte(cur_channel, *src, &cur_shift);
        }

        ++parsed_channels.cur_parsed_byte_num;
    }
}
