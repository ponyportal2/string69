#include "shark_sscanf_test.h"
#include <string.h>

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;
  float Int = 0;
  int Int2 = 0;
  char testInt[128][128] = {0};
  char *p;

  s21_sscanf("0.123e+2a3b3aoba abiba dsboba biba popa", "%f%p%6c%n%s", &Int, &p,
             testInt[2], &Int2, testInt[4]);
  printf("[%f][%p][%s][%d][%s]", Int, p, testInt[2], Int2,
         testInt[4]);
  //printf("%d", s21_memcmp("Pudgeasd", "Pudgeasd", 18));
  return 0;
}

// printf("%s%i%f", testString, testInt, testDouble);
// printf("%s%i", testString, testInt);

// char testInput[] = "%%%%sabaka%%%%aboba%abiba%%%%";
// char specifiers[64][128] = {0};