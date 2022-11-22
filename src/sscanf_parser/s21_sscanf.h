#include <stdarg.h>

#include "s21_string.h"

struct Specificators {
    int width, argWidth;
    char length;
    char Specif;
};

int s21_sscanf(const char *input, const char *format, ...);
void getNextFormatElem(char *input, char elem[8192], int *checkStartScanf);
void assignI(char currentInputElem[8192], bool *varArgLoaded,
             void *currentVarArg, size_t *n_counter);
void assignS(char currentInputElem[8192], bool *varArgLoaded,
             void *currentVarArg, size_t *n_counter);
void assignF(char inCurrentInputElem[8192], bool *varArgLoaded,
             void *currentVarArg, size_t *n_counter);
void assignD(char inCurrentInputElem[8192], bool *varArgLoaded,
             void *currentVarArg, size_t *n_counter);
void assignI(char inCurrentInputElem[8192], bool *varArgLoaded,
             void *currentVarArg, size_t *n_counter);
void assignO(char inCurrentInputElem[8192], bool *varArgLoaded,
             void *currentVarArg, size_t *n_counter);     
void assignX(char inCurrentInputElem[8192], bool *varArgLoaded,
             void *currentVarArg, size_t *n_counter);  
void assignN(char inCurrentInputElem[8192], bool *varArgLoaded,
             void *currentVarArg, size_t *n_counter);
void assignP(char inCurrentInputElem[8192], bool *varArgLoaded,
             void *currentVarArg, size_t *n_counter);  
void formatParsing(char formatStatic[16384], char currentFormatElem[8192],
                   bool *formatLoaded, struct Specificators *Specif,  int *checkStartScanf);
void checkFormatError (struct Specificators Specif);
void ifSpecIsD(struct Specificators *Specif, char inputStatic[16384]);
void ifSpecIsI(struct Specificators *Specif, char inputStatic[16384]);
void ifSpecIsF(struct Specificators *Specif, char inputStatic[16384]);
void ifSpecIsO(struct Specificators *Specif, char inputStatic[16384]);
void ifSpecIsX(struct Specificators *Specif, char inputStatic[16384]);
void ifSpecIsP(struct Specificators *Specif, char inputStatic[16384]);
void inputParsing(char inputStatic[16384], char currentInputElem[8192], int wid,
                  bool *inputLoaded, char Specif);
void varArgParsingAndAssignment(char currentFormatElem[8192],
                                char currentInputElem[8192], bool *varArgLoaded,
                                void *currentVarArg, struct Specificators Specif, size_t *n_counter);
char *strtokChop(char *str, const char *delim, char *leftOver);
void fillOneByOne(char input[16384], char currentInputElem[8192], int wid, char Specif);
void chopLeft(char input[16384], int howMany);

// Спецификатор формата для сканирующих функций следует прототипу:
// %[*][ширина][длина]спецификатор.

// ### sprintf and sscanf Спецификаторы
// | № | Спецификатор | Результат sprintf | Результат sscanf |
// | --- | --- | --- | --- |
// ---------------------------
// | 1 | c | Символ | Символ |
// ---------------------------
// | 2 | d | Знаковое десятичное целое число |
// Знаковое десятичное целое число |
// ---------------------------
// | 3 | i | Знаковое десятичное целое число |
// Знаковое целое число (может быть десятичным,
// восьмеричным или шестнадцатеричным) |
// ---------------------------
// | 4 | e | Научная нотация (мантисса/экспонента)
// с использованием символа e (вывод чисел должен
// совпадать с точностью до e-6) |
// Десятичное число с плавающей точкой или научная нотация
// (мантисса/экспонента) |
// ---------------------------
// | 5 | E | Научная нотация (мантисса/экспонента)
// с использованием символа Е | Десятичное число
// с плавающей точкой или научная нотация (мантисса/экспонента) |
// ---------------------------
// | 6 | f | Десятичное число с плавающей точкой |
// Десятичное число с плавающей точкой
// или научная нотация (мантисса/экспонента) |
// ---------------------------
// | 7 | g | Использует кратчайший из представлений десятичного числа |
// Десятичное число с плавающей точкой
// или научная нотация (мантисса/экспонента) |
// ---------------------------
// | 8 | G | Использует кратчайший из представлений десятичного числа |
// Десятичное число с плавающей точкой
// или научная нотация (мантисса/экспонента) |
// ---------------------------
// | 9 | o | Беззнаковое восьмеричное число |
// Беззнаковое восьмеричное число |
// ---------------------------
// | 10 | s | Строка символов | Строка символов |
// ---------------------------
// | 11 | u | Беззнаковое десятичное целое число |
// Беззнаковое десятичное целое число |
// ---------------------------
// | 12 | x | Беззнаковое шестнадцатеричное целое число |
// Беззнаковое шестнадцатеричное целое число (любые буквы) |
// ---------------------------
// | 13 | X | Беззнаковое шестнадцатеричное целое число (заглавные буквы) |
// Беззнаковое шестнадцатеричное целое число (любые буквы) |
// ---------------------------
// | 14 | p | Адрес указателя | Адрес указателя |
// ---------------------------
// | 15 | n | Количество символов, напечатанных до появления %n |
// Количество символов, считанных до появления %n |
// ---------------------------
// | 16 | % | Символ % | Символ % |
// ---------------------------

// ### sprintf and sscanf Длина
// | № | Длина | Описание |
// | --- | --- | --- |
// ---------------------------
// | 1 | h | Аргумент интерпретируется как короткое int ё
// или короткое int без знака
// (применяется только к целочисленным спецификаторам: i, d, o, u, x и X). |
// ---------------------------
// | 2 | l | Аргумент интерпретируется как длинное int
// или длинное int без знака для целочисленных
// спецификаторов (i, d, o, u, x и X) и как широкий символ
// или строка широких символов для спецификаторов c и s. |
// ---------------------------
// | 3 | L | Аргумент интерпретируется как длинный double
// (применяется только к спецификаторам с плавающей точкой − e, E, f, g и G). |
// ---------------------------

// !!!!!!!!!!!!!!!!!!!!!!!
// "%*6hhi" -  * давит присовение
// !!!!!!!!!!!!!!!!!!!!!!!