module;
#define SYSSTD_IMPLEMENTATION
#include "sysstd.h"

export module sysstd;

export namespace sysstd {
  constexpr const auto fopen = sysstd_fopen;
  constexpr const auto mkdir = sysstd_mkdir;
}
