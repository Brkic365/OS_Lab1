#include <stdio.h>
#include <stdlib.h>

void generate_file(const char *filename, size_t size)
{
    FILE *file = fopen(filename, "wb");
    if (file == NULL){
        perror("\nCannot open file for writing.");
        exit(1);
    }

    for (size_t i = 0; i < size; i++){
        fputc(rand() % 256, file);
    }

    fclose(file);
}

int main()
{
    generate_file("mala_datoteka.bin", 1);
    generate_file("srednja_datoteka.bin", 100 * 1024 * 1024);
    generate_file("velika_datoteka.bin", 1024 * 1024 * 1024);

    return 0;
}