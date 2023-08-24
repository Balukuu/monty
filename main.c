#include "monty.h"
bus_t bus = {NULL, NULL, NULL, 0};
/**
* main - monty code interpreter
* @argc: number of arguments
* @argv: monty file location
* Return: 0 on success
*/
int main(int argc, char *argv[])
{
    char *content;
    FILE *file;
    size_t size = 1024;
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
    content = (char *)malloc(size * sizeof(char));
    if (!content)
    {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    while (fgets(content, size, file) != NULL)
    {
        size_t len = strlen(content);
        if (len > 0 && content[len - 1] == '\n')
        {
            content[len - 1] = '\0';
        }

        bus.content = content;
        counter++;
        execute(content, &stack, counter, file);
    }

    free(content);
    free_stack(stack);
    fclose(file);
    return 0;
}
