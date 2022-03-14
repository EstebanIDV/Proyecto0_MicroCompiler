extern scanf 
 extern printf 
 global main 
 section .text 
 main: 
	mov eax, 3
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
	sub eax, ebx
	mov [Temp_1], eax
	mov eax, [Temp_1]
	mov [C], eax
	 push dword [C]
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
A: dd 0 
B: dd 0 
C: dd 0 
Temp_1: dd 0 
