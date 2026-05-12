#pragma once

#define MAX_NAME 50

typedef enum {
    ADD_EXERCISE = 1,
    VIEW_EXERCISES,
    UPDATE_EXERCISE,
    DELETE_EXERCISE,
    SORT_EXERCISES,
    EXIT_PROGRAM
}MENUOPTION;

typedef struct {
    int id;
    char name[MAX_NAME];
    int sets;
    int reps;
    float weight;
    float personalRecord;
}EXERCISE;

void addExercise(void);
void viewExercises(void);
void updateExercise(void);
void deleteExercise(void);
void sortExercises(void);

