;=============================================================
; Program: Count Vowels and Consonants
; Architecture: x86 (32-bit, Linux)
; Assembler: NASM
;=============================================================

section .data
    msg_in      db "Write a word: ", 0
    msg_vowel   db "Vowels: ", 0
    msg_cons    db "Consonants: ", 0
    nl          db 10, 0

section .bss
    entrada resb 50          ; Input buffer
    tam     resd 1           ; Bytes read
    vowels  resd 1           ; Counter for vowels
    cons    resd 1           ; Counter for consonants
    numStr  resb 12          ; Buffer for integer-to-string conversion

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
    ; Step 2: Read input
    ;=========================================================
    mov eax, 3
    mov ebx, 0
    mov ecx, entrada
    mov edx, 50
    int 0x80
    mov [tam], eax

    ; Initialize counters to 0
    mov dword [vowels], 0
    mov dword [cons], 0

    ;=========================================================
    ; Step 3: Loop through each character
    ;=========================================================
    xor ecx, ecx              ; index = 0
count_loop:
    mov eax, [tam]
    cmp ecx, eax
    jge done_count

    mov al, [entrada + ecx]   ; current char
    cmp al, 10                ; newline?
    je done_count

    ; Convert uppercase → lowercase
    cmp al, 'A'
    jl skip_char
    cmp al, 'Z'
    jg check_lower
    add al, 32                ; to lowercase
    jmp check_vowel

check_lower:
    cmp al, 'a'
    jl skip_char
    cmp al, 'z'
    jg skip_char

check_vowel:
    cmp al, 'a'
    je add_vowel
    cmp al, 'e'
    je add_vowel
    cmp al, 'i'
    je add_vowel
    cmp al, 'o'
    je add_vowel
    cmp al, 'u'
    je add_vowel
    jmp add_cons

add_vowel:
    inc dword [vowels]
    jmp next_char

add_cons:
    inc dword [cons]
    jmp next_char

skip_char:
    ; Ignore non-letter
next_char:
    inc ecx
    jmp count_loop

done_count:
    ;=========================================================
    ; Step 4: Print vowel count
    ;=========================================================
    mov eax, 4
    mov ebx, 1
    mov ecx, msg_vowel
    mov edx, 8
    int 0x80

    mov eax, [vowels]
    mov edi, numStr
    call int_to_str

    mov eax, 4
    mov ebx, 1
    mov ecx, numStr
    mov edx, 12
    int 0x80

    mov eax, 4
    mov ebx, 1
    mov ecx, nl
    mov edx, 1
    int 0x80

    ;=========================================================
    ; Step 5: Print consonant count
    ;=========================================================
    mov eax, 4
    mov ebx, 1
    mov ecx, msg_cons
    mov edx, 13
    int 0x80

    mov eax, [cons]
    mov edi, numStr
    call int_to_str

    mov eax, 4
    mov ebx, 1
    mov ecx, numStr
    mov edx, 12
    int 0x80

    mov eax, 4
    mov ebx, 1
    mov ecx, nl
    mov edx, 1
    int 0x80

    ;=========================================================
    ; Step 6: Exit program
    ;=========================================================
    mov eax, 1
    xor ebx, ebx
    int 0x80

;=============================================================
; Function: int_to_str
; Converts EAX integer to ASCII string into buffer at EDI.
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
; nasm -f elf32 count.asm
; ld -m elf_i386 count.o -o count
; ./count
;-------------------------------------------------------------
