#include "shark_sscanf_test.h"

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;
  int testInt = 0;
  int testInt2 = 0;
  int testInt3 = 0;
  s21_sscanf("5 5 5", "%i%i%i", &testInt, &testInt2, &testInt3);
  printf("[%i][%i][%i]", testInt, testInt2, testInt3);
  return 0;
}

// printf("%s%i%f", testString, testInt, testDouble);
// printf("%s%i", testString, testInt);

// char testInput[] = "%%%%sabaka%%%%aboba%abiba%%%%";
// char specifiers[64][128] = {0};