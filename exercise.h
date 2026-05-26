#ifndef EXERCISE_H
#define EXERCISE_H

#define MAX_NAME 50
#define CLEAR_BUFFER() while(getchar() != '\n')

static inline void clearInputBuffer(void) {
    while (getchar() != '\n');
}

typedef enum {
    ADD_EXERCISE = 1,
    VIEW_EXERCISES,
    UPDATE_EXERCISE,
    DELETE_EXERCISE,
    SORT_EXERCISES,
    SEARCH_EXERCISE,
    FILE_INFO,
    LINKED_LIST_VIEW,
    EXIT_PROGRAM
}MENUOPTION;

typedef union {
    float kilograms;
    int bodyweight;
}EXERCISEDATA;

typedef struct {
    int id;
    char name[MAX_NAME];
    int sets;
    int reps;
    float weight;
    float personalRecord;
    EXERCISEDATA data;
}EXERCISE;

typedef struct Node {
    EXERCISE exercise;
    struct Node* next;
}Node;

void addExercise(void);
void viewExercises(void);
void updateExercise(void);
void deleteExercise(void);
void sortExercises(void);
void searchExercise(void);
void showFileInfo(void);
void linkedListView(void);


#endif
