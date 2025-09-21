# List1 – Simple List Operations in C

This program implements basic list operations (insert, remove, union, intersection, difference, etc.) with a text-based menu.

## Requirements

- A C compiler such as `clang` or `gcc`.
- `make` installed (optional but recommended).

## Build and Run with `make`

1. Open a terminal in this folder.
2. Compile the program:

   ```bash
   make
   ```
This produces an executable named list1.

Run the program:

```bash
./list1
```

To clean up object files and the binary:

```bash
make clean
```

To build with debug flags (AddressSanitizer, symbols, no optimizations):

```bash
make debug
./list1
```

## Build and Run Without make
If you prefer not to use make, compile manually:

```bash
clang -Wall -Wextra -Wshadow main.c list.c -o list1 -lm
```

Then run:

```bash
./list1
```

Replace clang with gcc if desired.

---