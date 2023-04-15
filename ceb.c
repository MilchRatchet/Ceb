#include "ceb.h"

#include <stdio.h>

#include "ceb_base.h"
#include "ceb_gen.h"

int main(int argc, char** argv) {
  if (argc < 3) {
    printf("USAGE: ceb [NAME OF OUTPUT] [FILE 1] [FILE 2] ...\n");
    return -1;
  }

  CebGenerator* gen;
  CHECK_CEB(ceb_gen_init(&gen, argv[1]));

  for (int i = 2; i < argc; i++) {
    CHECK_CEB(ceb_gen_add_file(gen, argv[i]));
  }

  CHECK_CEB(ceb_gen_execute(gen));
  CHECK_CEB(ceb_gen_clear(&gen));

  return 0;
}
