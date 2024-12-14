#pragma leco tool

#define SYSSTD_IMPLEMENTATION
#include "sysstd.h"

int main() {
  char * env = sysstd_env("HOME");
  if (env) {
    printf("HOME = %s\n", env);
    free(env);
  }

  if (0 != sysstd_mkdir("out/test")) return 1;

  FILE * f = sysstd_fopen("out/test/file", "w");
  fclose(f);
  return 0;
}
