#ifndef CEB_H
#define CEB_H

#include <stdint.h>
#include <stdlib.h>

#ifndef CEB_BUILD

#if defined(__STDFC__) && __STDC_VERSION__ >= 199901
#define RESTRICT_KEYWORD restrict
#else
#define RESTRICT_KEYWORD
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * This function provides access to the embedded files.
 *
 * There are two modes: The default mode where the content of the specified file
 * is copied to a buffer and a mode where the size of the content of the specified
 * file is returned. The latter is meant to be used first in order to allocate
 * enough memory. Which mode is used is determined by the value stored in lmem.
 * If a value of -1 is stored in lmem then this value will be overwritten
 * with the size of the content of the specified file. If the value is not -1 then
 * the value stored in lmem is assumed to be the size of the buffer mem. If the buffer
 * is large enough to store the content of the specified file then the file is copied
 * to the buffer, else an error is thrown.
 *
 * Note that if the specified file is not present, no error is thrown. Instead the
 * function considers not present files to be of zero size. This means that if on
 * entry the value stored in lmem is -1 then this value will be set to 0, indicating
 * an empty file.
 *
 * If any of the inputs is a null pointer, an error will be thrown. The only exception
 * being mem which is ignored in the case that the value stored in lmem is -1.
 *
 * In this version of Ceb, the value in info is always 1 if an error is thrown. Note
 * that future versions of Ceb may indicate the reason of the error using other values.
 *
 * \param name a string containing the name of the file without its original path
 * \param mem a buffer to which the file will be copied (only if *lmem != -1)
 * \param lmem the size of the buffer in bytes,
 *              if this value is set to -1 then it will be overwritten by the size of the file in bytes
 * \param info the error code value, on success the value 0 will be written, otherwise a non-zero value
 *
 */
void ceb_load(
  const char RESTRICT_KEYWORD* name, void RESTRICT_KEYWORD* mem, int64_t RESTRICT_KEYWORD* lmem, uint64_t RESTRICT_KEYWORD* info);

#ifdef __cplusplus
}
#endif

#endif /* CEB_BUILD */

#endif /* CEB_H */
