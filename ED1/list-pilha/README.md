# List1 – Simple Stack Operations in C
stack operations (push, pop, peek, etc) with a text-based menu.

## Requirements

- A C compiler such as `clang` or `gcc`.
- `make` installed (optional but recommended).

## Build and Run with `make`

1. Open a terminal in this folder.
2. Compile the program:

   ```bash
   make
   ```
This produces an executable named list-pilha.

Run the program:

```bash
./list-pilha
```

To clean up object files and the binary:

```bash
make clean
```

To build with debug flags (AddressSanitizer, symbols, no optimizations):

```bash
make debug
./list-pilha
```

## Build and Run Without make
If you prefer not to use make, compile manually:

```bash
clang -Wall -Wextra -Wshadow main.c list.c -o list-pilha -lm
```

Then run:

```bash
./list-pilha
```

Replace clang with gcc if desired.

---