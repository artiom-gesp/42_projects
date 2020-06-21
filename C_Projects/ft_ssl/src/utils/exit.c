#include "ft_ssl.h"

void ssl_exit(char *msg, t_input *input, int8_t code)
{
    t_filename *tmp;

    ft_printf("%s", msg);
    while (input->filenames)
    {
        tmp = input->filenames;
        input->filenames = input->filenames->next;
        free(tmp);
    }
    exit(code);
}