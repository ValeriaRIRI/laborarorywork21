#pragma once
#ifndef ARRAY_H
#define ARRAY_H
#define SIZE 5
#define m 10

typedef struct Date {
    int day;
    int month;
    int year;
} date_t;

typedef struct Football {
    char surname[m];
    char club[m];
    char role[m];
    int game;
    char place[m];
    date_t birth_date;
} football_t;

int fill_array(football_t* players, int size);
int print_array(football_t* players, int size);
int print_player(football_t player);
football_t* search_surname(football_t* players, int size, const char* surname);
int compare_games(const void* a, const void* b);
int sort_by_games(football_t* players, int size);
int input_file(const char* filename, football_t* arr);
int output_file(const char* filename, football_t* arr, int n);
int print_menu(void);
int edit_player(football_t* player);
int change_record(football_t* players, int size);
int age(int year, int month, int day, int cur_year, int cur_month, int cur_day);
int writeYoungDefendersToFile(football_t* players, int size, int current_year, int current_month, int current_day, int* count);

#endif