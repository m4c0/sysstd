#ifndef SYSSTD_H
#define SYSSTD_H

#include <stdio.h>

#if _WIN32
#define SYSSTD_FILE_SEP "\\"
#else
#define SYSSTD_FILE_SEP "/"
#endif

const char * sysstd_env(const char * name);
FILE *       sysstd_fopen(const char * name, const char * mode);
int          sysstd_mkdir(const char * path);

#ifdef SYSSTD_IMPLEMENTATION

#ifdef _WIN32
#include <direct.h>

const char * sysstd_env(const char * name) {
  char *buf;
  size_t sz;
  return (0 == _dupenv_s(&buf, &sz, name)) ? buf : NULL;
}
FILE * sysstd_fopen(const char * name, const char * mode) {
  FILE * res;
  return (0 == fopen_s(&res, name, mode)) ? res : NULL;
}
int sysstd_mkdir(const char * path) {
  return _mkdir(path);
}

#else // !_WIN32
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

const char * sysstd_env(const char * name) {
  const char * e = getenv(name);
  return e ? strdup(e) : NULL;
}
FILE * sysstd_fopen(const char * name, const char * mode) { return fopen(name, mode); }
int sysstd_mkdir(const char * path) { return mkdir(path, 0777); }

#endif
 
#endif // SYSSTD_IMPLEMENTATION
#endif // SYSSTD_H
