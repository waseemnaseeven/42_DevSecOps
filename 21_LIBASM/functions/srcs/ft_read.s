; TODO : Stocker errno

extern __errno_location

section .text
    global ft_read

ft_read:
    mov rax, 0
    mov rdi, rdi
    mov rsi, rsi
    mov rdx, rdx

    syscall
    cmp rax, 0
    jl .error
    ret
    
.error:
	call __errno_location
    test rax, rax           ; Verifier si le pointeur retourne par __errno_location est null
    jz .error_exit          ; Quitter si le pointeur est null
    
    ; Si le pointeur est valide
    mov rdi, rax
    mov qword [rdi], -1

.error_exit:
    mov rax, -1
    ret
