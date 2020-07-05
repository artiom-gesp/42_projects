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

char *pad_msg(t_bytes data)
{
    uint16_t zero_pad;
    uint64_t msg_len;
    char *tmp;
    char *padded_msg;

    msg_len = data.nb_bytes;

    zero_pad = ((msg_len + 1) * 8) % 512 <= 448 ? 448 - (((msg_len + 1) * 8) % 512) : 448 + (512 - (((msg_len + 1) * 8) % 512));
    if (!(padded_msg = malloc(msg_len + 1 + ceil(zero_pad / 8) + 8)))
        return NULL;
    ft_memcpy(padded_msg, data.bytes, msg_len);
    ft_memset(padded_msg + msg_len, 0, 1 + ceil(zero_pad / 8) + 8);
    *(padded_msg + msg_len) = 0x80;
    *((uint64_t*)(padded_msg + msg_len + 1 + (uint16_t)(ceil(zero_pad / 8)))) = (msg_len * 8) % ULLONG_MAX;

    // print_b(padded_msg, msg_len + 1 + ceil(zero_pad / 8) + 8);
    return padded_msg;
}