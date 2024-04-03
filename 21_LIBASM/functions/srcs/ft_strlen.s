section .text
    global ft_strlen:

ft_strlen:
    xor rax, rax        ; Lorsqu'on le compare a lui meme, c'est forcement initialise a 0

loop:
    cmp byte[rdi], 0    ; Verifier si le caractere actuel de la chaine (rdi) est nul
    jp .done            ; Si c'est le cas, sortir de la boucle
    inc rax             ; Incrementer