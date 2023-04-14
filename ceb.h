#ifndef CEB_H
#define CEB_H

#include <stdlib.h>

struct CebData {
  size_t size;
  char* data;
  char* name;
} typedef CebData;

enum CebResult {
  CEB_RESULT_OK        = 0,
  CEB_RESULT_NULL      = 1,
  CEB_RESULT_MEMORY    = 2,
  CEB_RESULT_FILEIO    = 3,
  CEB_RESULT_STRING    = 4,
  CEB_RESULT_NOT_FOUND = 5
} typedef CebResult;

#define CHECK_CEB(call)                           \
  {                                               \
    CebResult __result__ = call;                  \
    if (__result__ != CEB_RESULT_OK) {            \
      printf("CEB ERROR CODE: %d\n", __result__); \
      return __result__;                          \
    }                                             \
  }

#ifndef CEB_BUILD
CebResult ceb_load(CebData* data, const char* name);
#endif /* CEB_BUILD */

#endif /* CEB_H */
