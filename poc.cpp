#pragma leco tool

import sysstd;

int main() {
  if (0 != sysstd::mkdir("out/test")) return 1;
  return 0;
}
