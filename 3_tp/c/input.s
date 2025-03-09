; Question 3

global _start

section .text
_start:
  ; print message for user
  mov rax, 1
  mov rdi, 1
  mov rsi, message
  mov rdx, len_message
  syscall

  ; get user input
  mov rax, 0
  mov rdi, 0
  mov rsi, user_input
  mov rdx, 20
  syscall

  ; print input
  mov rax, 1
  mov rdi, 1
  mov rsi, user_input
  mov rdx, 20
  syscall

; exit program + pop registers?
  mov rax, 60
  xor rdi, rdi
  syscall


section .bss
  user_input resb 20             ; set user input to 20 bytes/char max

section .data 
  message db 'Enter whatever you want:', 0x0A, 0
  len_message equ $ - message