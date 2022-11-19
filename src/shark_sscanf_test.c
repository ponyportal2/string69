#include "shark_sscanf_test.h"

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;
  int testInt[] = {0, 1, 2, 3, 4, 5, 6};

  s21_sscanf("5 6 7 8 9", "%i%i%i%i%i", &testInt[0], &testInt[1], &testInt[2],
             &testInt[3], &testInt[4]);
  printf("[%i][%i][%i][%i][%i]", testInt[0], testInt[1], testInt[2], testInt[3],
         testInt[4]);
  return 0;
}

// printf("%s%i%f", testString, testInt, testDouble);
// printf("%s%i", testString, testInt);

// char testInput[] = "%%%%sabaka%%%%aboba%abiba%%%%";
// char specifiers[64][128] = {0};