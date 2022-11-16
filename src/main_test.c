#include "s21_string.h"
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  unsigned char src[15] = "1234567890";

  // Заполняем массив символом ‘1’
  s21_memset(src, 100, 10);

  // Вывод массива src на консоль
  printf("src: %s\n", src);

  char app[1024] = "second string ";

  // Массив приемник данных
  char dst[1024] = "first string";

  // Добавляем строку из массива src в массив dst.
  s21_strncat(dst, app, 7);

  // Вывод массива dst на консоль
  printf("dst: %s\n", dst);

  char str[11] = "0123456789";
  // Код искомого символа
  int ch = '6';
  // Указатель на искомую переменную в строке,
  // по которой осуществляется поиск.
  char *ach;

  // Ищем символ ‘6’
  ach = s21_strchr(str, ch);

  // Выводим результат на консоль

  printf("Искомый символ в строке на позиции # %s\n", ach);

  char str11[1024] = "12305";
  char str22[1024] = "123c5";

  // Сравниваем две строки
  printf("%d\n", strncmp(str11, str22, 4));
  printf("%s\n", str22);

  char src1[1024] = "first string\0second string";

  // Массив приемник данных
  char dst1[1024] = "12";

  // Копируем строку из массива src в массив dst. Обратите внимание,
  //что скопируется только строка «первая строка\0».
  s21_strcpy(dst1, src1);

  // Вывод массива src на консоль
  printf("src: %s %s\n", src1, &src1[14]);

  // Вывод массива dst на консоль
  printf("dst: %s %s\n", dst1, &dst1[14]);

  char test[20] = "asd/.fgh/hjk";
  char test1[5] = "/.";
  char *ptch;
   
  ptch = strtok(test, test1);
  
  while (ptch!=NULL) {
    printf("%s %s\n", ptch, test);
    ptch = strtok(NULL, test1);
  
  }

  char test2[20] = "asd/.fgh/hjk";
  char test12[5] = "/.";
  char *ptch1;
  ptch1 = s21_strtok(test2, test12);
  
  while (ptch1!=NULL) {
    printf("%s %s\n", ptch1, test2);
    ptch1 = s21_strtok(NULL, test1);
  
  }
char test22[20] = "asd/.fgh/hjk";
char test122[5] = "./";
printf("%s\n", s21_strpbrk(test22, test122));
printf("%s\n", strpbrk(test22, test122));
    
printf("%s\n", strerror(106));
printf("%s\n", s21_strerror(107)); // \n после %s почему-то ломает вывод...
    printf("%s\n", s21_strerror(108)); 
    return 0;
}
