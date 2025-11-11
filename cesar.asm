;=============================================================
; Program: Caesar Cipher (encrypts input text with a fixed shift)
; Architecture: x86 (32-bit, Linux)
; Assembler: NASM
;=============================================================

section .data
    msg_in      db "Write a word: ", 0
    msg_out     db "Encrypted text: ", 0
    nl          db 10
    shift       db 3              ; Caesar cipher shift value (+3)

section .bss
    entrada resb 50               ; Input buffer (max 50 bytes)
    saida   resb 50               ; Output buffer (max 50 bytes)
    tam     resd 1                ; Number of bytes read

section .text
global _start

_start:
    ;=========================================================
    ; Step 1: Print input prompt
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

    mov [tam], eax               ; Save number of bytes read

    ;=========================================================
    ; Step 3: Encrypt input using Caesar cipher
    ;=========================================================
    mov ecx, 0                   ; Index
    mov esi, entrada             ; Source
    mov edi, saida               ; Destination
    mov bl, [shift]              ; Load shift value

encrypt_loop:
    mov al, [esi + ecx]          ; Load current character
    cmp al, 10                   ; Check for newline
    je end_encrypt               ; Stop at newline

    ;------------------------------
    ; If character is lowercase
    ;------------------------------
    cmp al, 'a'
    jl check_upper
    cmp al, 'z'
    jg check_upper
    sub al, 'a'
    add al, bl
    mov ah, 26
    div ah                       ; remainder in al (simulate mod 26)
    add al, 'a'
    jmp store_char

check_upper:
    ;------------------------------
    ; If character is uppercase
    ;------------------------------
    cmp al, 'A'
    jl store_char
    cmp al, 'Z'
    jg store_char
    sub al, 'A'
    add al, bl
    mov ah, 26
    div ah
    add al, 'A'

store_char:
    mov [edi + ecx], al          ; Store encrypted char
    inc ecx
    jmp encrypt_loop

end_encrypt:
    mov byte [edi + ecx], 10     ; Newline
    inc ecx
    mov byte [edi + ecx], 0      ; Null terminator

    ;=========================================================
    ; Step 4: Print output message
    ;=========================================================
    mov eax, 4
    mov ebx, 1
    mov ecx, msg_out
    mov edx, 17
    int 0x80

    ;=========================================================
    ; Step 5: Print encrypted string
    ;=========================================================
    mov eax, 4
    mov ebx, 1
    mov ecx, saida
    mov edx, [tam]
    int 0x80

    ;=========================================================
    ; Step 6: Exit
    ;=========================================================
    mov eax, 1
    xor ebx, ebx
    int 0x80

;-------------------------------------------------------------
; To assemble and run:
; nasm -f elf32 caesar.asm
; ld -m elf_i386 caesar.o -o caesar
; ./caesar
;-------------------------------------------------------------
