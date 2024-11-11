#!/bin/bash

# Using `cp` for copying
for size in 1 512 1024; do
    for file in mala_datoteka srednja_datoteka velika_datoteka; do
        echo "Mjerenje za file $file.bin koji ima buffer size: $size"
        for i in {1..3}; do
            /usr/bin/time -f "%e" cp "$file.bin" "${file}_$size.bin" > /dev/null 2>&1
        done
    done
done

# Using `program.c` for copying with SECONDS for time measurement
for size in 1 512 1024; do
    for file in mala_datoteka srednja_datoteka velika_datoteka; do
        echo "Mjerenje za file $file.bin koji ima buffer size: $size"
        for i in {1..3}; do
            SECONDS=0
            ./program "$file.bin" "${file}_$size.bin" "$size" > /dev/null 2>&1
            elapsed=$SECONDS
            echo "Elapsed time (program.c): $elapsed seconds"
        done
    done
done

# Using `program_linux.c` for copying
for size in 1 512 1024; do
    for file in mala_datoteka srednja_datoteka velika_datoteka; do
         echo "Mjerenje za file $file.bin koji ima buffer size: $size"
        for i in {1..3}; do
            SECONDS=0
            ./program_linux "$file.bin" "${file}_$size.bin" "$size" > /dev/null 2>&1
            elapsed=$SECONDS
            echo "Elapsed time (program_linux.c): $elapsed seconds"
        done
    done
done