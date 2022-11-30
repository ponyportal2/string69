#include <stdarg.h>

#include "s21_string.h"
struct Specificators {
    int width, argWidth;
    char length;
    char Specif;
    char Space;
    char buff[8192];
};

int s21_sscanf(const char *input, const char *format, ...);
void getNextFormatElem(char *input, char elem[8192], int *checkStartScanf);
void assignI(char currentInputElem[8192], bool *varArgLoaded,
             void *currentVarArg, struct Specificators Specif);
void assignS(char currentInputElem[8192], bool *varArgLoaded,
             void *currentVarArg);
void assignF(char inCurrentInputElem[8192], bool *varArgLoaded,
             void *currentVarArg, struct Specificators Specif);
void assignD(char inCurrentInputElem[8192], bool *varArgLoaded,
             void *currentVarArg, struct Specificators Specif);
void assignI(char inCurrentInputElem[8192], bool *varArgLoaded,
             void *currentVarArg, struct Specificators Specif);
void assignO(char inCurrentInputElem[8192], bool *varArgLoaded,
             void *currentVarArg, struct Specificators Specif);     
void assignX(char inCurrentInputElem[8192], bool *varArgLoaded,
             void *currentVarArg, struct Specificators Specif);  
void assignN(bool *varArgLoaded,
             void *currentVarArg, size_t *n_counter, int *counterForReturn);
void assignP(char inCurrentInputElem[8192], bool *varArgLoaded,
             void *currentVarArg);  
char formatParsing(char formatStatic[16384], char currentFormatElem[8192],
                   bool *formatLoaded, struct Specificators *Specif,  int *checkStartScanf, int *status);
void chooseSpecif(struct Specificators *Specif, char inputStatic[16384], bool *stopMove); 
void ifSpecIsD(struct Specificators *Specif, char inputStatic[16384], bool *stopMove);
void ifSpecIsI(struct Specificators *Specif, char inputStatic[16384], bool *stopMove);
void ifSpecIsF(struct Specificators *Specif, char inputStatic[16384], bool *stopMove);
void ifSpecIsO(struct Specificators *Specif, char inputStatic[16384], bool *stopMove);
void ifSpecIsX(struct Specificators *Specif, char inputStatic[16384], bool *stopMove);
void helpHexPars(struct Specificators *Specif, char inputStatic[16384], bool *stopMove, int startParse);
void helpOctPars(struct Specificators *Specif, char inputStatic[16384], bool *stopMove, int startParse);
void inputParsing(char inputStatic[16384], char currentInputElem[8192], int wid,
                  bool *inputLoaded, struct Specificators Specif, bool *startParsing, size_t *n_counter);
void varArgParsingAndAssignment(char currentInputElem[8192], bool *varArgLoaded,
                                void *currentVarArg, struct Specificators Specif, size_t *n_counter, int *counterForReturn);
char *strtokChop(char *str, const char *delim, char *leftOver);
void fillOneByOne(char input[16384], char currentInputElem[8192], int wid, struct Specificators Specif, bool *startParsing, size_t *n_counter);
void chopLeft(char input[16384], int howMany, size_t *n_counter, struct Specificators Specif);
unsigned long hexToBaseTenLong(char *hexVal);
unsigned int hexToBaseTen(char *hexVal);
unsigned short int hexToBaseTenShort(char *hexVal);
unsigned int octToBaseTen(char* octVal);
unsigned long int octToBaseTenLong(char* octVal);
unsigned short int octToBaseTenShort(char* octVal);
int s21_atoi(char *str);
short int s21_atoiShort(char *str);
long int s21_atoiLong(char *str);
double s21_atof(char *str);
long double s21_atofLong(char *str);