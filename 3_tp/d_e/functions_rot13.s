; Question 3

global _start

section .text
_start:

  call print_message
  call get_input
  call function_rot13
  call print_reversed
  call exit_program

; print message for user
print_message:
  mov rax, 1
  mov rdi, 1
  mov rsi, message
  mov rdx, len_message
  syscall
  ret

; get user input
get_input:
  mov rax, 0
  mov rdi, 0
  mov rsi, user_input
  mov rdx, 20
  syscall
  ret

function_rot13:
  mov rsi, user_input       ; pointer to user_input in rsi
  mov rdi, reversed         ; pointer to reversed in rdi

  xor rcx, rcx
  xor rax, rax        ; where we will temp store result

rot13:
  mov bl, [rsi+rcx]
  cmp bl, 0
  je finish_rot13
  
  ; check if lower case
  cmp bl, 97             ; 97=a
  jl not_lower_case
  cmp bl, 122
  jg not_lower_case
  add bl, 13
  cmp rbx, 122           ; check if went over 122=z (rbx otherwise doesn't work)
  jle add_result         ; if didn't go over, add to result otherwise, modulo
  sub bl, 26
  jmp add_result

not_lower_case:
  ; if it is not a lower case char, check if upper case, if not add as is
  cmp bl, 65          ; 65=A
  jl add_result
  cmp bl, 90          ; 90=Z
  jg add_result
  add bl, 13
  cmp rbx, 90          ; check if go over 90
  jle add_result      ; if not over 90 then can add character
  sub bl, 26          ; apply modulo if needed
  jmp add_result

add_result:
  ; add character as is
  mov [rdi], bl
  inc rcx
  inc rdi
  jmp rot13

finish_rot13:
  mov byte [rdi], 0         ; end string
  ret 

print_reversed:

  mov rax, 1
  mov rdi, 1
  mov rsi, result
  mov rdx, len_result
  syscall

  mov rax, 1
  mov rdi, 1
  mov rsi, reversed
  mov rdx, 20
  syscall
  ret

; exit program
exit_program:
  mov rax, 60
  xor rdi, rdi
  syscall
  ret


section .bss
  user_input resb 20             ; set user input to 20 bytes/char max
  reversed resb 20               ; set the resulted reversed string to 20 bytes/char max as well

section .data 
  message db 'Enter whatever you want:', 0x0A, 0
  len_message equ $ - message
  result db 'This is your message after a ROT13:', 0x0A, 0
  len_result equ $ - result