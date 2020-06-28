#include "ft_ssl.h"


void leftRotatebyOne(uint32_t arr[], int n) 
{ 
    int temp = arr[0], i; 
    for (i = 0; i < n - 1; i++) 
        arr[i] = arr[i + 1]; 
    arr[i] = temp; 
} 

void leftRotate(uint32_t arr[], int d, int n) 
{ 
    int i; 
    for (i = 0; i < d; i++) 
        leftRotatebyOne(arr, n); 
} 
  

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
    *(padded_msg + msg_len) = 0x80;
    *((uint64_t*)(padded_msg + msg_len + 1 + (uint16_t)(ceil(zero_pad / 8)))) = (msg_len * 8) % ULLONG_MAX;

    // print_b(padded_msg, msg_len + 1 + ceil(zero_pad / 8) + 8);
    // printf("\nmsg  %lu\n", msg_len);
    return padded_msg;
}

char *ft_md5(char *msg)
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
        cst[i] = floor(4294967296 * fabs(sin(i + 1)));
    msg_len = ceil(ft_strlen(msg) / (float)64) + ((ft_strlen(msg) % 64) >= 56 ? 1 : 0);
    if (!(padded_msg = pad_msg(msg)))
        return NULL;
    round = 0;

    int block;
    for (int i = 0; i < msg_len; i++)
    {
        a = res[0];
        b = res[1];
        c = res[2];
        d = res[3];
        // ft_printf("A=%u, B=%u, C=%u, D=%u\n", a, b, c, d);
        for (int j = 0; j < 64; j++)
        {
            if (j < 16)
            {
                func = (b & c) | (~b & d);
                block = j;
            }
            else if (j < 32)
            {
                func = (d & b) | (~d & c);
                block = ((5 * j) + 1) % 16;
            }
            else if (j < 48)
            {
                func = b ^ c ^ d;
                block = ((3 * j) + 5) % 16;
            }
            else
            {
                func = c ^ (b | ~d);
                block = (7 * j) % 16;
            }
            // ft_printf("block [%d] : %u\n", i * 16 + block, ((uint32_t*)(padded_msg))[i * 16 + block]);
            // ft_printf("block : %u, round : %d, cst: %u\n", block, rounds[(int)(j / 16)][round], cst[j]);
            func += a + cst[j] + ((uint32_t*)(padded_msg))[i * 16 + block];
            a = d;
            d = c;
            c = b;
            b += rotl32(func, rounds[(int)(j / 16)][round]);
            // uint32_t arr[4] = {a, b, c, d};
            // leftRotate(arr, j + 1, 4);
            round = round == 3 ? 0 : round + 1;
            // ft_printf("[i = %d] A=%u, B=%u, C=%u, D=%u\n", j, arr[0], arr[1], arr[2], arr[3]);
        }
        res[0] += a;
        res[1] += b;
        res[2] += c;
        res[3] += d;
    }
    free(padded_msg);
    for (int i = 0; i < 4; i++)
    {
        ft_printf("%08x ", __bswap_32(res[i]));
    }
    ft_printf("\n");
    return "a";
}
