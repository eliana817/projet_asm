; Question 2.c

global _start

section .text
_start:
  ; print message for user
  mov rax, 1             ; syscall for write
  mov rdi, 1             ; stdout
  mov rsi, message
  mov rdx, len_message
  syscall

  ; get user input
  mov rax, 0             ; syscall for read
  mov rdi, 0             ; stdin
  mov rsi, user_input    ; where the input data will be stored
  mov rdx, 2             ; 2 bytes, one byte per char (max is 12 with 2 bytes)
  syscall

  ; to convert to int
  mov rsi, user_input
  xor rax, rax           ; where converted int will be stored, clear data
  xor rbx, rbx           ; for mult, clear data
  
  xor rcx, rcx          ; the loop counter

string_to_int:
  mov bl, [rsi+rcx]     ; read character by character (byte). bl is one byte of rbx.
  cmp bl, 48            ; check if end of string (48 = 0)
  jl end_string_to_int
  
  cmp bl, 57            ; check if we are reading a char that isn't between 0 and 9. (57 = 9)
  jg end_string_to_int

  sub bl, 48            ; convert ascii to int
  add rax, rbx          ; add result of converted char to rax
  mov rbx, 10
  mul rbx
  inc rcx               ; move to the next character
  jmp string_to_int

end_string_to_int:
  cmp rcx, 0
  je factorial
  mov rbx, 10
  div rbx

  mov rcx, rax           ; store result in rcx for multiplication (loop counter register)
  mov rax, 1             ; start mul at 1
  

factorial:
  cmp rcx, 1             ; if rcx == 1 done
  je end_factorial
  mul rcx                ; rax = rax * rcx (rax is implicit when using mul)
  dec rcx
  jmp factorial

end_factorial:
  mov rsi, result
  add rsi, 7             ; move to the end of result buffer
  mov byte [rsi], 0      ; add end of string symbol to result
  dec rsi                ; go backwards

int_to_string:
  xor rdx, rdx           ; by precaution
  mov rbx, 10            ; divide rax by 10
  div rbx                ; quotient in rax, remainder in dl --> to convert to ascii
  add dl, '0'            ; convert dl to ascii
  mov [rsi], dl          ; [rsi] to go to the address pointed by rsi
  dec rsi                ; move to previous char
  cmp rax, 0             ; check if end of int
  jnz int_to_string      ; if not zero

print:
  ; print result
  mov rax, 1
  mov rdi, 1
  mov rsi, result
  mov rdx, 8
  syscall

  ; exit program
  mov rax, 60
  xor rdi, rdi           ; same as mov rdi, 0 but more efficient
  syscall


; to store uninitialized data such as user input and reserve space

section .bss
  user_input resb 2
  result resq 1      ; resq is for quad word meaning 8 bytes (here 64bits)
                     ; the max result with 12 would be 29 bits so with 64 there is enough


; to store initialized data

section .data
  message db 'Enter a number <= 12:', 0x0A, 0  ; db to define byte for each character
  len_message equ $ - message             ; $ - is to get the length
