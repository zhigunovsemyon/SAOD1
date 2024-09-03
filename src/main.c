#include "main.h"

int main (const int argc, const char** argv) {
    /*Если пользователь не указал аргументы функции, 
     * ему выведется инструкция по использованию программы */
    if (argc < 2) {
        usage(argv[0]);
        return EXIT_SUCCESS;
    }
    puts(argv[argc - 1]);
    return EXIT_SUCCESS;
}

void usage(const char* exename) {
    printf("%s [действие] ПУТЬ К ФАЙЛУ\n\n", exename);

    printf("Возможные действия над списком:\n");
    printf("\t%s ПАРАМЕТР\t%s\n", SORTAKEY ,"Сортировка по возрастанию");
    printf("\t%s ПАРАМЕТР\t%s\n", SORTDKEY ,"Сортировка по убыванию");

    printf("\t\t%s\t\t%s\n", SURNAMEKEY ,"Сортировка по фамилиям");
    printf("\t\t%s\t\t%s\n", NAMEKEY, "Сортировка по именам");
    printf("\t\t%s\t%s\n", PATRONIMKEY, "Сортировка по отчествам");
    printf("\t\t%s\t\t%s\n", NUMKEY, "Сортировка по номеру в журнале");
    printf("\t\t%s\t\t%s\n", IDKEY, "Сортировка по номеру зачётной книжки");
    printf("\t\t%s\t\t%s\n", L1KEY, "Сортировка по первому предмету");
    printf("\t\t%s\t\t%s\n", L2KEY, "Сортировка по второму предмету");
    printf("\t\t%s\t\t%s\n", L3KEY, "Сортировка по третьему предмету");
    printf("\t\t%s\t\t%s\n", L4KEY, "Сортировка по четвёртому предмету");
    printf("\t\t%s\t%s\n\n", L5KEY, "Сортировка по пятому предмету");

    printf("\t%s ЗАПРОС\t\t%s\n", SEARCHKEY ,"Поиск среди полей");
    printf("\t%s\tВывод этой справки\n", HELPKEY);
}
