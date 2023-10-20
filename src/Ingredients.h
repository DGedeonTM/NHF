#ifndef INGREDIENTS_H
#define INGREDIENTS_H

typedef struct Date{
    int i_year;
    int i_month;
    int i_day;
}Date;

typedef struct Ingredients{
    int i_weight;
    char c_unit[11];
    char c_ingredients_name[51];
    Date D_expiration_date;
    struct Ingredients *I_next;
}Ingredients;

#endif