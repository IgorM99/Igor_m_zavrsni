#ifndef FILE_H
#define FILE_H

#include "exercise.h"

extern const char* FILE_NAME;

void saveToFile(EXERCISE* exercises, int count);
EXERCISE* loadFromFile(int* count);
void copyFile(const char* source, const char* destination);

#endif