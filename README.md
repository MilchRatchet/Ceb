# Ceb

Ceb (C embed binaries) is a tool for embedding any binary file into an executable through a single C file. The access to each file is then abstracted away through a loader function which allows for dynamic embedding of files without changing the code of the executable.

This project is in early development and not yet fully functioning.

## Usage

```C

#include "ceb.h"

// ...

int64_t size = -1;
uint64_t info;

ceb_load("file_name.example", (void*) 0, &size, &info);

if (info || !size) {
  // Error
}

void* data = malloc(size);

ceb_load("file_name.example", data, &size, &info);

if (info) {
  // Error
}

```

## License

Please see [LICENSE](/LICENSE).
