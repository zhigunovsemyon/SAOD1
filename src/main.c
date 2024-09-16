/*Реализовать чтение из текстового файла информации о студентах (до 10 чел.):
 * номер, ФИО, номер зач. книжки, оценки 5 шт.
 * 1. Вывести в табличном виде
 * 2. Рассортировать
 * 3. Поиск
 * */

#include "main.h"

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
        return EXIT_FAILURE;
    }

    //Текст из файла без комментариев. Проверка на NULL осуществляется в GetStudentList()
    char *text = ReadUncommentedText(fptr);
    fclose(fptr);   //Закрытие файла

    int StudentCount; //Счётчик числа записей, зануляется в вызове GetStudentList()
    struct Record* StudentList;//Список записей.
    //Заполнение списка записей. Если text == NULL, то StudentList == NULL
    StudentList = GetStudentList(text, &StudentCount);

    free(text);     //Очистка буфера текста

    int parameterIndex; //Индекс режима работы
    
    /*Если пользователь выбрал сортировку по возрастанию, то осуществляется вызов функции, 
    сортирующей поля по ключу, идущему за индексом режима работы (parameterIndex). Если ключ некорректный --
    осуществляется досрочное освобождение памяти, пользователю выводится справка*/
    if ((parameterIndex = FindTheWord(argv, argc, SORTAKEY)) != -1) {
        if(0 != SortA_List(StudentList, StudentCount, argv[parameterIndex + 1])) {
            printf("Некорректный параметр сортировки: %s\n", argv[parameterIndex + 1]);
            FreeStudentList(StudentList, StudentCount);
            usage(argv[0]);
            return EXIT_FAILURE;
        }
    /*Если пользователь выбрал сортировку по убыванию, то осуществляется вызов функции, 
    сортирующей поля по ключу, идущему за индексом режима работы (parameterIndex). Если ключ некорректный --
    осуществляется досрочное освобождение памяти, пользователю выводится справка*/
    } else if ((parameterIndex = FindTheWord(argv, argc, SORTDKEY)) != -1) {
        if(0 != SortD_List(StudentList, StudentCount, argv[parameterIndex + 1])) {
            printf("Некорректный параметр сортировки: %s\n", argv[parameterIndex + 1]);
            FreeStudentList(StudentList, StudentCount);
            usage(argv[0]);
            return EXIT_FAILURE;
        }
    } 

    /* Если пользователь захотел осуществить поиск среди полей, то осуществляется вызов функции,
     * выводящей только записи, соответствующие поисковому запросу. 
     * Если таких записей нет -- выводится сообщение.*/
    if ((parameterIndex = FindTheWord(argv, argc, SEARCHKEY)) != -1) {
        if (0 != PrintStudentsMatchingQuery(stdout, StudentList, StudentCount, argv[parameterIndex + 1])) {
            printf("Не найдено записей по запросу: \"%s\"!\n", argv[parameterIndex + 1]);
        } 
    /* В ином случае осуществляется вывод всей базы данных */
    } else {
        if (StudentList != NULL && StudentCount > 0){
            PrintWholeStudentList(stdout, StudentList, StudentCount);
        }
        else {
            printf("Список пуст!\n");
        }
    }
    
    //Очистка динамически выделенной памяти, завершение работы
    FreeStudentList(StudentList, StudentCount);
    return EXIT_SUCCESS;
}

float AvgMark(struct Record *ptr) {
	int sum = 0;
	for(int i = 0; i < 5; i++){
		sum += ptr->marks[i];
	}

	return (float)sum / 5.0f;
}

void FreeStudentList(struct Record *List, int count) {
    while (count--) {
        free(List[count].name);
        free(List[count].surname);
        free(List[count].patronim);
    }
    //После освобождения 0-го поля (count == -1), освобождается список в целом
    free(List);
}

