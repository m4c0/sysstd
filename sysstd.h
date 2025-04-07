#ifndef SYSSTD_H
#define SYSSTD_H

#include <stdio.h>
#include <time.h>

#if _WIN32
#define SYSSTD_FILE_SEP "\\"
#else
#define SYSSTD_FILE_SEP "/"
#endif

int         sysstd_chdir(const char * path);
char *      sysstd_env(const char * name);
FILE *      sysstd_fopen(const char * name, const char * mode);
struct tm * sysstd_gmtime(const time_t * t);
int         sysstd_mkdir(const char * path);
int         sysstd_remove(const char * path);
void        sysstd_setenv(const char * name, const char * value);
char *      sysstd_strdup(const char * str);

#ifdef SYSSTD_IMPLEMENTATION

#ifdef _WIN32
#include <direct.h>
#include <stdlib.h>
#include <string.h>

int sysstd_chdir(const char * path) { return _chdir(path); }
char * sysstd_env(const char * name) {
  char *buf;
  size_t sz;
  return (0 == _dupenv_s(&buf, &sz, name)) ? buf : NULL;
}
FILE * sysstd_fopen(const char * name, const char * mode) {
  FILE * res;
  return (0 == fopen_s(&res, name, mode)) ? res : NULL;
}
struct tm * sysstd_gmtime(const time_t * t) {
  static struct tm tm;
  return (0 == gmtime_s(&tm, t)) ? &tm : NULL;
}
int sysstd_mkdir(const char * path) { return _mkdir(path); }
int sysstd_remove(const char * path) { return _remove(path); }
char * sysstd_strdup(const char * str) { return _strdup(str); }

#else // !_WIN32
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int sysstd_chdir(const char * path) { return chdir(path); }
char * sysstd_env(const char * name) {
  const char * e = getenv(name);
  return e ? strdup(e) : NULL;
}
FILE * sysstd_fopen(const char * name, const char * mode) { return fopen(name, mode); }
struct tm * sysstd_gmtime(const time_t * t) { return gmtime(t); }
int sysstd_mkdir(const char * path) { return mkdir(path, 0777); }
int sysstd_remove(const char * path) { return remove(path); }
void sysstd_setenv(const char * name, const char * value) { setenv(name, value, 0); }
char * sysstd_strdup(const char * str) { return strdup(str); }

#endif
 
#endif // SYSSTD_IMPLEMENTATION
#endif // SYSSTD_H
