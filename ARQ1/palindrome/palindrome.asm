;=============================================================
; Program: Palindrome Checker
; Architecture: x86 (32-bit, Linux)
; Assembler: NASM
;=============================================================

section .data
    msg_in      db "Write a word: ", 0
    msg_yes     db "It IS a palindrome.", 10, 0
    msg_no      db "It is NOT a palindrome.", 10, 0

section .bss
    entrada resb 50      ; Input buffer (max 50 bytes)
    tam     resd 1       ; Length of input

section .text
global _start

_start:
    ;=========================================================
    ; Step 1: Prompt user for input
    ;=========================================================
    mov eax, 4
    mov ebx, 1
    mov ecx, msg_in
    mov edx, 15
    int 0x80

    ;=========================================================
    ; Step 2: Read user input
    ;=========================================================
    mov eax, 3
    mov ebx, 0
    mov ecx, entrada
    mov edx, 50
    int 0x80
    mov [tam], eax        ; Store total bytes read (includes '\n')

    ;=========================================================
    ; Step 3: Setup pointers for comparison
    ;=========================================================
    mov ecx, [tam]
    dec ecx               ; Ignore newline '\n'
    mov esi, entrada      ; Start pointer
    mov edi, entrada
    add edi, ecx          ; Move EDI to end (after last valid char)
    dec edi               ; Set to last valid character

check_loop:
    cmp esi, edi
    jge palindrome_ok     ; Crossed pointers → palindrome confirmed

    mov al, [esi]         ; Load from start
    mov bl, [edi]         ; Load from end
    cmp al, bl
    jne not_palindrome    ; Mismatch → not palindrome

    inc esi               ; Move forward
    dec edi               ; Move backward
    jmp check_loop

palindrome_ok:
    ;=========================================================
    ; Step 4A: Print "IS palindrome"
    ;=========================================================
    mov eax, 4
    mov ebx, 1
    mov ecx, msg_yes
    mov edx, 20
    int 0x80
    jmp end_prog

not_palindrome:
    ;=========================================================
    ; Step 4B: Print "NOT palindrome"
    ;=========================================================
    mov eax, 4
    mov ebx, 1
    mov ecx, msg_no
    mov edx, 25
    int 0x80

end_prog:
    ;=========================================================
    ; Step 5: Exit program
    ;=========================================================
    mov eax, 1
    xor ebx, ebx
    int 0x80

;-------------------------------------------------------------
; To assemble and run:
; nasm -f elf32 palindrome.asm
; ld -m elf_i386 palindrome.o -o palindrome
; ./palindrome
;-------------------------------------------------------------
