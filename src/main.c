#include "main.h"

int main (const int argc, const char** argv) {
    /*Если пользователь не указал аргументы функции, 
     * ему выведется инструкция по использованию программы */
    if (argc < 2) {
        usage();
        return EXIT_SUCCESS;
    }
    puts(argv[argc - 1]);
    return EXIT_SUCCESS;
}

void usage(void) {
    printf("Здесь будет сообщение об ошибке\n");
}
