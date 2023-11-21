#include <string.h>
#include <assert.h>

#include <parse_sbus.h>


const uint8_t PACKET1[] = {
    15, 41, 107, 214, 235,
    44, 169, 3, 33, 187,
    239, 95, 95, 76, 252,
    16, 236, 190, 212, 237,
    81, 6, 69, 77, 0,
    15, 41, 107,
};

const uint8_t PACKET2[] = {
    214, 235,
    44, 169, 3, 33, 187,
    239, 95, 95, 76, 252,
    16, 236, 190, 212, 237,
    81, 6, 69, 77, 0
};

const uint16_t EXPECTED_OUTPUT[] = {
    809, 717, 943, 1174, 58, 1602,
    1006, 767, 1119, 1929, 67, 1910,
    1355, 987, 404, 552, 2047, 0
};


int main(void)
{
    sbus_decode_t res;

    parse_sbus(&res, PACKET1, sizeof(PACKET1));
    assert(res.trust_flag);
    assert(memcmp(res.channels_val, EXPECTED_OUTPUT, SBUS_CHANNELS_COUNT) == 0);

    parse_sbus(&res, PACKET2, sizeof(PACKET2));
    assert(res.trust_flag);
    assert(memcmp(res.channels_val, EXPECTED_OUTPUT, SBUS_CHANNELS_COUNT) == 0);
}