section .text
    global ft_list_push_front

ft_list_push_front:
    push    rbp               ; Sauvegarde de la base du pointeur
    mov     rbp, rsp          ; Initialisation de la base du pointeur
    sub     rsp, 16           ; Allocation de 16 octets pour une variable locale

    mov     rax, 0            ; Initialisation du pointeur new_node à NULL
    mov     rdi, 16           ; Taille de la structure t_list
    call    malloc            ; Appel de la fonction malloc pour allouer de la mémoire
    test    rax, rax          ; Vérification si malloc a retourné NULL
    je      .exit             ; Si rax (adresse allouée) est NULL, sauter à .exit

    mov     QWORD [rax], rsi  ; Copie du pointeur data dans le champ data de new_node
    mov     QWORD [rax+8], rdi ; Copie du pointeur *begin_list dans le champ next de new_node

    mov     rsi, rax          ; Mise à jour de *begin_list avec l'adresse de new_node
    mov     rax, [rbp+8]      ; Récupération du pointeur sur *begin_list
    mov     QWORD [rax], rsi  ; Copie de l'adresse de new_node dans *begin_list

.exit:
    leave                     ; Restauration de la base du pointeur
    ret                       ; Retour de la fonction