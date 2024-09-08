#include "sort.h"

int SortA_Surname (const void *a, const void *b) {
    return strcmp(((struct Record *) a)->surname,((struct Record *) b)->surname);
}

int SortD_Surname (const void *a, const void *b) {
    return strcmp(((struct Record *) b)->surname,((struct Record *) a)->surname);
}

