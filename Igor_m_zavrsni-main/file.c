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
        perror("Error opening file");
        return;
    }

    fwrite(&count, sizeof(int), 1, fp);
    fwrite(exercises, sizeof(EXERCISE), count, fp);

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

    EXERCISE* exercises = (EXERCISE*)malloc(*count * sizeof(EXERCISE));

    if (exercises == NULL)
    {
        perror("Memory allocation failed");
        fclose(fp);
        return NULL;
    }

    fread(exercises, sizeof(EXERCISE), *count, fp);

    fclose(fp);

    return exercises;
}