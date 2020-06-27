#include "ft_ssl.h"


uint32_t rotl32 (uint32_t value, unsigned int count) {
    const unsigned int mask = 8 * sizeof(value) - 1;
    count &= mask;
    return (value << count) | (value >> (-count & mask));
}

uint32_t rotr32 (uint32_t value, unsigned int count) {
    const unsigned int mask = 8 * sizeof(value) - 1;
    count &= mask;
    return (value >> count) | (value << (-count & mask));
}

void print_b(void *s, uint64_t len)
{
    char *p = s;
    uint64_t a = 0x8000000000000000;
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

char *pad_msg(char *msg)
{
    uint16_t zero_pad;
    uint64_t msg_len;
    char *tmp;
    char *padded_msg;

    msg_len = ft_strlen(msg);
    zero_pad = ((msg_len + 1) * 8) % 512 <= 448 ? 448 - (((msg_len + 1) * 8) % 512) : 448 + (512 - (((msg_len + 1) * 8) % 512));
    if (!(tmp = ft_strdup(msg)))
        return NULL;
    if (!(padded_msg = realloc(ft_strdup(tmp), msg_len + 1 + ceil(zero_pad / 8) + 8)))
    {
        free(tmp);
        return NULL;
    }
    ft_memset(padded_msg + msg_len, 0, 1 + ceil(zero_pad / 8) + 8);
    ft_printf("len msg : %d, zero pad %lld\n", msg_len, zero_pad);
    *(padded_msg + msg_len) = 0x80;
    *(padded_msg + msg_len + 1 + (uint64_t)(ceil(zero_pad / 8))) = msg_len;

    print_b(padded_msg, msg_len + 1 + ceil(zero_pad / 8) + 8);

    return padded_msg;
}

uint16_t *ft_md5(char *msg)
{
    unsigned int rounds[4][4] = {
        {7, 12, 17, 22}, {5, 9, 14, 20}, {4, 11, 16, 23}, {6, 10, 15, 21}
    };
    unsigned int round;
    unsigned int cst[64];
    unsigned int res[4] = {0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476};
    unsigned int a;
    unsigned int b;
    unsigned int c;
    unsigned int d;
    unsigned int func;
    char* padded_msg;
    uint64_t msg_len;

    for (int i = 0; i < 64; i++)
    {
        cst[i] = floor(4294967296 * fabs(sin(i + 1)));
        // printf("%#x\n", cst[i]);
    }
    msg_len = ceil(ft_strlen(msg) / (float)64) + ((ft_strlen(msg) % 64) >= 56 ? 1 : 0);
    ft_printf("len msg : %lld\n", msg_len); 
    if (!(padded_msg = pad_msg(msg)))
        return NULL;
    round = 0;
    ft_printf("In md5 : %s\n", msg);
    int block;
    for (int i = 0; i < msg_len; i++)
    {
        a = res[0];
        b = res[1];
        c = res[2];
        d = res[3];
        for (int j = 0; j < 64; j++)
        {
            if (j < 16)
            {
                func = (b & c) | (~b & d);
                block = i;
            }
            else if (j < 32)
            {
                func = (d & b) | (~d & c);
                block = ((5 * i) + 1) % 16;
            }
            else if (j < 48)
            {
                func = b ^ c ^ d;
                block = ((3 * i) + 5) % 16;
            }
            else
            {
                func = c ^ (b | ~d);
                block = (7 * i) % 16;
            }
            func += a + cst[i] + ((uint32_t*)(padded_msg))[i * 16 + block];
            a = d;
            d = c;
            c = b;
            b += rotl32(func, rounds[(int)(ceil(i / 64)) * 4][round]);
            ++round;
            if (round == 4)
                round = 0;
        }
        res[0] += a;
        res[1] += b;
        res[2] += c;
        res[3] += d;
    }
    free(padded_msg);
    for (int i = 0; i < 4; i++)
    {
        ft_printf("%x ", res[i]);
    }
    ft_printf("\n");
    return res[0] << 12 | res[1] << 8 | res[2] << 4 | res[1];
}
