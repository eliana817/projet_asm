#include <stdio.h>

int main(){

    char user_input[50];
    printf("Please enter whatever: \n");

    asm(
        ".intel_syntax noprefix"
        "mov rsi, %0;"          
        "mov rdi, 0;"           
        "mov rdx, 50;"          
        "mov rax, 0;"           
        "syscall;"     
                 
        :                       
        : "r"(user_input)       
        : "rsi", "rdi", "rdx", "rax" 
    );

    asm(
        ".intel_syntax noprefix"
        "mov rsi, %0;"          
        "mov rdi, 1;"           
        "mov rdx, 50;"          
        "mov rax, 1;"           
        "syscall;"              
        :                       
        : "r"(user_input)       
        : "rsi", "rdi", "rdx", "rax" 
    );
    
    printf("\n");

    return 0;

}