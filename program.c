#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE_1 1
#define BUFFER_SIZE_512 512
#define BUFFER_SIZE_1024 1024

void copy_file(const char *source, const char *destination, size_t buffer_size) {
    FILE *src_file = fopen(source, "rb");
    if (src_file == NULL) {
        perror("\nCannot open source file.");
        exit(EXIT_FAILURE);
    }

    FILE *dest_file = fopen(destination, "wb");
    if (dest_file == NULL) {
        perror("\nCannot open destination file.");
        fclose(src_file);
        exit(EXIT_FAILURE);
    }

    char *buffer = malloc(buffer_size);
    if (buffer == NULL) {
        perror("\nCannot allocat memmory for the buffer.");
        fclose(src_file);
        fclose(dest_file);
        exit(EXIT_FAILURE);
    }

    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, buffer_size, src_file)) > 0) {
        fwrite(buffer, 1, bytes_read, dest_file);
    }

    free(buffer);
    fclose(src_file);
    fclose(dest_file);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <source_file> <destination_file> <buffer_size>\n", argv[0]);
        return 1;
    }

    size_t buffer_size;
    if (strcmp(argv[3], "1") == 0) {
        buffer_size = BUFFER_SIZE_1;
    } else if (strcmp(argv[3], "512") == 0) {
        buffer_size = BUFFER_SIZE_512;
    } else if (strcmp(argv[3], "1024") == 0) {
        buffer_size = BUFFER_SIZE_1024;
    } else {
        fprintf(stderr, "Wrong buffer size. Select 1, 512 ili 1024.\n");
        return 1;
    }

    copy_file(argv[1], argv[2], buffer_size);
    return 0;
}