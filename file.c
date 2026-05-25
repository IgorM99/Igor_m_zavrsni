#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "file.h"

const char* FILE_NAME = "data.bin";

void saveToFile(EXERCISE* exercises, int count)
{
    FILE* fp = fopen(FILE_NAME, "wb");

    if (fp == NULL)
    {
        perror("File open error");
        return;
    }

    fwrite(&count, sizeof(int), 1, fp);

    fwrite(exercises,
        sizeof(EXERCISE),
        count,
        fp);

    if (ferror(fp))
    {
        printf("Write error: %s\n", strerror(errno));
    }

    fclose(fp);
}

EXERCISE* loadFromFile(int* count)
{
    FILE* fp = fopen(FILE_NAME, "rb");

    if (fp == NULL)
    {
        *count = 0;
        return NULL;
    }

    fread(count, sizeof(int), 1, fp);

    EXERCISE* exercises =
        (EXERCISE*)calloc(*count,
            sizeof(EXERCISE));

    if (exercises == NULL)
    {
        perror("Memory allocation error");

        fclose(fp);

        return NULL;
    }

    fread(exercises,
        sizeof(EXERCISE),
        *count,
        fp);

    if (feof(fp))
    {
        printf("End of file reached.\n");
    }

    fclose(fp);

    return exercises;
}

void copyFile(const char* source,
    const char* destination)
{
    FILE* src = fopen(source, "rb");
    FILE* dest = fopen(destination, "wb");

    if (src == NULL || dest == NULL)
    {
        perror("Copy file error");
        return;
    }

    char ch;

    while ((ch = fgetc(src)) != EOF)
    {
        fputc(ch, dest);
    }

    fclose(src);
    fclose(dest);
}