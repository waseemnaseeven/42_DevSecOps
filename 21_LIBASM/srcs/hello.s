global      hello_world

section     .text


section     .data
    msg     db "Hello world!"
    len     equ $ -msg

hello_world:
    mov edx, len
    mov ecx, msg

    mov ebx, 1

    mov eax, 4
    int 0x80

    mov eax, 1
    int 0x80