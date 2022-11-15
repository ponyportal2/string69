#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_sscanf.h"
#include "s21_string.h"

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;

  char tempSpecifiers[] = "%%%%sabaka%%%%aboba%abiba%%%%";
  char specifiers[128][128] = {0};
  int i = 0;
  char* tempStr = NULL;
  do {
    if (i == 0) {
      tempStr = s21_strtok(tempSpecifiers, "%");
    } else {
      tempStr = s21_strtok(NULL, "%");
    }
    if (tempStr != NULL) {
      s21_strcpy(specifiers[i], tempStr);
      printf("[%s]\n", specifiers[i]);
    }
    i++;
  } while (tempStr != NULL);

  return 0;
}