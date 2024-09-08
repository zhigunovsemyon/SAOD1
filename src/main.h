#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Коды ошибок
enum Errors {
    ERR_FILENOTFOUND = 1,  //Не удалось открыть файл
    ERR_OUTOFMEM, //Не удалось выделить память
};

//Запись о студенте
struct Record {
    int number; //Номер студента
    char *surname;//Фамилия студента
    char *name;//Имя студента
    char *patronim;//Отчество студента
    char id[8];//Номер студенческого билета
    int marks[5];//Оценки студента
};

/*Сортировка списка List размера count по возрастанию по параметру sortkey
 * Возвращает ноль при удачной сортировке, либо 1, если sortkey некорректный*/
int SortA_List (struct Record *List, int count, const char *sortkey);

/*Сортировка списка List размера count по убыванию по параметру sortkey
 * Возвращает ноль при удачной сортировке, либо 1, если sortkey некорректный*/
int SortD_List (struct Record *List, int count, const char *sortkey);

/* Поиск в записях по строке sortKey
 * Функция осуществляет возврат нового списка заместо старого oldList, освобождая его
 * передача размера осуществляется через *count*/
// struct Record *SearchInList (struct Record *oldList, int *count, const char *sortkey);

//Вывод сообщения об использовании программы
void usage(const char* exename);

//Поиск слова TheWord в массиве слов WordList, возврат индекса этого слова, либо -1
int FindTheWord (const char **WordList, const int ListLen, const char *TheWord);

//Вывод размера открытого файла
long FileLen(FILE *fptr);

/*Чтение текста из файла fptr в динамически выделенную область
 * При неудаче возвращается NULL
*!ПАМЯТЬ ДОЛЖНА БЫТЬ ОСВОБОЖДЕНА!*/
char *ReadUncommentedText(FILE *fptr);

/*Функция чтения из строки text записей о студентах. 
Через count передаётся информация о числе записей.
!ПАМЯТЬ ДОЛЖНА БЫТЬ ОСВОБОЖДЕНА! */
struct Record* GetStudentList(char* text, int *count);

//Вывод списка записей List величиной count в поток dest
void PrintStudentList(FILE* dest, struct Record* List, const int count);

//Файл с ключами
#include "keys.h"
//Файл с алгоритмами сортировки
#include "sort.h"

#endif //MAIN_H
