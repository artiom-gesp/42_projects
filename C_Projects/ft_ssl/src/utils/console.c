#include "ft_ssl.h"

t_console *allocate_console(t_bytes *output, t_input *input, char *msg)
{
    t_console *console;

    if (!(console = malloc(sizeof(t_console))))
    {
        free(msg);
        free(output->bytes);
        free(output);
        ssl_exit("Malloc failed", input, -1);
    }
    console->msg = msg;
    console->output = output;
    console->next = NULL;
    return console;
}

void add_to_console(t_bytes *output, t_input *input, char *msg)
{
    t_console *console;
    if (!output)
    {
        free(msg);
        return;
    }
    console = input->console;
    if (!console)
        input->console = allocate_console(output, input, msg);
    else
    {
        while (console->next)
            console = console->next;
        console->next = allocate_console(output, input, msg);
    }    
}


void print_console(t_console *head)
{
    uint32_t tmp;
    while (head)
    {
        for (int i = 0; i < head->output->nb_bytes / 4; i++)
        {
            tmp = ((uint32_t*)(head->output->bytes))[i];
            ft_printf("%08x ", __bswap_32(tmp));
        }
        ft_printf("\n");
        head = head->next;
    }
}