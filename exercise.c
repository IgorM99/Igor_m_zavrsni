#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "exercise.h"
#include "file.h"

static int recursiveBinarySearch(EXERCISE* exercises,
    int left,
    int right,
    int id)
{
    if (left > right)
    {
        return -1;
    }

    int middle = (left + right) / 2;

    if (exercises[middle].id == id)
    {
        return middle;
    }

    if (id < exercises[middle].id)
    {
        return recursiveBinarySearch(exercises,
            left,
            middle - 1,
            id);
    }

    return recursiveBinarySearch(exercises,
        middle + 1,
        right,
        id);
}

int compareByWeight(const void* a,
    const void* b)
{
    EXERCISE* e1 = (EXERCISE*)a;
    EXERCISE* e2 = (EXERCISE*)b;

    if (e1->weight > e2->weight)
    {
        return -1;
    }

    if (e1->weight < e2->weight)
    {
        return 1;
    }

    return 0;
}

int compareById(const void* key,
    const void* element)
{
    int id = *(int*)key;

    EXERCISE* exercise =
        (EXERCISE*)element;

    return id - exercise->id;
}

static int findNextId(void)
{
    int count = 0;

    EXERCISE* exercises =
        loadFromFile(&count);

    if (exercises == NULL || count == 0)
    {
        return 1;
    }

    int maxId = exercises[0].id;

    for (int i = 1; i < count; i++)
    {
        if (exercises[i].id > maxId)
        {
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

    EXERCISE* exercises =
        loadFromFile(&count);

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

    newExercise.personalRecord =
        newExercise.weight;

    newExercise.data.kilograms =
        newExercise.weight;

    EXERCISE* temp =
        (EXERCISE*)realloc(
            exercises,
            (count + 1) * sizeof(EXERCISE)
        );

    if (temp == NULL)
    {
        perror("Realloc failed");

        free(exercises);

        return;
    }

    exercises = temp;

    exercises[count] = newExercise;

    saveToFile(exercises,
        count + 1);

    free(exercises);

    exercises = NULL;
}

void viewExercises(void)
{
    int count = 0;

    EXERCISE* exercises =
        loadFromFile(&count);

    if (exercises == NULL || count == 0)
    {
        printf("No exercises found.\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        printf("\nID: %d\n",
            exercises[i].id);

        printf("Name: %s\n",
            exercises[i].name);

        printf("Sets: %d\n",
            exercises[i].sets);

        printf("Reps: %d\n",
            exercises[i].reps);

        printf("Weight: %.2f\n",
            exercises[i].weight);

        printf("PR: %.2f\n",
            exercises[i].personalRecord);
    }

    free(exercises);

    exercises = NULL;
}

void updateExercise(void)
{
    int count = 0;

    EXERCISE* exercises =
        loadFromFile(&count);

    if (exercises == NULL)
    {
        return;
    }

    int id;

    printf("Enter ID: ");
    scanf("%d", &id);

    int foundIndex =
        recursiveBinarySearch(exercises,
            0,
            count - 1,
            id);

    if (foundIndex == -1)
    {
        printf("Exercise not found.\n");

        free(exercises);

        return;
    }

    printf("New weight: ");

    scanf("%f",
        &exercises[foundIndex].weight);

    if (exercises[foundIndex].weight >
        exercises[foundIndex].personalRecord)
    {
        exercises[foundIndex].personalRecord =
            exercises[foundIndex].weight;
    }

    saveToFile(exercises,
        count);

    free(exercises);

    exercises = NULL;
}

void deleteExercise(void)
{
    int count = 0;

    EXERCISE* exercises =
        loadFromFile(&count);

    if (exercises == NULL)
    {
        return;
    }

    int id;

    printf("Enter ID to delete: ");
    scanf("%d", &id);

    FILE* tempFile =
        fopen("temp.bin", "wb");

    if (tempFile == NULL)
    {
        perror("Temp file error");

        free(exercises);

        return;
    }

    int newCount = 0;

    fwrite(&newCount,
        sizeof(int),
        1,
        tempFile);

    for (int i = 0; i < count; i++)
    {
        if (exercises[i].id != id)
        {
            fwrite(&exercises[i],
                sizeof(EXERCISE),
                1,
                tempFile);

            newCount++;
        }
    }

    rewind(tempFile);

    fwrite(&newCount,
        sizeof(int),
        1,
        tempFile);

    fclose(tempFile);

    remove(FILE_NAME);

    rename("temp.bin",
        FILE_NAME);

    free(exercises);

    exercises = NULL;

    printf("Exercise deleted.\n");
}

void sortExercises(void)
{
    int count = 0;

    EXERCISE* exercises =
        loadFromFile(&count);

    if (exercises == NULL)
    {
        return;
    }

    qsort(exercises,
        count,
        sizeof(EXERCISE),
        compareByWeight);

    saveToFile(exercises,
        count);

    free(exercises);

    exercises = NULL;

    printf("Exercises sorted by weight descending.\n");
}

void searchExercise(void)
{
    int count = 0;

    EXERCISE* exercises =
        loadFromFile(&count);

    if (exercises == NULL)
    {
        return;
    }

    qsort(exercises,
        count,
        sizeof(EXERCISE),
        compareById);

    int id;

    printf("Enter ID: ");
    scanf("%d", &id);

    EXERCISE* found =
        (EXERCISE*)bsearch(
            &id,
            exercises,
            count,
            sizeof(EXERCISE),
            compareById
        );

    if (found != NULL)
    {
        printf("\nExercise found:\n");

        printf("Name: %s\n",
            found->name);

        printf("Weight: %.2f\n",
            found->weight);
    }
    else
    {
        printf("Exercise not found.\n");
    }

    free(exercises);

    exercises = NULL;
}

void showFileInfo(void)
{
    FILE* fp = fopen(FILE_NAME,
        "rb");

    if (fp == NULL)
    {
        perror("File error");
        return;
    }

    fseek(fp,
        0,
        SEEK_END);

    long size =
        ftell(fp);

    rewind(fp);

    printf("File size: %ld bytes\n",
        size);

    fclose(fp);
}

void linkedListView(void)
{
    int count = 0;

    EXERCISE* exercises =
        loadFromFile(&count);

    if (exercises == NULL)
    {
        return;
    }

    Node* head = NULL;
    Node* current = NULL;

    for (int i = 0; i < count; i++)
    {
        Node* newNode =
            (Node*)malloc(sizeof(Node));

        newNode->exercise =
            exercises[i];

        newNode->next = NULL;

        if (head == NULL)
        {
            head = newNode;
            current = newNode;
        }
        else
        {
            current->next = newNode;
            current = newNode;
        }
    }

    current = head;

    while (current != NULL)
    {
        printf("%s %.2f kg\n",
            current->exercise.name,
            current->exercise.weight);

        current = current->next;
    }

    current = head;

    while (current != NULL)
    {
        Node* temp = current;

        current = current->next;

        free(temp);
    }

    free(exercises);

    exercises = NULL;
}