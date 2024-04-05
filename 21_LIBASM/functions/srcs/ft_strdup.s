section .text
    global ft_strdup

extern ft_strlen
extern malloc
extern ft_strcpy



ft_strdup:
    mov rax, rdi
    call ft_strlen
    mov rbx, rax

    mov rcx, rbx
    call malloc
    mov rdx, rcx

    mov rdi, rdx
    call ft_strcpy 

    ret

