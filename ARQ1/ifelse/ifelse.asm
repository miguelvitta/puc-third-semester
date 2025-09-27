segment .data ; dados inicializados
mensi db "Entre com uma string",10
tamensi equ $-mensi
mensig db "O caracter é igual",10
tamig equ $-mensig
mensdif db "O caracter é diferente",10
tamdif equ $-mensdif
segment .bss ; dados não inicializados
buff resb 20 ; vai receber a string lida
qde resd 4
section .text; Início do segmento de código
global _start; Símbolo para uso do LD
_start:
; Ponto de entrada do programa
; Exibindo a mensagem
mov eax, 4 ; PRINT
mov ebx, 1 ; FD da tela
mov ecx, mensi ; ponteiro da string
mov edx, tamensi
int 80h ; chamada ao kernel
; Recebendo a string
mov eax, 3 ; READ
mov ebx, 0 ; FD da teclado
mov ecx, buff; buffer de destino
mov edx, 20
int 80h ; chamada ao kernel
mov [qde], eax ; salvando quantos bytes ou caracteres entraram
; Modelando o IF
cmp byte[buff],"a"
je igual
diferente:
mov eax, 4 ; PRINT
mov ebx, 1 ; FD da tela
mov ecx, mensdif ; ponteiro da string
mov edx, tamdif
int 80h ; chamada ao kernel
jmp final
igual:
mov eax, 4 ; PRINT
mov ebx, 1 ; FD da tela
mov ecx, mensig ; ponteiro da string
mov edx, tamig
int 80h ; chamada ao kernel
final:
mov eax,1
int 0x80
; Exemplo: é montado com
; nasm –f elf64 teste.asm
; Gera o objeto teste.o
; ld teste.o –o teste
; Gera o executável teste
; ./teste
; Executa