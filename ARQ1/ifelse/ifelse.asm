;=============================================================
; Program: Compare first character of input string with 'a'
; Architecture: x86 (32-bit, Linux)
; Assembler: NASM
;=============================================================

segment .data               ; Initialized data segment
    mensi     db "Enter a string", 10             ; Prompt message for input
    tamensi   equ $ - mensi                       ; Length of the input message
    mensig    db "The character is equal", 10     ; Message for equal comparison
    tamig     equ $ - mensig                      ; Length of equal message
    mensdif   db "The character is different", 10 ; Message for not equal comparison
    tamdif    equ $ - mensdif                     ; Length of different message

segment .bss                ; Uninitialized data segment
    buff      resb 20       ; Buffer to store input string (max 20 bytes)
    qde       resd 4        ; Variable to store quantity of bytes read

section .text               ; Code segment
global _start               ; Entry point for linker

_start:
    ;=========================================================
    ; Step 1: Display input prompt
    ;=========================================================
    mov eax, 4              ; syscall: sys_write
    mov ebx, 1              ; file descriptor: stdout
    mov ecx, mensi          ; pointer to message
    mov edx, tamensi        ; message length
    int 0x80                ; make system call

    ;=========================================================
    ; Step 2: Read user input
    ;=========================================================
    mov eax, 3              ; syscall: sys_read
    mov ebx, 0              ; file descriptor: stdin
    mov ecx, buff           ; pointer to buffer
    mov edx, 20             ; max bytes to read
    int 0x80                ; make system call

    mov [qde], eax          ; store number of bytes read

    ;=========================================================
    ; Step 3: Compare first character with 'a'
    ;=========================================================
    cmp byte [buff], 'a'    ; compare first character with 'a'
    je igual                ; if equal, jump to 'igual' label

diferente:
    ;=========================================================
    ; Step 4a: Print "character is different"
    ;=========================================================
    mov eax, 4              ; syscall: sys_write
    mov ebx, 1              ; stdout
    mov ecx, mensdif        ; pointer to "different" message
    mov edx, tamdif         ; message length
    int 0x80                ; make system call
    jmp final               ; skip 'igual' section

igual:
    ;=========================================================
    ; Step 4b: Print "character is equal"
    ;=========================================================
    mov eax, 4              ; syscall: sys_write
    mov ebx, 1              ; stdout
    mov ecx, mensig         ; pointer to "equal" message
    mov edx, tamig          ; message length
    int 0x80                ; make system call

final:
    ;=========================================================
    ; Step 5: Exit program
    ;=========================================================
    mov eax, 1              ; syscall: sys_exit
    int 0x80                ; exit program

;-------------------------------------------------------------
; To assemble and run:
; nasm -f elf64 teste.asm
; ld teste.o -o teste
; ./teste
;-------------------------------------------------------------
