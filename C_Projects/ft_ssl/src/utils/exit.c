#include "ft_ssl.h"

void free_filenames(t_filename *filenames)
{
    t_filename *tmp;

    while (filenames)
    {
        tmp = filenames;
        filenames = filenames->next;
        free(tmp->output->bytes);
        free(tmp->output);
        free(tmp);
    }
}

void free_consoles(t_console *consoles)
{
    t_console *tmp;

    while (consoles)
    {
        tmp = consoles;
        consoles = consoles->next;
        free(tmp->output->bytes);
        free(tmp->output);
        free(tmp->msg);
        free(tmp);
    }
}

void ssl_exit(char *msg, t_input *input, int8_t code)
{
    t_filename *tmp;

    ft_printf("%s", msg);
    free_filenames(input->filenames);
    free_consoles(input->console);
    exit(code);
}