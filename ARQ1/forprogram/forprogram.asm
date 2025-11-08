;=============================================================
; Program: Reverse an input word and invert letter case
; Architecture: x86 (32-bit, Linux)
; Assembler: NASM
;=============================================================

section .data
    msg_in  db "Write a word: ", 0            ; Prompt message for user input
    msg_out db "The inverse is: ", 0          ; Message shown before output
    nl      db 10                             ; Newline character

section .bss
    entrada resb 50      ; Buffer to store user input (max 50 bytes)
    saida   resb 50      ; Buffer to store reversed + case-inverted string
    tam     resd 1       ; Variable to store input length

section .text
global _start

_start:
    ;=========================================================
    ; Step 1: Print the input prompt
    ;=========================================================
    mov eax, 4           ; syscall number for sys_write
    mov ebx, 1           ; file descriptor 1 -> stdout
    mov ecx, msg_in      ; pointer to message to print
    mov edx, 15          ; message length in bytes ("Write a word: ")
    int 0x80             ; make system call

    ;=========================================================
    ; Step 2: Read the user input string
    ;=========================================================
    mov eax, 3           ; syscall number for sys_read
    mov ebx, 0           ; file descriptor 0 -> stdin
    mov ecx, entrada     ; buffer to store input
    mov edx, 50          ; maximum bytes to read
    int 0x80             ; make system call

    mov [tam], eax       ; store number of bytes read (includes '\n')

    ;=========================================================
    ; Step 3: Reverse the string and invert letter case
    ;=========================================================
    mov ecx, [tam]       ; load total bytes read
    dec ecx              ; ignore the newline ('\n') at end
    dec ecx              ; set index to last valid character (0-based)

    mov esi, entrada     ; source pointer -> start of input string
    add esi, ecx         ; move ESI to the last character of input
    mov edi, saida       ; destination pointer -> start of output buffer

inverte_loop:
    cmp ecx, -1          ; check if we processed all characters
    jle fim_inverte      ; if yes, exit loop

    mov al, [esi]        ; load current character from input (backward)

    ;=========================================================
    ; CASE CONVERSION: lowercase ↔ uppercase
    ;=========================================================
    cmp al, 'a'          ; check if char >= 'a'
    jl check_upper       ; if less, maybe uppercase or non-letter
    cmp al, 'z'          ; check if char <= 'z'
    jg check_upper       ; if greater, not lowercase
    sub al, 32           ; convert lowercase -> uppercase ('a'..'z' -> 'A'..'Z')
    jmp store_char       ; jump to store character

check_upper:
    cmp al, 'A'          ; check if char >= 'A'
    jl store_char        ; if less, leave unchanged
    cmp al, 'Z'          ; check if char <= 'Z'
    jg store_char        ; if greater, leave unchanged
    add al, 32           ; convert uppercase -> lowercase ('A'..'Z' -> 'a'..'z')

store_char:
    mov [edi], al        ; store converted character in output buffer

    dec esi              ; move backward in input string
    inc edi              ; move forward in output string
    dec ecx              ; decrement character index
    jmp inverte_loop     ; repeat loop

fim_inverte:
    mov byte [edi], 10   ; append newline character to output
    inc edi
    mov byte [edi], 0    ; null-terminate the output string

    ;=========================================================
    ; Step 4: Print output label ("The inverse is:")
    ;=========================================================
    mov eax, 4           ; syscall: sys_write
    mov ebx, 1           ; stdout
    mov ecx, msg_out     ; pointer to output label
    mov edx, 17          ; message length ("The inverse is: ")
    int 0x80             ; make system call

    ;=========================================================
    ; Step 5: Print reversed + case-inverted string
    ;=========================================================
    mov eax, 4           ; syscall: sys_write
    mov ebx, 1           ; stdout
    mov ecx, saida       ; pointer to transformed string
    mov edx, [tam]       ; number of characters read
    dec edx              ; exclude original newline from print length
    int 0x80             ; make system call

    ;=========================================================
    ; Step 6: Exit program
    ;=========================================================
    mov eax, 1           ; syscall: sys_exit
    xor ebx, ebx         ; exit code 0
    int 0x80             ; make system call

;-------------------------------------------------------------
; To assemble and run:
; nasm -f elf32 forprogram.asm
; ld -m elf_i386 forprogram.o -o forprogram
; ./forprogram
;-------------------------------------------------------------
