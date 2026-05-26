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
        printf("6. Search exercise\n");
        printf("7. File info\n");
        printf("8. Linked list view\n");
        printf("9. Exit\n");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            clearInputBuffer();
            choice = 0;
            continue;
        }

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
        case SEARCH_EXERCISE:
            searchExercise();
            break;
        case FILE_INFO:
            showFileInfo();
            break;
        case LINKED_LIST_VIEW:
            linkedListView();
            break;

        case EXIT_PROGRAM:
            break;

        default:
            printf("Invalid option!\n");
        }

    } while (choice != EXIT_PROGRAM);
}
