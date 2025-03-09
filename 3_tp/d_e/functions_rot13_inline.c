#include <stdio.h>
#include <string.h>

#define SYS_WRITE 1
#define SYS_READ 0
#define SYS_EXIT 60

void print_message() {
    char message[] = "Enter whatever you want:\n";
    asm(
        "mov rax, %0\n"
        "mov rdi, 1\n"
        "mov rsi, %1\n"
        "mov rdx, %2\n"
        "syscall"
        :
        : "r"(SYS_WRITE), "r"(message), "r"(strlen(message))
        : "rax", "rdi", "rsi", "rdx");
}

void get_input(char *input) {
    asm(
        "mov rax, %0\n"
        "mov rdi, 0\n"
        "mov rsi, %1\n"
        "mov rdx, 20\n"
        "syscall"
        :
        : "r"(SYS_READ), "r"(input)
        : "rax", "rdi", "rsi", "rdx");
}

void function_rot13(char *input, char *reversed) {
    asm(
        "mov rsi, %0\n"       
        "mov rdi, %1\n"       
        "xor rcx, rcx\n"      
        "xor rax, rax\n"      

    "rot13_loop:\n"
        "mov bl, [rsi + rcx]\n"
        "cmp bl, 0\n"
        "je rot13_finish\n"    
        "cmp bl, 97\n"         
        "jl rot13_not_lower_case\n"
        "cmp bl, 122\n"        
        "jg rot13_not_lower_case\n"
        "add bl, 13\n"         
        "cmp bl, 123\n"        
        "jl rot13_add_result\n"
        "sub bl, 26\n"         
    "rot13_not_lower_case:\n"
        "cmp bl, 65\n"         
        "jl rot13_add_result\n"
        "cmp bl, 90\n"         
        "jg rot13_add_result\n"
        "add bl, 13\n"         
        "cmp bl, 91\n"         
        "jl rot13_add_result\n"
        "sub bl, 26\n"         
    "rot13_add_result:\n"
        "mov [rdi + rcx], bl\n"  
        "inc rcx\n"               
        "jmp rot13_loop\n"        
    "rot13_finish:\n"
        "mov byte [rdi + rcx], 0\n" 
        :
        : "r"(input), "r"(reversed)
        : "rax", "rdi", "rsi", "rcx", "rbx", "rdx");
}

void print_reversed(char *reversed) {
    char result[] = "This is your message after a ROT13:\n";
    asm("mov rax, %0\n"
        "mov rdi, 1\n"
        "mov rsi, %1\n"
        "mov rdx, %2\n"
        "syscall"
        :
        : "r"(SYS_WRITE), "r"(result), "r"(strlen(result))
        : "rax", "rdi", "rsi", "rdx");

    asm("mov rax, %0\n"
        "mov rdi, 1\n"
        "mov rsi, %1\n"
        "mov rdx, 20\n"
        "syscall"
        :
        : "r"(SYS_WRITE), "r"(reversed)
        : "rax", "rdi", "rsi", "rdx");
}

void exit_program() {
    asm("mov rax, %0\n"
        "xor rdi, rdi\n"
        "syscall"
        :
        : "r"(SYS_EXIT)
        : "rax", "rdi");
}

int main() {
    char user_input[20];
    char reversed[20];

    print_message();
    get_input(user_input);
    function_rot13(user_input, reversed);
    print_reversed(reversed);
    exit_program();
    return 0;
}
