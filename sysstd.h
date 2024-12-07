#ifndef SYSSTD_H
#define SYSSTD_H

#include <stdio.h>

#ifndef SYSSTD_IMPLEMENTATION

FILE * sysstd_fopen(const char * name, const char * mode);
int    sysstd_mkdir(const char * path);

#else // SYSSTD_IMPLEMENTATION

#ifdef _WIN32
#include <direct.h>

FILE * sysstd_fopen(const char * name, const char * mode) {
  FILE * res;
  if (0 != fopen_s(&res, name, mode)) return NULL;
  return res;
}
int sysstd_mkdir(const char * path) {
  return _mkdir(path);
}

#else // !_WIN32
#include <sys/stat.h>

FILE * sysstd_fopen(const char * name, const char * mode) { return fopen(name, mode); }
int sysstd_mkdir(const char * path) { return mkdir(path, 0777); }

#endif
 
#endif // SYSSTD_IMPLEMENTATION
#endif // SYSSTD_H
