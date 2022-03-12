global _main 
 section .text 
 _main: 
	mov eax, 71
	mov Temp&1, eax
	mov eax, Temp&1
	mov B, eax
	mov eax, 5
	mov ebx, B
	add eax, ebx
	mov Temp&2, eax
	mov eax, Temp&2
	mov A, eax
            mov ax, 4C00h
            int 21h section .data 
B: dd 0 
Temp&1: dd 0 
A: dd 0 
Temp&2: dd 0 
