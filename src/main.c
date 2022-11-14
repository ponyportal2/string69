#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

int s21_strlen(const char *str);
char *s21_strstr(char *str1, char *str2);
void *s21_memchr (const void *arr, int c, size_t n);
int s21_memcmp(const void *str1, const void *str2, size_t n);
void *s21_memcpy(void *dest, const void *src, size_t n); // если n больше размера заданного массива, то оригинал выдает ошибку, если одна строка вывод не тот
void *s21_memmove(void *dest, const void *src, size_t n);
void *s21_memset(void *str, int c, size_t n); // оригинал ошибка если n больше размера массива
char *s21_strcat(char *str1, const char *str2); // вставляет ли в конец строки \0
char *s21_strncat(char *str1, const char *str2, size_t n);
char *s21_strchr(const char *str, int c);
int s21_strcmp(const char *str1, const char *str2);
int s21_strncmp(const char *str1, const char *str2, size_t n);
char *s21_strcpy(char *dest, const char *src);

int main() {
    char str1[9] = "aabbccdd";
    char str2[9] = "aabbccdd";
    char str3[9] = "aabbccdd";
    printf("The string: %s\n", str1);
    memcpy(str1 + 2, str1, 6);
    printf("New string: %s\n", str1);
    s21_memcpy(str3 + 2, str3, 6);
    printf("%s\n", str3);

    printf("The string: %s\n", str2);
    memmove(str2 + 2, str2, 6);
    printf("New string: %s\n", str2);
    
    // Исходный массив
    unsigned char src[15]="1234567890";
  
    // Заполняем массив символом ‘1’
    s21_memset (src, 100, 10);

    // Вывод массива src на консоль
    printf ("src: %s\n",src);
    
    char app[1024]="second string ";
  
    // Массив приемник данных
    char dst[1024]="first string";

    // Добавляем строку из массива src в массив dst.
    s21_strncat (dst, app, 7);

    // Вывод массива dst на консоль
    printf ("dst: %s\n",dst);
    
    char str [11]="0123456789";
       // Код искомого символа
       int ch = '6';
       // Указатель на искомую переменную в строке,
       // по которой осуществляется поиск.
       char *ach;
      
       // Ищем символ ‘6’
       ach=s21_strchr (str, ch);

       // Выводим результат на консоль

          printf ("Искомый символ в строке на позиции # %s\n", ach);
    
    char str11[1024]="12305";
       char str22[1024]="123c5";
      
       // Сравниваем две строки
    printf("%d\n", strncmp (str11, str22, 4));
    printf("%s\n", str22);
    
    char src1[1024]="first string\0second string";
  
    // Массив приемник данных
    char dst1[1024]="12";

    // Копируем строку из массива src в массив dst. Обратите внимание,
    //что скопируется только строка «первая строка\0».
    s21_strcpy (dst1, src1);

    // Вывод массива src на консоль
    printf ("src: %s %s\n",src1, &src1[14]);

    // Вывод массива dst на консоль
    printf ("dst: %s %s\n",dst1, &dst1[14]);
    return 0;
}

int s21_strlen(const char *str) {
    int len = 0;
    while (*str != '\0') {
        str++;
        len++;
    }
    return len;
}




char *s21_strstr(char *str1, char *str2) {
    int i = 0, j = 0;
    char *a = NULL;
    while (str1[i] != '\0' && a == NULL) {
        if (str1[i] == str2[j]) {
            j++;
        } else {
            j = 0;
        }
        if (str2[j] == '\0') {
            if (j == s21_strlen(str2)) {
                a = str1 + i - j + 1;
            }
        }
        i++;
    }
    return a;
}


void *s21_memchr(const void *arr, int c, size_t n) {
    unsigned char *sym = NULL;
    unsigned char *tmp = (unsigned char*)arr;
    while (*tmp != c && n > 1) {
        n--;
        tmp++;
    }
    if (*tmp == c) {
        sym = tmp;
    }
    return sym;
}

int s21_memcmp(const void *str1, const void *str2, size_t n) {
    int result = 0;
    char *tmp1 = (char*)str1;
    char *tmp2 = (char*)str2;
    while (n > 0) {
        result = *(char*)tmp1 - *(char*)tmp2;
        if (result != 0) {
            n = 0;
        } else {
            tmp1++;
            tmp2++;
            n--;
        }
    }
    return result;
}

void *s21_memcpy(void *dest, const void *src, size_t n) {
    char *tmp = dest;
    const char *s = src;
    while (n > 0) {
        *tmp = *s;
        tmp++;
        s++;
        n--;
    }
    return dest;
}

void *s21_memmove(void *dest, const void *src, size_t n) {
    char *tmp = dest;
    const char *s = src;
    char move[n];
    for (size_t i = 0; i < n; i++) {
        move[i] = *s;
        s++;
    }
    for (size_t i = 0; i < n; i++) {
        *tmp = move[i];
        tmp++;
    }
    return dest;
}

void *s21_memset(void *str, int c, size_t n) {
    unsigned char *tmp = (unsigned char*)str;
    for (size_t i = 0; i < n; i++) {
        *tmp = c;
        tmp++;
    }
    return str;
}


char *s21_strcat(char *str1, const char *str2) {
    char *tmp1 = str1;
    const char *tmp2 = str2;
    while (*tmp1 != '\0') {
        tmp1++;
    }
    while (*tmp2 != '\0') {
        *tmp1 = *tmp2;
        tmp1++;
        tmp2++;
    }
    if (*tmp1 != '\0') {
        tmp1++;
        *tmp1 = '\0';
    }
    return tmp1;
}

char *s21_strncat(char *str1, const char *str2, size_t n) {
    char *tmp1 = str1;
    const char *tmp2 = str2;
    while (*tmp1 != '\0') {
        tmp1++;
    }
    while (*tmp2 != '\0' && n) {
        *tmp1 = *tmp2;
        tmp1++;
        tmp2++;
        n--;
    }
    if (*tmp1 != '\0') {
        tmp1++;
        *tmp1 = '\0';
    }
    return tmp1;
}

char *s21_strchr(const char *str, int c) {
    char *sym = NULL;
    int check = 1;
    while(*str && check) {
        if (*str == c) {
            sym = (char*)str;
            check = 0;
        }
        str++;
    }
    return sym;
}

int s21_strcmp(const char *str1, const char *str2) {
    int check  = 1, result = 0;
    while (*str1 && *str2 && check) {
        if (*str1 - *str2 != 0) {
            result = *str1 - *str2;
            check = 0;
        } else {
            str1++;
            str2++;
        }
    }
    return result;
}

int s21_strncmp(const char *str1, const char *str2, size_t n) {
    int check  = 1, result = 0;
    while (*str1 && *str2 && check && n) {
        if (*str1 - *str2 != 0) {
            result = *str1 - *str2;
            check = 0;
        } else {
            str1++;
            str2++;
            n--;
        }
    }
    return result;
}

char *s21_strcpy(char *dest, const char *src) {
    char *tmp = dest;
    while (*src != '\0') {
        tmp = (char*)src;
        tmp++;
        src++;
    }
    if (*tmp != '\0') {
        tmp++;
        *tmp = '\0';
    }
    return tmp;
}
