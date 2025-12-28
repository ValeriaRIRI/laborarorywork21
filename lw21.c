#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "array.h"


int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    football_t players[SIZE];
    int count = 0;
    int choice;
    int current_day, current_month, current_year;

    printf("Введите сегодняшнюю дату (день месяц год): ");
    scanf("%d %d %d", &current_day, &current_month, &current_year);
    getchar();

    do {
        print_menu();
        printf("Выберите действие (0-8): ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
        case 1: // Инициализация
            fill_array(players, SIZE);
            count = SIZE;
            printf("Массив инициализирован (%d записей)\n", count);
            break;

        case 2: // Загрузка из файла
            count = input_file("players_out.txt", players);
            printf("Загружено %d записей из файла\n", count);
            if (count > 0) print_array(players, count);
            break;

        case 3: // Вывод массива
            if (count == 0) {
                printf("Массив пуст.\n");
            }
            else {
                print_array(players, count);
            }
            break;

        case 4: // Изменение записи
            if (count == 0) {
                printf("Массив пуст.\n");
            }
            else {
                change_record(players, count);
            }
            break;

        case 5: // Поиск по фамилии
            if (count == 0) {
                printf("Массив пуст.\n");
            }
            else {
                printf("Введите фамилию для поиска: ");
                char surname[m];
                fgets(surname, sizeof(surname), stdin);
                surname[strcspn(surname, "\n")] = 0;

                football_t* found = search_surname(players, count, surname);
                if (found != NULL) {
                    printf("Найден игрок:\n");
                    print_player(*found);
                }
                else {
                    printf("Игрок с фамилией '%s' не найден\n", surname);
                }
            }
            break;

        case 6: // Сортировка по играм
            if (count == 0) {
                printf("Массив пуст.\n");
            }
            else {
                sort_by_games(players, count);
            }
            break;

        case 7: // Сохранение в файл
            if (count == 0) {
                printf("Массив пуст. Сначала: 1(инициализация) или 2(загрузка)\n");
            }
            else {
                output_file("players_out.txt", players, count);  
            }
            break;


        case 8: // Поиск молодых защитников и запись в файл
            if (count == 0) {
                printf("Массив пуст.\n");
            }
            else {
                int found_count = 0;
                writeYoungDefendersToFile(players, count, current_year, current_month, current_day, &found_count);
                if (found_count == 0) {
                    printf("Подходящих футболистов не найдено.\n");
                }
            }
            break;

        case 0:
            printf("Выход из программы.\n");
            break;

        default:
            printf("Такой операции не существует   \n");
        }
        printf("\n");
    } while (choice != 0);

    return 0;
}

