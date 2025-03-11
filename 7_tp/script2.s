section .data
    message db "Enter text: ", 0
    len_message equ $ - message
    buffer times 256 db 0

section .bss
    input resb 256

section .text
    global _start

_start:
    ; Afficher un message
    mov rax, 1
    mov rdi, 1
    mov rsi, message
    mov rdx, len_message
    syscall

    ; Lire l’entrée utilisateur
    mov rax, 0
    mov rdi, 0
    mov rsi, input
    mov rdx, 255
    syscall

    ; Appliquer ROT13 partiel
    mov rsi, input
    xor rcx, rcx  ; Compteur de position

rot13_loop:
    lodsb            ; Charger le prochain caractère dans AL
    test al, al      ; Vérifier si fin de chaîne
    jz end_rot13
    test cl, 1       ; Appliquer ROT13 seulement sur un caractère sur deux
    jnz no_transform

    cmp al, 'A'
    jb no_transform
    cmp al, 'Z'
    ja check_lower
    add al, 13
    cmp al, 'Z'
    jbe store
    sub al, 26
    jmp store

check_lower:
    cmp al, 'a'
    jb no_transform
    cmp al, 'z'
    ja no_transform
    add al, 13
    cmp al, 'z'
    jbe store
    sub al, 26

store:
    stosb
    jmp rot13_loop

no_transform:
    stosb
    jmp rot13_loop

end_rot13:
    ; Afficher le texte transformé
    mov rax, 1
    mov rdi, 1
    mov rsi, input
    mov rdx, 255
    syscall

    ; Quitter
    mov rax, 60
    xor rdi, rdi
    syscall
