#include "ft_ssl.h"

t_bytes *format_base64_output(char *res, uint64_t len)
{
    t_bytes *output;
    
    if (!(output = malloc(sizeof(t_bytes))))
        return NULL;
    output->bytes = res;
    output->nb_bytes = len;
    return output;
}

char base64_convert(uint8_t val)
{
    if (val < 26)
        return val + 65;
    if (26 <= val && val < 52)
        return (val - 26) + 'a';
    if (52 <= val && val < 61)
        return (val - 52) + '0';
    if (val == 62)
        return '+';
    return '/';
}

t_bytes *ft_base64(t_bytes data)
{
    uint8_t padding_len;
    uint64_t output_len;
    char* output;
    uint8_t tmp;
    uint8_t index;

    padding_len = (3 - data.nb_bytes % 3) % 3;
    output_len = (ceil(data.nb_bytes / 3.0)) * 4;
    if (!(output = malloc(output_len)))
        return NULL;
    for (int i = 0; i < padding_len; i++)
        output[output_len - 1 - i] = '=';
    index = 0;
    for (int i = 0; i < (output_len - padding_len); i++)
    {
        tmp = 0;
        for (int j = 0; j < 3; j++)
        {
            tmp |= ((*data.bytes >> (6 - index)) & 0x03) << (4 - j * 2);
            if (index == 6)
                ++data.bytes;
            index = index == 6 ? 0 : index + 2;
        }
        output[i] = base64_convert(tmp);
    }
    return format_base64_output(output, output_len);
}