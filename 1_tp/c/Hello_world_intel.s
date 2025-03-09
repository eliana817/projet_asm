; Intel syntax

global _start                             ; equivalent of main in C

section .text                             ; section for code to be ran
_start:                                   
  mov rax, 1                              ; sys_write
  mov rdi, 1                              ; stdout
  mov rsi, message                        ; message to print
  mov rdx, len_message                    ; message length
  syscall                                 ; run

  ; to exit the program
  mov rax, 60                             ; exit 
  mov rdi, 0                              ; 0 = error output
  syscall                                 ; run

section .data
  message db 'Hello World!", 0x0A, 0      ; (0x0A) is for newline
  len_mesage equ $ - message              ; ($ -) is for length of message

; To compile: intel = nasm