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
    msg[ft_strlen(msg) - 1] = 0;
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
        ft_printf("(\"%s\") ", head->msg);
        for (int i = 0; i < head->output->nb_bytes / 4; i++)
        {
            tmp = ((uint32_t*)(head->output->bytes))[i];
            ft_printf("%08x ", __bswap_32(tmp));
        }
        ft_printf("\n");
        head = head->next;
    }
}

void handle_noninteractive(t_input *input)
{
    char *line;
    char buffer[BUFFER_SIZE];

    line = NULL;
    ft_memset(buffer, 0, BUFFER_SIZE);
    while((input->flags & CONSOLE_FLAG) && fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        if (line)
        {
            line = realloc(line, ft_strlen(line) + ft_strlen(buffer) + 1);
            line = ft_strcat(line, buffer);
        }
        else 
        {
            line = calloc(BUFFER_SIZE, sizeof(char));
            line = ft_strcpy(line, buffer);
        }
    }
    if (line)
    {
        add_to_console(input->alg_func(line), input, line);
        input->alg_func(line);
    }
}

void handle_interactive(t_input *input)
{
    char *line;
    char buffer[BUFFER_SIZE];

    line = NULL;
    ft_memset(buffer, 0, BUFFER_SIZE);
    while((input->flags & CONSOLE_FLAG) && fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        if (line && !ft_strstr(line, "\n"))
        {
            line = realloc(line, ft_strlen(line) + ft_strlen(buffer) + 1);
            line = ft_strcat(line, buffer);
        }
        else
        {
            line = calloc(BUFFER_SIZE, sizeof(char));
            line = ft_strcpy(line, buffer);
        }
        if ((ft_strlen(buffer) + 1 < BUFFER_SIZE) || ft_strstr(buffer, "\n"))
        {
            add_to_console(input->alg_func(line), input, line);
            input->alg_func(line);
            line = NULL;
        }
    }
    if (line)
    {
        add_to_console(input->alg_func(line), input, line);
        input->alg_func(line);
    }
}