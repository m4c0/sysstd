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
void        sysstd_fullpath(const char * path, char * dst, unsigned dst_len);
struct tm * sysstd_gmtime(const time_t * t);
int         sysstd_mkdir(const char * path);
int         sysstd_remove(const char * path);
void        sysstd_setenv(const char * name, const char * value);
int         sysstd_spawn(const char * cmd, const char * const * argv);
char *      sysstd_strdup(const char * str);

#ifdef SYSSTD_IMPLEMENTATION

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <direct.h>
#include <process.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

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
void sysstd_fullpath(const char * path, char * dst, unsigned dst_size) {
  _fullpath(dst, path, dst_size);
}
struct tm * sysstd_gmtime(const time_t * t) {
  static struct tm tm;
  return (0 == gmtime_s(&tm, t)) ? &tm : NULL;
}
int sysstd_mkdir(const char * path) { return _mkdir(path); }
int sysstd_remove(const char * path) { return remove(path); }
void sysstd_setenv(const char * name, const char * value) {
  SetEnvironmentVariable(name, value);
}
int sysstd_spawn(const char * cmd, const char * const * argv) { return _spawnvp(_P_WAIT, cmd, argv); }
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
void sysstd_fullpath(const char * path, char * dst, unsigned dst_size) {
  // TODO: assert dst_size >= PATH_MAX
  realpath(path, dst);
}
struct tm * sysstd_gmtime(const time_t * t) { return gmtime(t); }
int sysstd_mkdir(const char * path) { return mkdir(path, 0777); }
int sysstd_remove(const char * path) { return remove(path); }
void sysstd_setenv(const char * name, const char * value) { setenv(name, value, 0); }
int sysstd_spawn(const char * cmd, const char * const * argv) {
  pid_t pid = fork();
  if (pid < 0) return pid;
  if (pid == 0) {
    execvp(cmd, (char * const *)argv);
    exit(1);
  } else {
    int res;
    waitpid(pid, &res, 0);
    if (WIFEXITED(res)) return WEXITSTATUS(res);
    return 13;
  }
}
char * sysstd_strdup(const char * str) { return strdup(str); }

#endif
 
#endif // SYSSTD_IMPLEMENTATION
#endif // SYSSTD_H
