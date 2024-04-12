; TODO : changer de registre + valgrind + lire char par char

section .text
    global ft_strcpy

ft_strcpy:

.loop:
    mov al, [rsi]           ; Deplace la premiere donneee du tableau dans un registre de 8 bits  
    test al, al             ; Savoir si la donnee vaut 0
    je .done                ; Sortir de la boucle

    mov [rdi], al           ; Deplacer le caractere sur le tableau rdi 
    inc rsi                 ; Incrementer le pointeur de source
    inc rdi                 ; Incrementer le pointeur de destination
    jmp .loop               ; Loop jusqua trouver le 0

.done:
    mov byte [rdi], 0       ; Mettre \0, il y a aussi mov [rdi], al
    ret
