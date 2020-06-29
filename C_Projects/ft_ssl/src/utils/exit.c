#include "ft_ssl.h"

void free_filenames(t_filename *filenames)
{
    t_filename *tmp;

    while (filenames)
    {
        tmp = filenames;
        filenames = filenames->next;
        if (tmp->output)
        {
            free(tmp->output->bytes);
            free(tmp->output);
        }
        free(tmp);
    }
}

void free_strings(t_string *strings)
{
    t_string *tmp;

    while (strings)
    {
        tmp = strings;
        strings = strings->next;
        if (tmp->output)
        {
            free(tmp->output->bytes);
            free(tmp->output);
        }
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
        if (tmp->output)
        {
            free(tmp->output->bytes);
            free(tmp->output);
        }
        free(tmp->msg);
        free(tmp);
    }
}

void ssl_exit(char *msg, t_input *input, int8_t code)
{
    t_filename *tmp;

    free_filenames(input->filenames);
    free_strings(input->strings);
    free_consoles(input->console);
    exit(code);
}