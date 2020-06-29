#include "ft_ssl.h"

t_string *allocate_string(t_bytes *output, t_input *input, char *msg)
{
    t_string *string;

    if (!(string = malloc(sizeof(t_string))))
    {
        free(msg);
        free(output->bytes);
        free(output);
        ssl_exit("Malloc failed", input, -1);
    }
    string->str = msg;
    string->output = output;
    string->next = NULL;
    return string;
}

void add_to_string(t_bytes *output, t_input *input, char *msg)
{   
    t_string *string;
    if (!output)
    {
        free(msg);
        return;
    }
    string = input->strings;
    if (!string)
        input->strings = allocate_string(output, input, msg);
    else
    {
        while (string->next)
            string = string->next;
        string->next = allocate_string(output, input, msg);
    }    
}

void print_string(t_string *head)
{
    uint32_t tmp;
    while (head)
    {
        ft_printf("(\"%s\") ", head->str);
        for (int i = 0; i < head->output->nb_bytes / 4; i++)
        {
            tmp = ((uint32_t*)(head->output->bytes))[i];
            ft_printf("%08x ", __bswap_32(tmp));
        }
        ft_printf("\n");
        head = head->next;
    }
}