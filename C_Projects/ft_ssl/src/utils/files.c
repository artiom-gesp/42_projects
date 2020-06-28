#include "ft_ssl.h"

void print_files(t_filename *head)
{
    while (head)
    {
        for (int i = 0; i < head->output->nb_bytes / 4; i++)
        {
            ft_printf("%08x ", __bswap_32(((uint32_t*)(head->output->bytes))[i]));
        }
        ft_printf("\n");
        head = head->next;
    }
}

void handle_file(t_filename *filename, t_input *input)
{
    FILE *file;
    int len;
    char *buffer;

    file = fopen(filename->name, "r");
    fseek(file, 0, SEEK_END);
    len = ftell(file);
 
    fseek(file, 0L, SEEK_SET);
    if (!(buffer = calloc(len, sizeof(char))))
        ssl_exit("Malloc error", input, -1);
    fread(buffer, sizeof(char), len, file);
    fclose(file);
    filename->output = ft_md5(buffer);
    free(buffer);
}

void handle_files(t_input *input)
{
    t_filename *filename;

    filename = input->filenames;
    if (!filename)
        return;
    while (filename)
    {
        if (access(filename->name, F_OK))
        {
            ft_printf("%s: No such file or directory\n", filename->name);
        }
        else
        {
            handle_file(filename, input);
        }
        filename = filename->next;
    }
}