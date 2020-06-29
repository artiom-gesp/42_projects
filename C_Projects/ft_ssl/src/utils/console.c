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
        ft_printf("(\"stdin\") ");
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
    uint8_t read_bytes;
    uint64_t total_read_byte;
    char buffer[BUFFER_SIZE];

    line = NULL;
    ft_memset(buffer, 0, BUFFER_SIZE);
    total_read_byte = 0;
    while ((input->flags & CONSOLE_FLAG))
    {
        read_bytes = fread(buffer,  sizeof(char), BUFFER_SIZE, stdin);
        if (line)
        {
            line = realloc(line, total_read_byte + read_bytes + 1);
            ft_memcpy(line + total_read_byte, buffer, read_bytes);
        }
        else 
        {
            line = calloc(BUFFER_SIZE, sizeof(char));
            line = ft_memcpy(line, buffer, read_bytes);
        }
        total_read_byte += read_bytes;
        if (read_bytes < BUFFER_SIZE)
            if (feof(stdin))
                break;
    }
    if (line)
        add_to_console(input->alg_func((t_bytes){line, total_read_byte}), input, line);
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
        if (ft_strstr(buffer, "\n"))
        {
            add_to_console(input->alg_func((t_bytes){line, ft_strlen(line)}), input, line);
            line = NULL;
        }
    }
    if (line)
        add_to_console(input->alg_func((t_bytes){line, ft_strlen(line)}), input, line);
}