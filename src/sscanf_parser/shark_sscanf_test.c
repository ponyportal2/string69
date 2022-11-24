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

    long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
    const char str[] = "-asd1 -2 +345 -4 +5";
    const char fstr[] = "%c %*s %s %c";

    int16_t res1 = s21_sscanf(str, fstr, testInt[0], testInt[1], testInt[2], testInt[3]);
    int16_t res2 = sscanf(str, fstr, testInt[4], testInt[5], testInt[6], testInt[7]);
    printf("%d %d\n", res1, res2);
    printf("%ld %s\n", a1, testInt[4]);
    printf("%ld %s\n", b1, testInt[5]);
    printf("%ld %s\n", c1, testInt[6]);
    printf("%ld %s\n", d1, testInt[7]);
  
// int testInt[] = {0, 1, 2, 3, 4, 5, 6};

  char *p;
 	 
 

  //printf("%d", s21_memcmp("Pudgeasd", "Pudgeasd", 18));
  return 0;
}

// printf("%s%i%f", testString, testInt, testDouble);
// printf("%s%i", testString, testInt);

// char testInput[] = "%%%%sabaka%%%%aboba%abiba%%%%";
// char specifiers[64][128] = {0};