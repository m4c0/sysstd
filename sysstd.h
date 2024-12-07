#ifndef SYSSTD_H
#define SYSSTD_H

#ifndef SYSSTD_IMPLEMENTATION

int sysstd_mkdir(const char * path);

#else // SYSSTD_IMPLEMENTATION

#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#define _mkdir(x) mkdir((x), 0777)
#endif
 
int sysstd_mkdir(const char * path) {
  return _mkdir(path);
}

#endif // SYSSTD_IMPLEMENTATION
#endif // SYSSTD_H
