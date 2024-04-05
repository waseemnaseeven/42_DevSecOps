section .data
    error_message db 'ft_write error', 0

section .text
    global ft_write

ft_write:
    ; 3 Parametres int fd, const void *buf, size_t count
    ; RDI pour int fd
    ; RSI pour const void* buf
    ; RDX pour size_t count

    mov rdi, rdi            ; charge fd dans le registre rdi
    mov rsi, rsi            ; charge buf dans le registre rsi
    mov rdx, rdx            ; charge count dans le registre rdx
    
    mov rax, 1              ; Code 1 pour l'appel systeme write
    syscall

    ; Check for errors
    cmp rax, -1             ; Si syscall return -1
    jnz .error              ; jump vers error si n'est pas egal a 0

.error
    mov rsi, error_message