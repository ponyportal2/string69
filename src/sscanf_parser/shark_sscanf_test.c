#include "shark_sscanf_test.h"
#include <string.h>

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;
  float Int = 0;
  int Int2 = 0;
  char testInt[128][128] = {0};
  char *p;


    char fstr[] = "%c%%%c%c%c";
    char str[] = "z *'@";

    int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
    s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    sscanf(str, fstr, &a2, &b2, &c2, &d2);
  
     
    printf("%d %d\n",a1, a2);
     printf("%d %d\n",b1, b2);
      printf("%d %d\n",c1, c2);
       printf("%d %d\n",d1, d2);
  //printf("%d", s21_memcmp("Pudgeasd", "Pudgeasd", 18));
  return 0;
}

// printf("%s%i%f", testString, testInt, testDouble);
// printf("%s%i", testString, testInt);

// char testInput[] = "%%%%sabaka%%%%aboba%abiba%%%%";
// char specifiers[64][128] = {0};