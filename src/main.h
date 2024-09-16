#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Запись о студенте
struct Record {
    int number; //Номер студента
    char *surname;//Фамилия студента
    char *name;//Имя студента
    char *patronim;//Отчество студента
    char id[8];//Номер студенческого билета
    int marks[5];//Оценки студента
};

//Получение диапазона оценок markA и markB
int GetMarkRange(const char *text, float *markA, float *markB);

//Расчёт среднего балла студента
float AvgMark(struct Record *ptr);

//Очистка из памяти динамического списка записей List размера count
void FreeStudentList(struct Record *List, int count);

/*Сортировка списка List размера count по возрастанию по параметру sortkey
 * Возвращает ноль при удачной сортировке, либо 1, если sortkey некорректный*/
int SortA_List (struct Record *List, int count, const char *sortkey);

/*Сортировка списка List размера count по убыванию по параметру sortkey
 * Возвращает ноль при удачной сортировке, либо 1, если sortkey некорректный*/
int SortD_List (struct Record *List, int count, const char *sortkey);

/*Вывод из списка записей List величиной count в поток dest
 * только тех записей, которые соответствуют запросу query.
 * Если список пустой, возвращает 1, если нет -- 0*/
int PrintStudentsMatchingQuery(FILE* dest, struct Record* List, const int count, const char *query);

/*Вывод из списка записей List величиной count в поток dest
 * только тех записей, которые соответствуют диапазону оценок lowMark и highMark.
 * Если список пустой, возвращает 1, если нет -- 0*/
int PrintStudentsMatchingMarks(FILE* dest, struct Record* List, const int count, float const lowMark, float const highMark);

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
!ПАМЯТЬ ДОЛЖНА БЫТЬ ОСВОБОЖДЕНА!
!ПЕРЕД ОЧИСТКОЙ СПИСКА ОЧИСТИТЬ ДИНАМИЧЕСКИЕ ПОЛЯ!*/
struct Record* GetStudentList(char* text, int *count);

//Вывод списка записей List величиной count в поток dest
void PrintWholeStudentList(FILE* dest, struct Record* List, const int count);

//Файл с ключами
#include "keys.h"
//Файл с алгоритмами сортировки
#include "sort.h"

#endif //MAIN_H
