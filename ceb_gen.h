#ifndef CEB_GEN_H
#define CEB_GEN_H

#include <stdint.h>

#include "ceb_base.h"

struct CebGenerator {
  char* name;
  char** files;
  uint32_t count;
  uint32_t allocated;
} typedef CebGenerator;

CebResult ceb_gen_init(CebGenerator** gen, const char* name);
CebResult ceb_gen_add_file(CebGenerator* gen, const char* file);
CebResult ceb_gen_execute(const CebGenerator* gen);
CebResult ceb_gen_clear(CebGenerator** gen);

#endif /* CEB_GEN_H */
