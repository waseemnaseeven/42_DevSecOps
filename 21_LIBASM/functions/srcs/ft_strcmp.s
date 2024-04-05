section .text
    global ft_strcmp

ft_strcmp:
    ; RDI contient l'adresse de la première chaîne (s1)
    ; RSI contient l'adresse de la deuxième chaîne (s2)
    
    xor     rax, rax           ; Initialiser le résultat à zéro
    
.loop:
    mov     al, [rdi]          ; Charger le caractère actuel de s1 dans AL
    cmp     al, [rsi]          ; Comparer le caractère actuel de s1 avec celui de s2
    je      .next_char         ; Si les caractères sont égaux, passer au caractère suivant
    
    ; Si les caractères sont différents, calculer la différence et retourner le résultat
    sub     al, [rsi]          ; Soustraire le caractère de s2 de celui de s1
    ret                        ; Renvoyer le résultat
    
.next_char:
    test    al, al             ; Vérifier si le caractère actuel est nul
    jz      .done              ; Si c'est le cas, sortir de la boucle
    
    inc     rdi                ; Passer au caractère suivant de s1
    inc     rsi                ; Passer au caractère suivant de s2
    jmp     .loop              ; Répéter le processus
    
.done:
    xor     rax, rax           ; Si les chaînes sont identiques, retourner 0
    ret
