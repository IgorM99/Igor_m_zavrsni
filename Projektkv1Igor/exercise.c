#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "exercise.h"
#include "file.h"

int findNextId(void) {
    int count = 0;
    EXERCISE* exercises = loadFromFile(&count);
    if (exercises == NULL || count == 0)
    {
        return 1;
    }
    int maxId = exercises[0].id;
    for (int i = 1; i < count; i++) {
        if (exercises[i].id > maxId) {
            maxId = exercises[i].id;
        }
    }
    free(exercises);
    exercises = NULL;
    return maxId + 1;
}

void addExercise(void)
{
    int count = 0;

    EXERCISE* exercises = loadFromFile(&count);

    EXERCISE newExercise;

    newExercise.id = findNextId();                                            
                                            
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
    int count=0;
    EXERCISE* exercises = loadFromFile(&count);

    if (exercises == NULL) {
        return;
    }
    int id;

    printf("Enter exercise ID: ");
    scanf("%d", &id);
    int found = 0;

    for (int i = 0; i < count; i++)
    {
        if (exercises[i].id == id) {
            found = 1;

            printf("New weight: ");
            scanf("%f", &exercises[i].weight);

            if (exercises[i].weight > exercises[i].personalRecord) {
                exercises[i].personalRecord = exercises[i].weight;
            }
            break;
        }
    }
    if (!found) {
        printf("Exercise not found.\n");
    }
    else {
        saveToFile(exercises, count);
        printf("Exercise updated.\n");
    }
    free(exercises);
    exercises = NULL;
}
 
void deleteExercise(void)
{
   int count=0;
   EXERCISE* exercises = loadFromFile(&count);

   if (exercises == NULL) {
       return;
   }
   int id;
   printf("Enter ID to delete: ");
   scanf("%d", &id);
   FILE* tempFile = fopen("temp.bin", "wb");
   if (tempFile == NULL) {
       perror("Temp file error");
       free(exercises);
       return;
   }
   int newCount = 0;
   fwrite(&newCount,sizeof(int), 1, tempFile);
   for (int i = 0; i < count; i++) {
       if (exercises[i].id != id)
       {
           fwrite(&exercises[i], sizeof(EXERCISE), 1, tempFile);
           newCount++;
       }
   }
   rewind(tempFile);
   fwrite(&newCount, sizeof(int), 1, tempFile);
   fclose(tempFile);
   remove(FILE_NAME);
   rename("temp.bin", FILE_NAME);
   free(exercises);
   exercises == NULL;
   printf("Exercise deleted.\n");
}

int compareByWeight(const void* a, const void* b)
{
    EXERCISE* e1 = (EXERCISE*)a;
    EXERCISE* e2 = (EXERCISE*)b;

    if (e1->weight > e2->weight)
        return -1;

    if (e1->weight < e2->weight)
        return 1;

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

int compareById(const void* key, const void* element)
{
    int id = *(int*)key;
    EXERCISE* exercise = (EXERCISE*)element;
    return id - exercise->id;
}

void searchExercise(void) {
    int count = 0;
    EXERCISE* exercises = loadFromFile(&count);
    if (exercises == NULL) {
        return;
    }
    qsort(exercises, count, sizeof(EXERCISE), compareById);
    int id;
    printf("Enter ID: ");
    scanf("%d", &id);

    EXERCISE* found = (EXERCISE*)bsearch(&id, exercises, count, sizeof(EXERCISE), compareById);
    if (found != NULL) {
        printf("\nExercise found : \n");
        printf("Name: %s\n", found->name);
        printf("Weight: %.2f\n", found->weight);
    }
    else {
        printf("Exercise not found.\n");
    }
    free(exercises);
    exercises = NULL;
}

void showFileInfo(void) {
    FILE* fp = fopen(FILE_NAME, "rb");

    if (fp == NULL) {
        perror("File error");
        return;
    }
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);
    printf("File size: %ld bytes\n", size);
    fclose(fp);
}