int SortA_List (struct Record *List, int count, const char *sortkey) {
    if(!strcmp(sortkey, SURNAMEKEY)) { //Если ключ сортировки соответсвует пофамильному
        qsort(List, (size_t)count, sizeof(struct Record), SortA_Surname);
        return 0;
    } else if (!strcmp(sortkey, NAMEKEY)) { //Если ключ сортировки соответсвует поименному
        qsort(List, (size_t)count, sizeof(struct Record), SortA_Name);
        return 0;
    } else if (!strcmp(sortkey, PATRONIMKEY)) { //Если ключ сортировки по отчествам
        qsort(List, (size_t)count, sizeof(struct Record), SortA_Patronim);
        return 0;
    } else if (!strcmp(sortkey, NUMKEY)) { //Если ключ сортировки по номерам
        qsort(List, (size_t)count, sizeof(struct Record), SortA_Num);
        return 0;
    } else if (!strcmp(sortkey, IDKEY)) { //Если ключ сортировки по номерам з/к
        qsort(List, (size_t)count, sizeof(struct Record), SortA_ID);
        return 0;
    } else if (!strcmp(sortkey, L1KEY)) { //Если ключ сортировки по первому предмету
        qsort(List, (size_t)count, sizeof(struct Record), SortA_L1);
        return 0;
    } else if (!strcmp(sortkey, L2KEY)) { //Если ключ сортировки по второму предмету
        qsort(List, (size_t)count, sizeof(struct Record), SortA_L2);
        return 0;
    } else if (!strcmp(sortkey, L3KEY)) { //Если ключ сортировки по третьему предмету
        qsort(List, (size_t)count, sizeof(struct Record), SortA_L3);
        return 0;
    } else if (!strcmp(sortkey, L4KEY)) { //Если ключ сортировки по четвёртому предмету
        qsort(List, (size_t)count, sizeof(struct Record), SortA_L4);
        return 0;
    } else if (!strcmp(sortkey, L5KEY)) { //Если ключ сортировки по пятому предмету
        qsort(List, (size_t)count, sizeof(struct Record), SortA_L5);
        return 0;
    } else { //Если ключ некорректный -- возвращается соответствующий флаг
        return 1;
    }
}

int SortD_List (struct Record *List, int count, const char *sortkey) {
    if(!strcmp(sortkey, SURNAMEKEY)) { //Если ключ сортировки соответсвует пофамильному
        qsort(List, (size_t)count, sizeof(struct Record), SortD_Surname);
        return 0;
    } else if (!strcmp(sortkey, NAMEKEY)) { //Если ключ сортировки соответсвует поименному
        qsort(List, (size_t)count, sizeof(struct Record), SortD_Name);
        return 0;
    } else if (!strcmp(sortkey, PATRONIMKEY)) { //Если ключ сортировки по отчествам
        qsort(List, (size_t)count, sizeof(struct Record), SortD_Patronim);
        return 0;
    } else if (!strcmp(sortkey, NUMKEY)) { //Если ключ сортировки по номерам
        qsort(List, (size_t)count, sizeof(struct Record), SortD_Num);
        return 0;
    } else if (!strcmp(sortkey, IDKEY)) { //Если ключ сортировки по номерам з/к
        qsort(List, (size_t)count, sizeof(struct Record), SortD_ID);
        return 0;
    } else if (!strcmp(sortkey, L1KEY)) { //Если ключ сортировки по первому предмету
        qsort(List, (size_t)count, sizeof(struct Record), SortD_L1);
        return 0;
    } else if (!strcmp(sortkey, L2KEY)) { //Если ключ сортировки по второму предмету
        qsort(List, (size_t)count, sizeof(struct Record), SortD_L2);
        return 0;
    } else if (!strcmp(sortkey, L3KEY)) { //Если ключ сортировки по третьему предмету
        qsort(List, (size_t)count, sizeof(struct Record), SortD_L3);
        return 0;
    } else if (!strcmp(sortkey, L4KEY)) { //Если ключ сортировки по четвёртому предмету
        qsort(List, (size_t)count, sizeof(struct Record), SortD_L4);
        return 0;
    } else if (!strcmp(sortkey, L5KEY)) { //Если ключ сортировки по пятому предмету
        qsort(List, (size_t)count, sizeof(struct Record), SortD_L5);
        return 0;
    } else { //Если ключ некорректный -- возвращается соответствующий флаг
        return 1;
    }
}

