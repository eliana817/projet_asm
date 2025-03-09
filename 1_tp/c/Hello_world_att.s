; AT&T syntax

.global _start

.section .text
_start
  mov $1, %rax 
  mov $1, %rdi 
  lea message(%rip), %rsi 
  mov $14, %rdx 
  syscall

  ; exit program
  mov $60, %rax
  xor %rdi, %rdi                ; same as "mov $0, %rdi" 
  syscall

.section .data
  msg: .ascii "Hello World!\n"

; To compile: AT&T = as