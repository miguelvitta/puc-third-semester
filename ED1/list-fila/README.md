# List1 – Simple Queue Operations in C
stack operations (add, get_front, etc) with a text-based menu.

## Requirements

- A C compiler such as `clang` or `gcc`.
- `make` installed (optional but recommended).

## Build and Run with `make`

1. Open a terminal in this folder.
2. Compile the program:

   ```bash
   make
   ```
This produces an executable named list-fila.

Run the program:

```bash
./list-fila
```

To clean up object files and the binary:

```bash
make clean
```

To build with debug flags (AddressSanitizer, symbols, no optimizations):

```bash
make debug
./list-fila
```

## Build and Run Without make
If you prefer not to use make, compile manually:

```bash
clang -Wall -Wextra -Wshadow -std=c11 *.c -o list-fila -lm
```

Then run:

```bash
./list-fila
```

Replace clang with gcc if desired.

---