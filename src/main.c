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

/*Функция чтения из строки text записей о студентах. 
Через count передаётся информация о числе записей.
!ПАМЯТЬ ДОЛЖНА БЫТЬ ОСВОБОЖДЕНА! */
struct Record* GetStudentList(char* text, int *count);

//Вывод списка записей List величиной count в поток dest
void PrintStudentList(FILE* dest, struct Record* List, const int count);

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

    FILE *fptr; //Текстовый файл с записями
    //Попытка открыть файл, вывод сообщения об ошибке в случае неудачи
    if((fptr = fopen(filename, "rt")) == NULL) {
        perror(filename);
        return ERR_FILENOTFOUND;
    }
    printf("Размер файла: %ld\n\n", FileLen(fptr));
    //Текст из файла без комментариев
    char *text = ReadUncommentedText(fptr);

    int StudentCount; //Счётчик числа записей
    //Список записей
    struct Record* StudentList = GetStudentList(text, &StudentCount);

    free(text);     //Очистка буфера текста
    fclose(fptr);   //Закрытие файла

    if (StudentCount < 1) {
        printf("Список пуст!\n");
    }

    int parameterIndex;
    if ((parameterIndex = FindTheWord(argv, argc, SORTAKEY)) != -1) {
        printf("Сортировка по возрастанию по: %s \n", argv[parameterIndex + 1]);
    } else if ((parameterIndex = FindTheWord(argv, argc, SORTDKEY)) != -1) {
        printf("Сортировка по убыванию по: %s \n", argv[parameterIndex + 1]);
    } else if ((parameterIndex = FindTheWord(argv, argc, SEARCHKEY)) != -1) {
        printf("Поиск по запросу: %s \n", argv[parameterIndex + 1]);
    } else {
        printf("Вывод списка без изменений целиком\n");
    }

    PrintStudentList(stdout, StudentList, StudentCount);

    free(StudentList);
    return EXIT_SUCCESS;
}

void PrintStudentList(FILE* dest, struct Record* List, const int count) {
    puts("Список:");
    for (int i = 0; i < count; ++i) {
        struct Record* cur = List + i;
        fprintf(dest, "%d %s\t%s\t%s\t%s %d %d %d %d %d\n",
            cur->number, cur->surname, cur->name, cur->patronim, cur->id,
            cur->marks[0], cur->marks[1], cur->marks[2], cur->marks[3], cur->marks[4]);
    }
}

struct Record* GetStudentList(char* text, int *count) {
    int tmpNum;                     //Временное хранилище номера
    char tmpSurname[100] = { 0 };   //Временное хранилище фамилий
    char tmpName[100] = { 0 };      //Временное хранилище имени
    char tmpPatronim[100] = { 0 };  //Временное хранилище отчества
    char tmpId[8] = { 0 };          //Временное хранилище номера з/к
    int tmpMarks[5] = { 0 };        //Временное хранилище оценок
    struct Record* Students = NULL; //Указатель на область памяти со студентами
    *count = 0; //Обнуление счётчика перед началом
    
    /*Цикл чтения строки*/
    while (1)  {
        //Если строка закончилась, смысла пытаться её прочитать нет
        if (text == NULL) {
            return Students;
        }

        //Чтение строки, сохранение числа прочитанных полей
        const int scanfOutput = sscanf(text, "%d %99s %99s %99s %7s %d %d %d %d %d",
            &tmpNum, tmpSurname, tmpName, tmpPatronim, tmpId,
            tmpMarks, tmpMarks + 1, tmpMarks + 2, tmpMarks + 3, tmpMarks + 4);

        //Если в результате чтения очередная строка не была прочитана полностью, чтение завершается
        if (10 != scanfOutput) {
            return Students;
        }

        //Перемещение указателя на следующую строку
        text = strchr(text, '\n');
        if (text != NULL) {
            text++;
        }

        /*Выделение динамических буферов под поля, проверка*/
        char *newName = (char *) malloc(strlen(tmpName));
        char *newSurname = (char *) malloc(strlen(tmpSurname));
        char *newPatronim = (char *) malloc(strlen(tmpPatronim));
        if (!(newName && newSurname && newPatronim)) {
            free(newName);
            free(newSurname);
            free(newPatronim);
            return Students;
        }

        /*Перевыделение памяти под новое число записей, 
        если выделить память не удалось, из функции возращается старый указатель */
        struct Record* newStudents = (struct Record*)realloc(Students, (size_t)(*count + 1) * sizeof(struct Record));
        if (newStudents == NULL) {
            free(newName);
            free(newSurname);
            free(newPatronim);
            return Students;
        }

        //Копирование текста в новые буферы
        strcpy(newName, tmpName);
        strcpy(newSurname, tmpSurname);
        strcpy(newPatronim, tmpPatronim);

        //Расстановка новых буферов в поля записи
        newStudents[*count].surname = newSurname;
        newStudents[*count].name = newName;
        newStudents[*count].patronim = newPatronim;
       
        //Копирование остальных полей
        newStudents[*count].number = tmpNum;
        strcpy(newStudents[*count].id, tmpId);
        memcpy(newStudents[*count].marks, tmpMarks, 5 * sizeof(int));

        //Замена указателя на список записей на новый
        Students = newStudents;
        (*count)++;
    }
}

char *ReadUncommentedText(FILE *fptr) {
    long length = FileLen(fptr); //Длина файла
    if (length < 1) {           //Если длина некорректная -- чтение не осуществляется
        return NULL;
    }
    
    //Выделение памяти под текст, проверка работы calloc
    char *text = (char *) calloc(sizeof(char), (size_t)length + 1);
    if (text == NULL) {
        return NULL;
    }

    //Цикл обходит весь текстовый файл до конца, записывая символы в буффер buf
    int buf, i;
    for(i = 0; (buf = fgetc(fptr)) != EOF; i++){
        //Если при чтении файла встречается #, начинается внутренний цикл, идущий до переноса
        while (buf == '#'){
            do {
                buf = fgetc(fptr);
            } while (!(buf == '\n' || buf == EOF));
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
