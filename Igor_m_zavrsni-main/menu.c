#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#include "exercise.h"

void menu(void)
{
    int choice;

    do
    {
        printf("\n=== GYM TRACKER ===\n");
        printf("1. Add exercise\n");
        printf("2. View exercises\n");
        printf("3. Update exercise\n");
        printf("4. Delete exercise\n");
        printf("5. Sort exercises\n");
        printf("6. Exit\n");

        scanf("%d", &choice);

        switch (choice)
        {
        case ADD_EXERCISE:
            addExercise();
            break;

        case VIEW_EXERCISES:
            viewExercises();
            break;

        case UPDATE_EXERCISE:
            updateExercise();
            break;

        case DELETE_EXERCISE:
            deleteExercise();
            break;

        case SORT_EXERCISES:
            sortExercises();
            break;

        case EXIT_PROGRAM:
            break;

        default:
            printf("Invalid option!\n");
        }

    } while (choice != EXIT_PROGRAM);
}