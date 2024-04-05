section .data
    error_message db 'ft_read error', 0

section .text
    global ft_read

ft_read:
    mov rdi, rdi
    mov rsi, rsi
    mov rdx, rdx

    mov rax, 0
    syscall
    ret

    cmp rax, -1
    jnz .error

.error:
    mov rsi, error_message

