; TODO : Verifier via valgrind + verifier malloc

section .text
    global ft_strdup

extern strlen
extern malloc
extern strcpy

ft_strdup:
    xor rax, rax                ; Initialisation a 0
    call strlen                 ; Call 
    inc rax
    push rdi                    ; Pousse la valeur actuelle de rdi sur la pile avant de l'utiliser dans une operation qui pourrait la modifier
    mov rdi, rax                ; deplace la longueur de la chaine dans le premier argument de la fonction malloc
    call malloc                 ; Alloue rax octets
    ; protection malloc ici
    xor rax, rax
    jl .error
    pop rsi                     ; Cette instruction dépile la valeur précédemment sauvegardée de rdi de la pile et la stocke dans rsi. Cela restaure la valeur précédente de rdi qui a été sauvegardée avec push rdi
    mov rdi, rax                ; rax contient le pointeur alloue
    call strcpy 

    ret

.error
    mov rdi, -1
    ret