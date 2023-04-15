#ifndef CEB_H
#define CEB_H

#include <stdint.h>
#include <stdlib.h>

#ifndef CEB_BUILD
void ceb_load(const char* name, void* mem, int64_t* lmem, uint64_t* info);
#endif /* CEB_BUILD */

#endif /* CEB_H */
