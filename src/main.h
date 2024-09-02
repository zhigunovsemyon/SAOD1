#ifndef MAIN_H 
#define MAIN_H 

#include <stdlib.h>
#include <stdio.h>

//Ключи работы с программой
#define HELPKEY "--help" //Вывод информации об использовании
#define SORTAKEY "--sorta" //Сортировка по возрастанию
#define SORTDKEY "--sortd" //Сортировка по убыванию
#define SEARCHKEY "--search" //Поиск среди полей
#define SURNAMEKEY "surname" //Сортировка по фамилиям
#define NAMEKEY "name" //Сортировка по именам
#define PATRONIMKEY "patronim" //Сортировка по отчествам
#define NUMKEY "number" //Сортировка по номеру в журнале
#define IDKEY "id" //Сортировка по номеру зачётной книжки
#define L1KEY "math" //Сортировка по первому предмету
#define L2KEY "english" //Сортировка по второму предмету
#define L3KEY "cs" //Сортировка по третьему предмету
#define L4KEY "physics" //Сортировка по четвёртому предмету
#define L5KEY "philosophy" //Сортировка по пятому предмету

//Коды ошибок
#define ERR_FILENOTFOUND 2 //Не удалось открыть файл
#define ERR_NOSEARCHPATTERN 3 //Пользователь не указал строку поиска
#define ERR_NOSORTKEY 4 //Пользователь не указал параметр для сортировки
#define ERR_OUTOFMEM -1 //Не удалось выделить память

//Вывод сообщения об использовании программы
void usage(void);

#endif
