#include "sort.h"

int SortA_L1 (const void *a, const void *b) {
    int arg1 = ((struct Record *)a)->marks[0];
    int arg2 = ((struct Record *)b)->marks[0];
    return (arg2 > arg1) - (arg2 < arg1);
}

int SortD_L1 (const void *a, const void *b) {
    int arg1 = ((struct Record *)a)->marks[0];
    int arg2 = ((struct Record *)b)->marks[0];
    return (arg1 > arg2) - (arg1 < arg2);
}

int SortA_L2 (const void *a, const void *b) {
    int arg1 = ((struct Record *)a)->marks[1];
    int arg2 = ((struct Record *)b)->marks[1];
    return (arg2 > arg1) - (arg2 < arg1);
}

int SortD_L2 (const void *a, const void *b) {
    int arg1 = ((struct Record *)a)->marks[1];
    int arg2 = ((struct Record *)b)->marks[1];
    return (arg1 > arg2) - (arg1 < arg2);
}

int SortA_L3 (const void *a, const void *b) {
    int arg1 = ((struct Record *)a)->marks[2];
    int arg2 = ((struct Record *)b)->marks[2];
    return (arg2 > arg1) - (arg2 < arg1);
}

int SortD_L3 (const void *a, const void *b) {
    int arg1 = ((struct Record *)a)->marks[2];
    int arg2 = ((struct Record *)b)->marks[2];
    return (arg1 > arg2) - (arg1 < arg2);
}

int SortA_L4 (const void *a, const void *b) {
    int arg1 = ((struct Record *)a)->marks[3];
    int arg2 = ((struct Record *)b)->marks[3];
    return (arg2 > arg1) - (arg2 < arg1);
}

int SortD_L4 (const void *a, const void *b) {
    int arg1 = ((struct Record *)a)->marks[3];
    int arg2 = ((struct Record *)b)->marks[3];
    return (arg1 > arg2) - (arg1 < arg2);
}

int SortA_L5 (const void *a, const void *b) {
    int arg1 = ((struct Record *)a)->marks[4];
    int arg2 = ((struct Record *)b)->marks[4];
    return (arg2 > arg1) - (arg2 < arg1);
}

int SortD_L5 (const void *a, const void *b) {
    int arg1 = ((struct Record *)a)->marks[4];
    int arg2 = ((struct Record *)b)->marks[4];
    return (arg1 > arg2) - (arg1 < arg2);
}

int SortA_Num (const void *a, const void *b) {
    int arg1 = ((struct Record *)a)->number;
    int arg2 = ((struct Record *)b)->number;
    return (arg2 > arg1) - (arg2 < arg1);
}

int SortD_Num (const void *a, const void *b) {
    int arg1 = ((struct Record *)a)->number;
    int arg2 = ((struct Record *)b)->number;
    return (arg1 > arg2) - (arg1 < arg2);
}

int SortA_ID (const void *a, const void *b) {
    return strcmp(((struct Record *) a)->id,((struct Record *) b)->id);
}

int SortD_ID (const void *a, const void *b) {
    return strcmp(((struct Record *) b)->id,((struct Record *) a)->id);
}

int SortA_Patronim (const void *a, const void *b) {
    return strcmp(((struct Record *) a)->patronim,((struct Record *) b)->patronim);
}

int SortD_Patronim (const void *a, const void *b) {
    return strcmp(((struct Record *) b)->patronim,((struct Record *) a)->patronim);
}

int SortA_Name (const void *a, const void *b) {
    return strcmp(((struct Record *) a)->name,((struct Record *) b)->name);
}

int SortD_Name (const void *a, const void *b) {
    return strcmp(((struct Record *) b)->name,((struct Record *) a)->name);
}

int SortA_Surname (const void *a, const void *b) {
    return strcmp(((struct Record *) a)->surname,((struct Record *) b)->surname);
}

int SortD_Surname (const void *a, const void *b) {
    return strcmp(((struct Record *) b)->surname,((struct Record *) a)->surname);
}

