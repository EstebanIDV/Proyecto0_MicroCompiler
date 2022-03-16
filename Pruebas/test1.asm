extern scanf 
 extern printf 
 global main 
 section .text 
 main: 
; This is a section to get user input
;Telling user to enter a variable value 
	 push inputVariableAux 
	 call printf 
	 pop eax 

	 push A
	 push inputFormat
	 call scanf
	 pop eax 
	 pop eax 

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
	mov [C], eax
	mov eax, [B]
	mov [D], eax
	mov eax, [A]
	mov ebx, [B]
	add eax, ebx
	mov [Temp_1], eax
	mov eax, [Temp_1]
	mov [B], eax
	mov eax, [B]
	mov ebx, [A]
	sub eax, ebx
	mov [Temp_2], eax
	mov eax, [Temp_2]
	mov [A], eax
	mov eax, [B]
	mov ebx, [A]
	sub eax, ebx
	mov [Temp_3], eax
	mov eax, [Temp_3]
	mov [B], eax
	 push dword [A]
	push inputFormat 
	 call printf 
	pop eax 
	pop eax 


;Printing end of line
	push eol 
	call printf 
	pop eax 

	 push dword [B]
	push inputFormat 
	 call printf 
	pop eax 
	pop eax 


;Printing end of line
	push eol 
	call printf 
	pop eax 

	mov eax, [A]
	mov ebx, [D]
	sub eax, ebx
	mov [Temp_4], eax
	mov eax, [Temp_4]
	cmp eax, 0
	je equj0
	mov eax, 1
	mov [Temp_5], eax
	jmp nequj0
	equj0:
	mov eax, 0
	mov [Temp_5], eax
	nequj0:
	mov eax, [Temp_5]
	mov [D], eax
	mov eax, [B]
	mov ebx, [C]
	sub eax, ebx
	mov [Temp_6], eax
	mov eax, [Temp_6]
	cmp eax, 0
	je equj0
	mov eax, 1
	mov [Temp_7], eax
	jmp nequj0
	equj0:
	mov eax, 0
	mov [Temp_7], eax
	nequj0:
	mov eax, [Temp_7]
	mov [C], eax
; This is a section to get user input
;Telling user to enter a variable value 
	 push inputVariableAux 
	 call printf 
	 pop eax 

	 push D
	 push inputFormat
	 call scanf
	 pop eax 
	 pop eax 

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
D: dd 0 
Temp_1: dd 0 
Temp_2: dd 0 
Temp_3: dd 0 
Temp_4: dd 0 
Temp_5: dd 0 
Temp_6: dd 0 
Temp_7: dd 0 
