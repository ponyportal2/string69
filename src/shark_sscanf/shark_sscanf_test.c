#include "shark_sscanf_test.h"
#include <string.h>
#include <stdlib.h>
#define BUFF_SIZE 512

int main(int argc, char **argv) {


  (void)argc;
  (void)argv;
  float Int = 0;
  int Int2 = 0;
  char testInt[128][128] = {0};

    long c1 = 0, c2 = 0, d1 = 0, d2 = 0;
    char a1[100] = {0}, a2[100] = {0};
    char b1[100] = {0}, b2[100] = {0};
    const char str[] = "11337  ++3   +3 -5 ------4";
    const char fstr[] = "%s%c%ld%ld";

    int16_t res1 = s21_sscanf(str, fstr, a1, b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, a2, b2, &c2, &d2);
    printf("%d %d\n", res1, res2);
    printf("%s %s\n", a1, a2);
    printf("%s %s\n", b1, b2);
    printf("%ld %ld\n", c1, c2);
    printf("%ld %ld\n", d1, d2);
  
// int testInt[] = {0, 1, 2, 3, 4, 5, 6};

  char *p;
 	 
 

  //printf("%d", s21_memcmp("Pudgeasd", "Pudgeasd", 18));
  return 0;
}

// printf("%s%i%f", testString, testInt, testDouble);
// printf("%s%i", testString, testInt);

// char testInput[] = "%%%%sabaka%%%%aboba%abiba%%%%";
// char specifiers[64][128] = {0};