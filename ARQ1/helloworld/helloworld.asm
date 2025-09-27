segment .data
mens db "Até amanhã, pessoal",10
compr equ $-mens
section .text
global _start

_start: 
	mov edx,compr
	mov ecx,mens
	mov ebx,1
	mov eax,4
	int 80h
	
fim:
	mov eax,1
	mov ebx,0
	int 80h