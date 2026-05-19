#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "exercise.h"
#include "file.h"

static int nextId = 1;

void addExercise(void)
{
    int count = 0;

    EXERCISE* exercises = loadFromFile(&count);

    EXERCISE newExercise;

    newExercise.id = nextId++;

    printf("Exercise name: ");
    scanf(" %49[^\n]", newExercise.name);

    printf("Sets: ");
    scanf("%d", &newExercise.sets);

    printf("Reps: ");
    scanf("%d", &newExercise.reps);

    printf("Weight: ");
    scanf("%f", &newExercise.weight);

    newExercise.personalRecord = newExercise.weight;

    EXERCISE* temp = (EXERCISE*)malloc((count + 1) * sizeof(EXERCISE));

    if (temp == NULL)
    {
        perror("Memory allocation failed");
        free(exercises);
        return;
    }

    for (int i = 0; i < count; i++)
    {
        temp[i] = exercises[i];
    }

    temp[count] = newExercise;

    saveToFile(temp, count + 1);

    free(exercises);
    free(temp);
}

void viewExercises(void)
{
    int count = 0;

    EXERCISE* exercises = loadFromFile(&count);

    if (exercises == NULL || count == 0)
    {
        printf("No exercises found.\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        printf("\nID: %d\n", exercises[i].id);
        printf("Name: %s\n", exercises[i].name);
        printf("Sets: %d\n", exercises[i].sets);
        printf("Reps: %d\n", exercises[i].reps);
        printf("Weight: %.2f\n", exercises[i].weight);
        printf("PR: %.2f\n", exercises[i].personalRecord);
    }

    free(exercises);
}

void updateExercise(void)
{
    printf("Update function...\n");
}

void deleteExercise(void)
{
    printf("Delete function...\n");
}

int compareByWeight(const void* a, const void* b)
{
    EXERCISE* e1 = (EXERCISE*)a;
    EXERCISE* e2 = (EXERCISE*)b;

    if (e1->weight > e2->weight)
        return 1;

    if (e1->weight < e2->weight)
        return -1;

    return 0;
}

void sortExercises(void)
{
    int count = 0;

    EXERCISE* exercises = loadFromFile(&count);

    if (exercises == NULL)
        return;

    qsort(exercises, count, sizeof(EXERCISE), compareByWeight);

    saveToFile(exercises, count);

    free(exercises);

    printf("Exercises sorted.\n");
}