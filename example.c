#define SYSSTD_IMPLEMENTATION
#include "sysstd.h"

int main() {
  if (0 != sys_mkdir("out/test")) return 1;
  return 0;
}
