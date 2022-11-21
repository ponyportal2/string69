#include "shark_sscanf_test.h"

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;
  int Int = 0;
  char testInt[128][128] = {0};

  s21_sscanf("+0123a2boba abiba dsboba biba popa", "%i%s%3c%s%s", &Int, testInt[1],
             testInt[2], testInt[3], testInt[4]);
  printf("[%i][%s][%s][%s][%s]", Int, testInt[1], testInt[2], testInt[3],
         testInt[4]);
  return 0;
}

// printf("%s%i%f", testString, testInt, testDouble);
// printf("%s%i", testString, testInt);

// char testInput[] = "%%%%sabaka%%%%aboba%abiba%%%%";
// char specifiers[64][128] = {0};