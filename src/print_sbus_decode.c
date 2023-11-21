#include "print_sbus_decode.h"

#include <stdio.h>


void print_sbus_decode(const sbus_decode_t* decode, sbus_dbg_port_t port)
{
    switch (port) {
        case terminal:
        {
            const uint16_t* cur_chanell;
            for (cur_chanell = decode->channels_val;
                cur_chanell != decode->channels_val + SBUS_CHANNELS_COUNT - 1;
                ++cur_chanell)
            {
                printf("%hu, ", *cur_chanell);
            }
            printf("%hu\n", *cur_chanell);

            break;
        }
        default:
            return;
    }
}
