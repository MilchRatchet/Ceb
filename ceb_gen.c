#include "ceb_gen.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ceb.h"
#include "ceb_base.h"

#define CEB_GEN_LOAD_CHUNK_SIZE 8192

CebResult ceb_gen_init(CebGenerator** gen, const char* name) {
  if (!gen) {
    return CEB_RESULT_NULL;
  }

  *gen = calloc(1, sizeof(CebGenerator));

  if (!gen) {
    return CEB_RESULT_MEMORY;
  }

  const size_t len = strlen(name) + 1;

  (*gen)->name = malloc(len);

  if (!(*gen)->name) {
    return CEB_RESULT_MEMORY;
  }

  memcpy((*gen)->name, name, len);

  (*gen)->files = calloc(16, sizeof(char*));

  if (!(*gen)->files) {
    return CEB_RESULT_MEMORY;
  }

  (*gen)->allocated = 16;

  return CEB_RESULT_OK;
}

CebResult ceb_gen_add_file(CebGenerator* gen, const char* file) {
  if (!gen) {
    return CEB_RESULT_NULL;
  }

  if (!file) {
    return CEB_RESULT_NULL;
  }

  if (gen->allocated == gen->count) {
    gen->allocated = gen->allocated + gen->allocated;
    gen->files     = realloc(gen->files, gen->allocated);

    if (!gen->files) {
      return CEB_RESULT_MEMORY;
    }
  }

  const size_t len = strlen(file) + 1;

  gen->files[gen->count] = malloc(len);

  if (!gen->files[gen->count]) {
    return CEB_RESULT_MEMORY;
  }

  memcpy(gen->files[gen->count], file, len);

  gen->count++;

  return CEB_RESULT_OK;
}

static void strreplace(char* str, const size_t num_chars, const char in, const char out) {
  for (size_t i = 0; i < num_chars; i++) {
    if (str[i] == in) {
      str[i] = out;
    }
  }
}

static CebResult read_file(CebData* data, const char* path) {
  FILE* file = fopen(path, "rb");

  if (!file) {
    return CEB_RESULT_FILEIO;
  }

  size_t bytes_read     = 0;
  size_t allocated_size = CEB_GEN_LOAD_CHUNK_SIZE;

  data->data = malloc(CEB_GEN_LOAD_CHUNK_SIZE + 1);

  if (!data->data) {
    return CEB_RESULT_MEMORY;
  }

  data->size = 0;

  while (bytes_read = fread(data->data + data->size, 1, allocated_size - data->size, file)) {
    data->size += bytes_read;

    allocated_size = allocated_size * 2;

    data->data = realloc(data->data, allocated_size + 1);

    if (!data->data) {
      return CEB_RESULT_MEMORY;
    }
  }

  fclose(file);

  data->data[data->size] = '\0';

  printf("%s\n", data->data);
}

static CebResult _ceb_gen_create_cebdata(CebData* data, const char* file) {
  const char* slash     = strrchr(file, '/');
  const char* backslash = strrchr(file, '\\');

  const char* filename_start = file;

  if (slash || backslash) {
    filename_start = (slash > backslash) ? slash + 1 : backslash + 1;
  }

  size_t filename_len = strlen(filename_start) + 1;

  data->name = malloc(filename_len);

  if (!data->name) {
    return CEB_RESULT_MEMORY;
  }

  memcpy(data->name, filename_start, filename_len);

  data->hash = ceb_hash_fnv1a(data->name);

  CHECK_CEB(read_file(data, file));

  return CEB_RESULT_OK;
}

static CebResult _ceb_gen_write_date(FILE* file, const CebData* data) {
  const size_t num_numbers = (data->size + 7) / 8;
  char* buffer             = malloc(num_numbers * 19 + 4096);

  if (!buffer) {
    return CEB_RESULT_MEMORY;
  }

  const size_t len_size_line = sprintf(buffer, "static size_t size_%" PRIu64 " = %zu;\n", data->hash, data->size);
  fwrite(buffer, 1, len_size_line, file);

  const uint64_t* data64_i = (const uint64_t*) data->data;

  size_t buffer_offset = 0;

  buffer_offset += sprintf(buffer, "static uint64_t data_%" PRIu64 "[] = {", data->hash);

  for (size_t j = 0; j < num_numbers - 1; j++) {
    const uint64_t v = data64_i[j];

    if (v < 10) {
      buffer_offset += sprintf(buffer + buffer_offset, "%" PRIu64 ",", v);
    }
    else {
      buffer_offset += sprintf(buffer + buffer_offset, "0x%" PRIx64 ",", v);
    }
  }

  uint64_t v             = 0;
  const int last_iter    = ((data->size % 8) == 0) ? 8 : (data->size % 8);
  const uint8_t* data8_i = (const uint8_t*) (data->data + 8 * (num_numbers - 1));

  for (int j = 0; j < 8; j++) {
    const uint8_t w = (j < last_iter) ? data8_i[j] : 0;

    v = (v << 8) | w;
  }

  buffer_offset += sprintf(buffer + buffer_offset, "0x%" PRIx64 "};\n", v);

  fwrite(buffer, 1, buffer_offset, file);

  free(buffer);

  return CEB_RESULT_OK;
}

CebResult ceb_gen_execute(const CebGenerator* gen) {
  CebData* datas = (CebData*) calloc(1, sizeof(CebData) * gen->count);

  if (!datas) {
    return CEB_RESULT_MEMORY;
  }

  for (uint32_t i = 0; i < gen->count; i++) {
    CHECK_CEB(_ceb_gen_create_cebdata(datas + i, gen->files[i]));
  }

  const size_t name_len = strlen(gen->name) + 1;

  char* output_path = malloc(name_len + 2);

  if (!output_path) {
    return CEB_RESULT_MEMORY;
  }

  sprintf(output_path, "%s.c", gen->name);

  FILE* output = fopen(output_path, "w");

  free(output_path);

  if (!output) {
    return CEB_RESULT_FILEIO;
  }

  fwrite("#include \"ceb.h\"\n", 1, 17, output);
  fwrite("#include <stdlib.h>\n", 1, 20, output);
  fwrite("#include <stdint.h>\n", 1, 20, output);

  for (uint32_t i = 0; i < gen->count; i++) {
    CHECK_CEB(_ceb_gen_write_date(output, datas + i));
  }

  if (fclose(output)) {
    return CEB_RESULT_FILEIO;
  }

  return CEB_RESULT_OK;
}

CebResult ceb_gen_clear(CebGenerator** gen) {
  if (!gen || !*gen) {
    return CEB_RESULT_NULL;
  }

  free((*gen)->name);

  for (uint32_t i = 0; i < (*gen)->count; i++) {
    free((*gen)->files[i]);
  }

  free((*gen)->files);

  free(*gen);
  *gen = (CebGenerator*) 0;

  return CEB_RESULT_OK;
}
