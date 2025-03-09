void main(){

    char msg[] = "Hello World!\n";

    // Method 1
    long ax;
    asm("syscall": "=a"(ax) : "0"(1), "S"(msg), "d"(13));

    // Method 2 (INTEL)
    asm(".intel_syntax noprefix\n"
        "mov rax, 1\n"
        "mov rdi, 1\n"
        "mov rsi, %0\n"
        "mov rdx, offset 13\n"
        "syscall\n"
        :
        : "r"(msg)
        : "rax", "rdi", "rsi", "rdx"
    );

    // Method 3 (AT&T)
    asm(
        "mov $1, %%rax;"
        "mov $1, %%rdi;"
        "mov %0, %%rsi;"
        "mov $13, %%rdx;"
        "syscall;"
        :
        : "r"(msg)
        : "%rax", "%rdi", "%rsi", "%rdx"
    );

}