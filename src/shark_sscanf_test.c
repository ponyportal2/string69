
#include "shark_sscanf_test.h"

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;
  char *testString = NULL;
  int testInt = 0;
  double testDouble = 0.0;
  s21_sscanf("booba", "%s%i%f", &testString, &testInt, &testDouble);
  printf("[%i][%f]", testInt, testDouble);
  return 0;
}

// printf("%s%i%f", testString, testInt, testDouble);
// printf("%s%i", testString, testInt);

// char testInput[] = "%%%%sabaka%%%%aboba%abiba%%%%";
// char specifiers[64][128] = {0};