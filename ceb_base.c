#include "ceb_base.h"

#include <stdint.h>

uint64_t ceb_hash_fnv1a(const char* str) {
  uint64_t hash = 0xcbf29ce484222325;

  for (size_t i = 0; str[i] != '\0'; i++) {
    hash = hash ^ ((uint64_t) str[i]);
    hash = hash * 0x100000001b3;
  }

  return hash;
}
