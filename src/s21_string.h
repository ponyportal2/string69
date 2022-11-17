#include <stdbool.h>
#include <stddef.h>

// переделаем нуллы и size_t вот в это под конец:
// #define s21_size_t unsigned long long
// #define s21_NULL (void *)0

size_t s21_strlen(const char *str);
char *s21_strstr(char *str1, char *str2);
void *s21_memchr(const void *arr, int c, size_t n);
int s21_memcmp(const void *str1, const void *str2, size_t n);
// s21_memcpy: если n больше размера заданного массива, то оригинал выдает
// ошибку, если одна строка вывод не тот
void *s21_memcpy(void *dest, const void *src, size_t n);
void *s21_memmove(void *dest, const void *src, size_t n);
// s21_memset: оригинал ошибка если n больше размера массива
void *s21_memset(void *str, int c, size_t n);

// s21_strcat: вставляет ли в конец строки \0
// char *s21_strcat(char *str1, const char *str2); // karnhor
// char *s21_strncat(char *str1, const char *str2, size_t n); // karnhor

char *s21_strchr(const char *str, int c);
int s21_strcmp(const char *str1, const char *str2);
int s21_strncmp(const char *str1, const char *str2, size_t n);

// char *s21_strcpy(char *dest, const char *src); // karnhor

char *s21_strcpy_helper(char *dest, const char *src, size_t n,
                        bool isNcopy); // sharkmer
char *s21_strcpy(char *dest, const char *src); // sharkmer
char *s21_strncpy(char *dest, const char *src, size_t n); // sharkmer

char *s21_strcat_helper(char *dest, const char *src, size_t n, bool isNcat); // sharkmer
char *s21_strcat(char *dest, const char *src); // sharkmer
char *s21_strncat(char *dest, const char *src, size_t n); // sharkmer

char *s21_strrchr(const char *str, int c);
size_t s21_strspn(const char *stringOne, const char *stringTwo);
size_t s21_strcspn(const char *stringOne, const char *stringTwo);

char *s21_strtok (char *str, const char *delim);
char *s21_strpbrk(const char *str, const char *sym);
char *s21_strerror(int errcode);

// helper functions:
bool s21_match(const char *inputCharArr, char inputChar);
size_t s21_strspn_helper(const char *stringOne, const char *stringTwo,
                         bool isCspn);

// duffmank
// Part 5 Специальные функции обработки строк (вдохновленные классом String в языке C#)                        
void* insert(const char* src, const char* str, size_t start_index);
void* to_upper(const char* str);
void* to_lower(const char* str);
void* trim(const char* src, const char* trim_chars);
// duffmank