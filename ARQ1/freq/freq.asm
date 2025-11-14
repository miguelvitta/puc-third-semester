;=============================================================
; Program: Character Frequency Counter
; Architecture: x86 (32-bit, Linux)
; Assembler: NASM
;=============================================================

section .data
    msg_char    db "Enter a character: ", 0
    msg_word    db "Enter a word: ", 0
    msg_result  db "Occurrences: ", 0
    nl          db 10, 0

section .bss
    charBuf resb 2          ; store one character + newline
    entrada resb 50         ; store the word
    tam     resd 1          ; size of word
    count   resd 1          ; counter of occurrences
    numStr  resb 12         ; buffer for integer-to-string

section .text
global _start

_start:
    ;=========================================================
    ; Step 1: Ask for the character
    ;=========================================================
    mov eax, 4
    mov ebx, 1
    mov ecx, msg_char
    mov edx, 20
    int 0x80

    ; Read one character
    mov eax, 3
    mov ebx, 0
    mov ecx, charBuf
    mov edx, 2
    int 0x80

    mov al, [charBuf]       ; character to search
    mov [charBuf], al       ; keep only the character

    ;=========================================================
    ; Step 2: Ask for the word
    ;=========================================================
    mov eax, 4
    mov ebx, 1
    mov ecx, msg_word
    mov edx, 15
    int 0x80

    mov eax, 3
    mov ebx, 0
    mov ecx, entrada
    mov edx, 50
    int 0x80
    mov [tam], eax

    ;=========================================================
    ; Step 3: Count occurrences
    ;=========================================================
    mov dword [count], 0    ; reset counter
    xor ecx, ecx            ; index = 0

count_loop:
    mov eax, [tam]
    cmp ecx, eax
    jge done_count

    mov al, [entrada + ecx]
    cmp al, 10              ; stop at newline
    je done_count

    cmp al, [charBuf]       ; compare with target
    jne next_char

    inc dword [count]       ; match → increment

next_char:
    inc ecx
    jmp count_loop

done_count:
    ;=========================================================
    ; Step 4: Print result label
    ;=========================================================
    mov eax, 4
    mov ebx, 1
    mov ecx, msg_result
    mov edx, 13
    int 0x80

    ;=========================================================
    ; Step 5: Convert count to string
    ;=========================================================
    mov eax, [count]
    mov edi, numStr
    call int_to_str

    ;=========================================================
    ; Step 6: Print number
    ;=========================================================
    mov eax, 4
    mov ebx, 1
    mov ecx, numStr
    mov edx, 12
    int 0x80

    ; print newline
    mov eax, 4
    mov ebx, 1
    mov ecx, nl
    mov edx, 1
    int 0x80

    ;=========================================================
    ; Step 7: Exit
    ;=========================================================
    mov eax, 1
    xor ebx, ebx
    int 0x80

;=============================================================
; Function: int_to_str
; Converts integer in EAX to ASCII string at buffer EDI
;=============================================================
int_to_str:
    mov ebx, 10
    mov ecx, edi
    add ecx, 11
    mov byte [ecx], 0

convert_loop:
    dec ecx
    xor edx, edx
    div ebx
    add dl, '0'
    mov [ecx], dl
    test eax, eax
    jnz convert_loop

    mov edi, ecx
    mov esi, edi
    mov edi, numStr

copy_loop:
    mov al, [esi]
    mov [edi], al
    inc esi
    inc edi
    cmp byte [esi], 0
    jne copy_loop

    mov byte [edi], 0
    ret

;-------------------------------------------------------------
; To assemble and run:
; nasm -f elf32 freq.asm
; ld -m elf_i386 freq.o -o freq
; ./freq
;-------------------------------------------------------------
