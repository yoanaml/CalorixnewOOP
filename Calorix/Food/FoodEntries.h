#pragma once
#include "Food.h"
#include "../Date/Date.h"

class FoodEntry
{
private:
    int    s8EntryId;
    Food& food;
    double f32QuantityGrams;
    Date   date;

public:
    static int s8IdGenerator;

    FoodEntry(Food& food, double f32QuantityGrams, const Date& date);

    int           getEntryId()       const;
    const Food& getFood()          const;
    double        getQuantityGrams() const;
    Date          getDate()          const;

    double calculateCalories() const;
    double calculateProtein()  const;
    double calculateCarbs()    const;
    double calculateFat()      const;
};
