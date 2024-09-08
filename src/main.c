/*Реализовать чтение из текстового файла информации о студентах (до 10 чел.):
 * номер, ФИО, номер зач. книжки, оценки 5 шт.
 * 1. Вывести в табличном виде
 * 2. Рассортировать
 * 3. Поиск
 * */

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

//Запись о студенте
struct Record {
    int number; //Номер студента
    char *surname;//Фамилия студента
    char *name;//Имя студента
    char *patronim;//Отчество студента
    char id[8];//Номер студенческого билета
    int marks[5];//Оценки студента
};

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

/*Функция чтения из строки text записей о студентах
!ПАМЯТЬ ДОЛЖНА БЫТЬ ОСВОБОЖДЕНА! */
struct Record* GetStudentList(const char* text);

int main (const int argc, const char** argv) {
    /*Если пользователь не указал аргументы функции, 
     * ему выведется инструкция по использованию программы */
    if (argc < 2) {
        usage(argv[0]);
        return EXIT_SUCCESS;
    }
    //Если пользователь запросил справку, она ему будет выведена
    if(-1 != FindTheWord(argv, argc, HELPKEY)) {
        usage(argv[0]);
        return EXIT_SUCCESS;
    }

    //Вывод информации об открываемом файле
    const char* filename = argv[argc - 1];
    printf("Открываемый файл: %s\n", filename);

    //Попытка открыть файл, вывод сообщения об ошибке в случае неудачи
    FILE *fptr = fopen(filename, "rt");
    if(fptr == NULL) {
        perror(filename);
        return ERR_FILENOTFOUND;
    }
    printf("Размер файла: %ld\n", FileLen(fptr));
    char *text = ReadUncommentedText(fptr);
    printf("%s\n", text);
    free(text);
    fclose(fptr);//Закрытие файла
    return EXIT_SUCCESS;
}

struct Record* GetStudentList(const char* text) {
    char tmpSurname[100];   //Временное хранилище фамилий
    char tmpName[100];      //Временное хранилище имени
    char tmpPatronim[100];  //Временное хранилище отчества
    char tmpId[8];          //Временное хранилище номера з/к
    int tmpNum;             //Временное хранилище номера
    int tmpMarks[5];        //Временное хранилище оценок

}

char *ReadUncommentedText(FILE *fptr) {
    long length = FileLen(fptr); //Длина файла
    if (length < 1) {           //Если длина некорректная -- чтение не осуществляется
        return NULL;
    }
    
    //Выделение памяти под текст, проверка работы calloc
    char *text = (char *) calloc(sizeof(char), (unsigned long)length + 1);
    if (text == NULL) {
        return NULL;
    }

    //Цикл обходит весь текстовый файл до конца, записывая символы в буффер buf
    int buf, i;
    for(i = 0; (buf = fgetc(fptr)) != EOF; i++){
        //Если при чтении файла встречается #, начинается внутренний цикл, идущий до переноса
        while (buf == '#'){
            while ((buf = fgetc(fptr)) != '\n') {};
            /*После цикла пропуска строки записывается новый символ следующей строки, 
            если это снова #, следующая строка также пропускается*/
            buf = fgetc(fptr);
        }
        //Содержимое буффера переносится в строку
        text[i] = (char)buf;
    }
    text[i] = '\0'; //EOF заменяется нуль-терминатором
    return text;    //Возврат на область со строкой
}

long FileLen(FILE *fptr) {
    fseek(fptr, SEEK_SET, SEEK_END);
    long len = ftell(fptr);
    rewind(fptr);
    return len;
}

int FindTheWord(const char **WordList, const int ListLen, const char *TheWord) {
    /*Цикл обходит массив слов WordList для поиска слова TheWord в нём. 
    Если слово найдено, возвращается его индекс, в противном случае -- возврат -1 */
    for (int i = 0; i < ListLen; i++) {
        if (!strcmp(WordList[i], TheWord)) {
            return i;
        }
    }
    return -1;
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
