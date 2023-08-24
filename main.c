#include "monty.h"
bus_t bus = {NULL, NULL, NULL, 0};

int main(int argc, char *argv[])
{
    char *content;
    FILE *file;
    size_t size = 0;
    ssize_t read_line = 1;
    stack_t *stack = NULL;
    unsigned int counter = 0;

    if (argc != 2)
    {
        fprintf(stderr, "USAGE: monty file\n");
        exit(EXIT_FAILURE);
    }
    file = fopen(argv[1], "r");
    bus.file = file;
    if (!file)
    {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    while (read_line > 0)
    {
        content = NULL;
        // Use getline to read a line from the file into the content buffer
        read_line = getline(&content, &size, file);

        // Remove the newline character from the end of the line if it exists
        if (read_line > 0 && content[read_line - 1] == '\n')
        {
            content[read_line - 1] = '\0';
            read_line--; // Update the length after removing newline
        }

        bus.content = content;
        counter++;
        if (read_line > 0)
        {
            execute(content, &stack, counter, file);
        }
        free(content);
    }
    free_stack(stack);
    fclose(file);
    return 0;
}

