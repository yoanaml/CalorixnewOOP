#pragma once
#include "Exercise.h"
#include "../Date/Date.h"

class ExerciseEntry
{
private:
    int              s8EntryId;
    const Exercise& exercise;
    int              s8DurationMinutes;
    Date             date;

public:
    static int s8IdGenerator;

    ExerciseEntry(const Exercise& exercise, int s8DurationMinutes, const Date& date);

    int             getEntryId()        const;
    const Exercise& getExercise()       const;
    int             getDurationMinutes() const;
    Date            getDate()           const;

    double calculateBurnedCalories() const;
};