#include "ft_ssl.h"

uint32_t rotl32 (uint32_t value, unsigned int count)
{
    const unsigned int mask = 8 * sizeof(value) - 1;
    count &= mask;
    return (value << count) | (value >> (-count & mask));
}

uint32_t rotr32 (uint32_t value, unsigned int count)
{
    const unsigned int mask = 8 * sizeof(value) - 1;
    count &= mask;
    return (value >> count) | (value << (-count & mask));
}

void print_b(void *s, uint64_t len)
{
    char *p = s;
    uint8_t a;

    for (int i = 0; i < len; i++)
    {
        a = 128;
        for (int j = 0; j < 8; j++)
        {
            printf("%u", p[i] & a ? 1 : 0);
            a = a >> 1;
        }
        printf(" ");
    }
    printf("\n");
}
