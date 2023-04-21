#ifndef CEB_BASE_H
#define CEB_BASE_H

#include <stdint.h>

struct CebData {
  int64_t size;
  char* data;
  char* name;
  uint64_t hash;
} typedef CebData;

enum CebResult {
  CEB_RESULT_OK        = 0,
  CEB_RESULT_NULL      = 1,
  CEB_RESULT_MEMORY    = 2,
  CEB_RESULT_FILEIO    = 3,
  CEB_RESULT_STRING    = 4,
  CEB_RESULT_NOT_FOUND = 5
} typedef CebResult;

#define CHECK_CEB(call)                                                        \
  {                                                                            \
    CebResult __result__ = call;                                               \
    if (__result__ != CEB_RESULT_OK) {                                         \
      printf("CEB ERROR CODE: %d at %s:%d\n", __result__, __FILE__, __LINE__); \
      return __result__;                                                       \
    }                                                                          \
  }

uint64_t ceb_hash_fnv1a(const char* str);

#endif /* CEB_BASE_H */
