#pragma once

#include "exercise.h"

extern const char* FILE_NAME;

void saveToFile(EXERCISE* exercises, int count);
EXERCISE* loadFromFile(int* count);