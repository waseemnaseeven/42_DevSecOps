section .data
    error_message db 'ft_write error', 0

extern __errno_location

section .text
    global ft_write

ft_write:
    ; 3 Parametres int fd, const void *buf, size_t count
    ; RDI pour int fd
    ; RSI pour const void* buf
    ; RDX pour size_t count

    mov rax, 1              ; Code 1 pour l'appel systeme write
    mov rdi, rdi            ; charge fd dans le registre rdi
    mov rsi, rsi            ; charge buf dans le registre rsi
    mov rdx, rdx            ; charge count dans le registre rdx
    
    syscall
    cmp rax, 0              ; Tcheck si syscall write est a 0
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