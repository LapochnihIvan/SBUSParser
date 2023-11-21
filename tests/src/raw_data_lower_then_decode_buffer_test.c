#include <string.h>
#include <assert.h>

#include <parse_sbus.h>


const uint8_t src[] = {
    15, 41, 107, 214, 235,
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


#define FIRST_PART_SIZE (10)
#define SECOND_PART_SIZE (3)
#define THIRD_PART_SIZE (12)


int main(void)
{
    sbus_decode_t res;

    parse_sbus(&res, src, FIRST_PART_SIZE);
    assert(!res.trust_flag);

    parse_sbus(&res, src + FIRST_PART_SIZE, SECOND_PART_SIZE);
    assert(!res.trust_flag);

    parse_sbus(&res, src + FIRST_PART_SIZE + SECOND_PART_SIZE, THIRD_PART_SIZE);
    assert(res.trust_flag);

    assert(memcmp(res.channels_val, EXPECTED_OUTPUT, SBUS_CHANNELS_COUNT) == 0);
}