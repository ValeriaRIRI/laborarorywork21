#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "array.h"

#define SIZE 5
#define m 10

int print_menu(void) {
    printf("\n=== МЕНЮ ФУТБОЛЬНЫХ ИГРОКОВ ===\n");
    printf("1 - Инициализация массива\n");
    printf("2 - Загрузка из файла (players_out.txt)\n");
    printf("3 - Вывод массива\n");
    printf("4 - Изменение записи\n");
    printf("5 - Поиск по фамилии\n");
    printf("6 - Сортировка по количеству игр\n");
    printf("7 - Сохранение в файл (players_out.txt)\n");
    printf("8 - Молодые защитники в файл (young_defenders.txt)\n");
    printf("0 - Выход\n");
    return 0;
}

// Функция для записи молодых защитников в файл 
int writeYoungDefendersToFile(football_t * players, int size,
    int current_year, int current_month, int current_day, int* count) {
    FILE* file = fopen("young_defenders.txt", "w");
    if (file == NULL) {
        printf("Ошибка создания файла\n");
        return -1;
    }

    *count = 0;
    for (int i = 0; i < size; i++) {
        if (strcmp(players[i].role, "Защитник") == 0) {
            int player_age = age(players[i].birth_date.year, players[i].birth_date.month,
                players[i].birth_date.day, current_year, current_month, current_day);
            if (player_age < 20 && players[i].game >= 40) {
                // Запись в файл
                fprintf(file, "Фамилия: %s\n", players[i].surname);
                fprintf(file, "Дата рождения: %d.%d.%d\n",
                    players[i].birth_date.day, players[i].birth_date.month, players[i].birth_date.year);
                fprintf(file, "Клуб: %s\n", players[i].club);
                fprintf(file, "Амплуа: %s\n", players[i].role);
                fprintf(file, "Количество игр: %d\n", players[i].game);
                fprintf(file, "Место рождения: %s\n", players[i].place);
                fprintf(file, "------------------------\n");

                (*count)++;
            }
        }
    }

    fclose(file);
    printf("Данные записаны в файл 'young_defenders.txt'\n");
    return 0;
}

int age(int year, int month, int day, int cur_year, int cur_month, int cur_day) {
    int age = cur_year - year;
    if (cur_month < month || (cur_month == month && cur_day < day)) {
        age--;
    }
    return age;
}


int fill_array(football_t* players, int size) {
    football_t defaultPlayers[SIZE] = {
        {"Иванов", "Спартак", "Защитник", 45, "Москва", {15, 3, 2005}},
        {"Петров", "Зенит", "Нападающий", 38, "СПб", {10, 7, 2004}},
        {"Сидоров", "ЦСКА", "Защитник", 42, "Москва", {22, 11, 2006}},
        {"Козлов", "Локомотив", "Вратарь", 30, "Ярославль", {5, 1, 2003}},
        {"Морозов", "Динамо", "Вратарь", 25, "Москва", {18, 9, 2005}}
    };

    for (int i = 0; i < size; i++) {
        players[i] = defaultPlayers[i];
    }
    return 0;
}

int print_array(football_t* players, int size) {
    printf("\n+---+------------------+------------------+------------------+------------------+------------------+\n");
    printf("|№    | Фамилия          | Клуб             | Амплуа           | Игр              | Дата рождения    |\n");
    printf(" +----+------------------+------------------+------------------+------------------+------------------+\n");

    for (int i = 0; i < size; i++) {
        printf("|%-2d | ", i + 1);
        print_player(players[i]);
        printf("+---+----------------+------------------+------------------+------------------+------------------+\n");
    }
    return 0;
}

int print_player(football_t player) {
    printf("%-16s | %-16s | %-16s | %-16d | %02d.%02d.%d\n",
        player.surname,
        player.club,
        player.role,
        player.game,
        player.birth_date.day,
        player.birth_date.month,
        player.birth_date.year
    );
    return 0;
}


int change_record(football_t* players, int size) {
    printf("Введите фамилию для поиска записи: ");
    char surname[m];
    fgets(surname, sizeof(surname), stdin);
    surname[strcspn(surname, "\n")] = 0;

    football_t* found = search_surname(players, size, surname);
    if (found != NULL) {
        printf("Найдена запись:\n");
        print_player(*found);
        printf("Изменить эту запись? (1 - yes): ");
        int c;
        scanf(" %d", &c);
        getchar();

        switch (c) {
            case 1: {
                edit_player(found);
                printf("Запись обновлена!\n");
                break;
            }
        } 
    }
    else {
        printf("Игрок с фамилией '%s' не найден\n", surname);
        return -1;
    }
    return 0;
}

int edit_player(football_t* player) {
    printf("\nВведите новые данные через пробел:\n");

    printf("Фамилия (%s): ", player->surname);
    char temp[m];
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp, "\n")] = 0;
    if (strlen(temp) > 0) strcpy(player->surname, temp);

    printf("Клуб (%s): ", player->club);
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp, "\n")] = 0;
    if (strlen(temp) > 0) strcpy(player->club, temp);

    printf("Амплуа (%s): ", player->role);
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp, "\n")] = 0;
    if (strlen(temp) > 0) strcpy(player->role, temp);

    printf("Количество игр (%d): ", player->game);
    int games;
    if (scanf("%d", &games) == 1) {
        player->game = games;
    }
    getchar();

    printf("Место (%s): ", player->place);
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp, "\n")] = 0;
    if (strlen(temp) > 0) strcpy(player->place, temp);
    return 0;
}

football_t* search_surname(football_t* players, int size, const char* surname) {
    for (int i = 0; i < size; i++) {
        if (strcmp(players[i].surname, surname) == 0) {
            return &players[i];
        }
    }
    return NULL;
}

int compare_games(const void* a, const void* b) {
    const football_t* pa = (const football_t*)a;
    const football_t* pb = (const football_t*)b;
    return pa->game - pb->game;
}

int sort_by_games(football_t* players, int size) {
    qsort(players, size, sizeof(football_t), compare_games);
    printf("Массив отсортирован по количеству игр\n");
    print_array(players, size);
    return 0;
}

int input_file(const char* filename, football_t* arr) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("Файл %s не найден\n", filename);
        return 0;
    }

    int i = 0;
    while (i < SIZE && fscanf(f, "%9s %9s %9s %d %9s %d %d %d",
        arr[i].surname, arr[i].club, arr[i].role, &arr[i].game,
        arr[i].place, &arr[i].birth_date.day, &arr[i].birth_date.month,
        &arr[i].birth_date.year) == 8) {
        i++;
    }
    fclose(f);
    return i;
}

int output_file(const char* filename, football_t* arr, int n) {
    FILE* f = fopen(filename, "w");
    if (!f) {
        perror("Ошибка создания файла");
        return -1;
    }

    for (int i = 0; i < n; i++) {
        fprintf(f, "%s %s %s %d %s %d %d %d\n",
            arr[i].surname, arr[i].club, arr[i].role, arr[i].game,
            arr[i].place, arr[i].birth_date.day, arr[i].birth_date.month,
            arr[i].birth_date.year);
    }
    fclose(f);
    return 0;
}
