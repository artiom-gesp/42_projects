#include "ft_ssl.h"

t_bytes *format_sha256_output(uint32_t *res)
{
    t_bytes output;
    
    if (!(output.bytes = malloc(16)))
        return NULL;
    ft_memcpy(output.bytes, res, 16);
    return &output;
}

t_bytes *ft_sha256(t_bytes data)
{
    
    ft_printf("In sha256 : %s", data.bytes);
    return format_sha256_output(NULL);
}
