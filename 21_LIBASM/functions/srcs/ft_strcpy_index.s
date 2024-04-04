section .text
    global ft_strcpy

ft_strcpy:
    xor rax, rax              ; Initialisation de l'index à 0

.loop:
    cmp byte [rsi + rax], 0   ; Vérifier si le caractère actuel de la source est NULL
    je .done                  ; Si c'est le cas, sortir de la boucle
    cmp byte [rdi], 0         ; Vérifier si la destination est NULL
    je .done                  ; Si c'est le cas, sortir de la boucle

    mov al, [rsi + rax]       ; Charger le caractère actuel de la source dans AL
    mov [rdi + rax], al       ; Copier le caractère de la source à la destination
    inc rax                   ; Avancer l'index
    jmp .loop                 ; Continuer le processus

.done:
    mov byte [rdi + rax], 0   ; Ajouter le caractère nul à la fin de la chaîne destination
    ret                       ; Renvoyer la valeur