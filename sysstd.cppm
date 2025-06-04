module;
#define SYSSTD_IMPLEMENTATION
#include "sysstd.h"

export module sysstd;

export namespace sysstd {
  constexpr const auto chdir    = sysstd_chdir;
  constexpr const auto env      = sysstd_env;
  constexpr const auto fopen    = sysstd_fopen;
  constexpr const auto fullpath = sysstd_fullpath;
  constexpr const auto gmtime   = sysstd_gmtime;
  constexpr const auto mkdir    = sysstd_mkdir;
  constexpr const auto remove   = sysstd_remove;
  constexpr const auto setenv   = sysstd_setenv;
  constexpr const auto spawn    = sysstd_spawn;
  constexpr const auto strdup   = sysstd_strdup;
}
