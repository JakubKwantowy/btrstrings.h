# btrstrings.h #

A basic string library.

## Installation ##

### As a header ###

Put `btrstrings.h` in your project's includes folder and put a file similar to `btrstrings.c`.

```c
#define BTRSTRINGS_IMPLEMENTATION
#include "btrstrings.h"
```

### As a static library ###

Make sure that the following are installed

- GNU Make
- GCC (or a similar C compiler, can be changed in the Makefile)

Run the following commands in a terminal.

```bash
mkdir bin
make
```

On some systems (such as BSD) replace `make` with `gmake`.

Put `btrstrings.h` in your project's includes folder and place `bin/btrstrings.a` in your project's library folder.

## Documentation ##

Documentation can be found in the `btrstrings.h` file.
