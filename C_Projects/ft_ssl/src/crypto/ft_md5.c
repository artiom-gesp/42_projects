#include "ft_ssl.h"

unsigned int rounds[4][4] = {{7, 12, 17, 22}, {5, 9, 14, 20}, {4, 11, 16, 23}, {6, 10, 15, 21}};

t_bytes *format_md5_output(uint32_t *res)
{
    t_bytes *output;
    
    if (!(output = malloc(sizeof(t_bytes))))
        return NULL;
    if (!(output->bytes = malloc(16)))
    {
        free(output);
        return NULL;
    }
    output->nb_bytes = 16;
    ft_memcpy(output->bytes, res, 16);
    return output;
}

void compute_func(t_md5 *process, int j)
{
    if (j < 16)
    {
        process->func = (process->tmp[1] & process->tmp[2]) | (~process->tmp[1] & process->tmp[3]);
        process->block_index = j;
    }
    else if (j < 32)
    {
        process->func = (process->tmp[3] & process->tmp[1]) | (~process->tmp[3] & process->tmp[2]);
        process->block_index = ((5 * j) + 1) % 16;
    }
    else if (j < 48)
    {
        process->func = process->tmp[1] ^ process->tmp[2] ^ process->tmp[3];
        process->block_index = ((3 * j) + 5) % 16;
    }
    else
    {
        process->func = process->tmp[2] ^ (process->tmp[1] | ~process->tmp[3]);
        process->block_index = (7 * j) % 16;
    }
}

void md5_hash(t_md5 *process, int j)
{
    process->tmp[0] = process->tmp[3];
    process->tmp[3] = process->tmp[2];
    process->tmp[2] = process->tmp[1];
    process->tmp[1] += rotl32(process->func, rounds[(int)(j / 16)][process->round]);
    process->round = process->round == 3 ? 0 : process->round + 1;
}

t_bytes *ft_md5(t_bytes data)
{
    t_md5 process;
    unsigned int cst[64];
    unsigned int res[4] = {0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476};
    char* padded_msg;

    ft_memset(&process, 0, sizeof(t_md5));
    for (int i = 0; i < 64; i++)
        cst[i] = floor(4294967296 * fabs(sin(i + 1)));
    process.nb_blocks = ceil((data.nb_bytes + 1) / (float)64) + ((data.nb_bytes % 64) >= 56 ? 1 : 0);
    if (!(padded_msg = pad_msg(data)))
        return NULL;
    for (int i = 0; i < process.nb_blocks; i++)
    {
        for (int k = 0; k < 4; k++)
            process.tmp[k] = res[k];
        for (int j = 0; j < 64; j++)
        {
            compute_func(&process, j);
            process.func += process.tmp[0] + cst[j] + ((uint32_t*)(padded_msg))[i * 16 + process.block_index];
            md5_hash(&process, j);
        }
        for (int k = 0; k < 4; k++)
            res[k] += process.tmp[k];
    }
    free(padded_msg);
    return format_md5_output(res);
}
