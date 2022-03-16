extern scanf 
 extern printf 
 global main 
 section .text 
 main: 
	mov eax, 1
	mov [B], eax
	mov eax, 34
	mov [Temp_1], eax
	mov eax, [Temp_1]
	cmp eax, 0
	je equj1
	mov eax, 1
	mov [Temp_2], eax
	jmp nequj1
	equj1:
	mov eax, 2
	mov [Temp_2], eax
	nequj1:
	mov eax, [Temp_2]
	mov [A], eax
; This is a section to get user input
;Telling user to enter a variable value 
	 push inputVariableAux 
	 call printf 
	 pop eax 

	 push B
	 push inputFormat
	 call scanf
	 pop eax 
	 pop eax 

	mov eax, [A]
	mov ebx, [B]
	add eax, ebx
	mov [Temp_3], eax
	mov eax, [Temp_3]
	mov ebx, [F]
	add eax, ebx
	mov [Temp_4], eax
	mov eax, [Temp_4]
	mov ebx, 1
	add eax, ebx
	mov [Temp_5], eax
	mov eax, [Temp_5]
	mov [C], eax
	 push dword [A]
	push inputFormat 
	 call printf 
	pop eax 
	pop eax 


;Printing end of line
	push eol 
	call printf 
	pop eax 


ret


section .data 
inputFormat: db "%d",0 
eol: db "", 10,0 
inputVariableAux: db "Por favor ingrese el valor de la variable:  ",0 
B: dd 0 
A: dd 0 
Temp_1: dd 0 
Temp_2: dd 0 
C: dd 0 
Temp_3: dd 0 
F: dd 0 
Temp_4: dd 0 
Temp_5: dd 0 
