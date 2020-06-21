#include "ft_ssl.h"

void handle_file(char *filename, t_input *input)
{
    FILE *file;
    int len;
    char *buffer;

    file = fopen(filename, "r");
    fseek(file, 0, SEEK_END);
    len = ftell(file);
 
    fseek(file, 0L, SEEK_SET);
    if (!(buffer = calloc(len, sizeof(char))))
        ssl_exit("Malloc error", input, -1);
    fread(buffer, sizeof(char), len, file);
    fclose(file);
    ft_printf("buffer : %s", input->alg_func(buffer));
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
            handle_file(filename->name, input);
        }
        
        filename = filename->next;
    }
}