extern scanf 
 extern printf 
 global main 
 section .text 
 main: 
	mov eax, [A]
	mov ebx, 70
	add eax, ebx
	mov [Temp_1], eax
	mov eax, [Temp_1]
	mov [B], eax
	mov eax, 5
	mov ebx, [B]
	add eax, ebx
	mov [Temp_2], eax
	mov eax, [Temp_2]
	mov [A], eax

ret


 section .data 
inputFormat: db "%d",0 
inputVariableAux: db "Por favor ingrese el valor de la variable:  ",0 
B: dd 0 
A: dd 0 
Temp_1: dd 0 
Temp_2: dd 0 
