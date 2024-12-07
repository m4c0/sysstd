module;
#define SYSSTD_IMPLEMENTATION
#include "sysstd.h"

export module sysstd;

export namespace sysstd {
  constexpr const auto mkdir = sys_mkdir;
}
