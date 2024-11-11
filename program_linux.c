#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE_1 1
#define BUFFER_SIZE_512 512
#define BUFFER_SIZE_1024 1024

void copy_file(const char *source, const char *destination, size_t buffer_size)
{
    int src_file = open(source, O_RDONLY);
    if (src_file < 0)
    {
        perror("\nCannot open source file.");
        exit(EXIT_FAILURE);
    }

    int dest_file = open(destination, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_file < 0)
    {
        perror("\nCannot open destination file.");
        close(src_file);
        exit(EXIT_FAILURE);
    }

    char *buffer = malloc(buffer_size);
    if (buffer == NULL)
    {
        perror("\nCannot allocat memmory for the buffer.");
        close(src_file);
        close(dest_file);
        exit(EXIT_FAILURE);
    }

    ssize_t bytes_read;
    while ((bytes_read = read(src_file, buffer, buffer_size)) > 0){
        write(dest_file, buffer, bytes_read);
    }

    free(buffer);
    close(src_file);
    close(dest_file);
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Usage: %s <izvorna_datoteka> <odredi�na_datoteka> <velicina_buffera>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t buffer_size;
    if (strcmp(argv[3], "1") == 0)
    {
        buffer_size = BUFFER_SIZE_1;
    }
    else if (strcmp(argv[3], "512") == 0)
    {
        buffer_size = BUFFER_SIZE_512;
    }
    else if (strcmp(argv[3], "1024") == 0)
    {
        buffer_size = BUFFER_SIZE_1024;
    }
    else
    {
        fprintf(stderr, "Neva�eca velicina buffera. Odaberite 1, 512 ili 1024.\n");
        return 1;
    }

    copy_file(argv[1], argv[2], buffer_size);
    return 0;
}