int PrintStudentsMatchingQuery(FILE* dest, struct Record* List, const int count, const char *query) {
    int EmptyFlag = 1; //Флаг несоответствия запроса записям
    size_t QueryLen = strlen(query);//Длинна запроса
    //Цикл, перебирающий каждую запись
    for (int i = 0; i < count; ++i) {
        struct Record* cur = List + i;//Текущая запись

        /* Если запрос не совпал с текстовым полем (имени, фамилии, отчества, ном. з/к)... */ 
        if((strncmp(query, cur->surname, QueryLen) && strncmp(query, cur->name, QueryLen) && 
            strncmp(query, cur->id, QueryLen) && strncmp(query, cur->patronim, QueryLen))) {
            /* ...и длина запроса == 1, но 1й символ запроса не совпал с одной из оценок либо номером в журнале, 
             * то текущая позиция пропускается, цикл переходит на следующий виток */
            if (QueryLen == 1) {
                if((strncmp(query, cur->surname, QueryLen) && strncmp(query, cur->name, QueryLen) && 
                    strncmp(query, cur->id, QueryLen) && strncmp(query, cur->patronim, QueryLen) && 
                    (cur->marks[0] + '0' - query[0]) && (cur->marks[1] + '0' - query[0]) && 
                    (cur->marks[2] + '0' - query[0]) && (cur->marks[3] + '0' - query[0]) && 
                    (cur->marks[4] + '0' - query[0]) && (cur->number + '0' - query[0]))) {
                    continue;
                }
            } else {
                continue;
            }
        }
        //Если цикл дошёл до сюда, при этом флаг ещё поднят, значит это первое совпадение
        if (EmptyFlag == 1 ) {
            //Вывод шапки таблицы
            printf("№  фамилия\tИмя\tОтчество\t№ з/к    %s %s %s %s %s AVG\n", 
                L1KEY, L2KEY, L3KEY, L4KEY, L5KEY);
            EmptyFlag = 0;//Осуществляется сброс флага несоответствия
        }
        //Осуществляется вывод записи
        fprintf(dest, "%-2d %s\t%s\t%s\t%s %d    %d       %d       %d      %d      %2.1f\n",
            cur->number, cur->surname, cur->name, cur->patronim, cur->id,
            cur->marks[0], cur->marks[1], cur->marks[2], cur->marks[3], cur->marks[4], AvgMark(cur));
    }
    //Флаг возвращается из функции
    return EmptyFlag;
}

void PrintWholeStudentList(FILE* dest, struct Record* List, const int count) {
    //Вывод шапки таблицы
    printf("№  фамилия\tИмя\tОтчество\t№ з/к    %s %s %s %s %s\n", 
           L1KEY, L2KEY, L3KEY, L4KEY, L5KEY);
    //Цикл, перебирающий каждую запись
    for (int i = 0; i < count; ++i) {
        struct Record* cur = List + i;//Текущая запись

        //Осуществляется вывод записи
        fprintf(dest, "%-2d %s\t%s\t%s\t%s %d %d %d %d %d %2.1f\n",
            cur->number, cur->surname, cur->name, cur->patronim, cur->id,
            cur->marks[0], cur->marks[1], cur->marks[2], cur->marks[3], cur->marks[4], AvgMark(cur));
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
    *count = 0;                     //Обнуление счётчика перед началом
    
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
        char *newName = (char *) malloc(1 + strlen(tmpName));
        char *newSurname = (char *) malloc(1 + strlen(tmpSurname));
        char *newPatronim = (char *) malloc(1 + strlen(tmpPatronim));
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
    char *text; //Буфер с очищенным текстом
    //Выделение памяти под текст, проверка работы calloc
    text = (char *) calloc(sizeof(char), (size_t)length + 1);
    if (text == NULL) {
        return NULL;
    }

    int buf,// Временный буфер для символа
        i; //Счётчик
    //Цикл обходит весь текстовый файл до конца, записывая символы в буфер buf
    for(i = 0; (buf = fgetc(fptr)) != EOF; i++){
        //Если при чтении файла встречается #, начинается внутренний цикл, идущий до переноса строки
        while (buf == '#'){
            do {
                buf = fgetc(fptr);
            } while (!(buf == '\n' || buf == EOF));
            /*После цикла пропуска строки записывается новый символ следующей строки, 
            если это снова #, следующая строка также пропускается*/
            buf = fgetc(fptr);
        }
        //Содержимое буфера переносится в строку
        text[i] = (char)buf;
    }
    text[i] = '\0'; //EOF заменяется нуль-терминатором
    return text;    //Возврат указателя на область со строкой
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
