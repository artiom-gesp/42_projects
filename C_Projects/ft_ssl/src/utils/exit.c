#include "ft_ssl.h"

void ssl_exit(char *msg, t_input *input)
{
    t_filename *tmp;

    ft_printf("%s", msg);
    if (input->filenames)
    {
        tmp = input->filenames;
        input->filenames = input->filenames->next;
        free(tmp);
    }
    exit(-1);
}