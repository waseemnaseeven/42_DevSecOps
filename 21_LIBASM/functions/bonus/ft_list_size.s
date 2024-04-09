section .text
    global ft_list_size

ft_list_size:
    xor rax, rax                ; Init de size a 0

.loop:
    cmp byte [rdi], 0
    je .done
    inc rax
    inc rdi
    jmp .loop

.done:
    ret