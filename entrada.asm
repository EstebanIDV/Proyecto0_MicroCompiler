global _main
section .text
_main:
	mov eax, [A]
	mov ebx, 70
	add eax, ebx
	mov [Temp1], eax
	mov eax, [Temp1]
	mov [B], eax
	mov eax, 5
	mov ebx, [B]
	add eax, ebx
	mov [Temp2], eax
	mov eax, [Temp2]
	mov [A], eax
	mov ebx, 0 ; exit code, 0=normal
	mov eax, 1	; exit command to kernel
	int	0x80
section .data 
B: dd 0 
A: dd 0 
Temp1: dd 0
Temp2: dd 0
