#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//Файл с ключами
#include "keys.h"

//Коды ошибок
enum Errors {
    ERR_FILENOTFOUND = 1,  //Не удалось открыть файл
    ERR_NOSEARCHPATTERN, //Пользователь не указал строку поиска
    ERR_NOSORTKEY, //Пользователь не указал параметр для сортировки
    ERR_OUTOFMEM, //Не удалось выделить память
};

//Вывод сообщения об использовании программы
void usage(const char* exename);

//Поиск слова TheWord в массиве слов WordList, возрат индекса этого слова, либо -1
int FindTheWord(const char **WordList, int ListLen, const char *TheWord);
int FindTheWord(const char **WordList, int ListLen, const char *TheWord) {
    /*Цикл обходит массив слов WordList для поиска слова TheWord в нём. 
    Если слово найдено, возращается его индекс, в противном случае -- возрат -1 */
    for (int i = 0; i < ListLen; i++) {
        if (!strcmp(WordList[i], TheWord)) {
            return i;
        }
    }
    return -1;
}

int main (const int argc, const char** argv) {
    /*Если пользователь не указал аргументы функции, 
     * ему выведется инструкция по использованию программы */
    if (argc < 2) {
        usage(argv[0]);
        return EXIT_SUCCESS;
    }
    if(-1 != FindTheWord(argv, argc, HELPKEY)) {
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
