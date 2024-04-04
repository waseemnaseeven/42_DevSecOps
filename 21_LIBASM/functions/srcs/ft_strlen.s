section .text
    global ft_strlen

ft_strlen:
    xor rax, rax        ; Lorsqu'on le compare a lui meme, c'est forcement initialise a 0

.loop:
    cmp byte [rdi], 0   ; Verifier si le caractere actuel de la chaine (rdi) est nul
    je .done            ; Si c'est le cas, sortir de la boucle
    inc rax             ; Incrementer
    inc rdi             ; Passer au caractere suivant, equivalent de i++
    jmp .loop           ; Repeter le processus

.done:
    ret                 ; Renvoyer la valeur de retour, donc le registre rax
