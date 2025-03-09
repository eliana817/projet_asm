#include <stdio.h>

int main(){
    unsigned int n, res;
    printf("Entrez un nombre (en-dessous de 12): ");
    scanf("%u", &n);

    if (n >= 12) {
        printf("Le nombre doit etre plus petit que 12.\n");
        return 1;
    }

    asm(
        "movl $1, %%eax;\n"
        "movl %1, %%ecx;\n"
        "test %%ecx, %%ecx;\n"
        "jz end;\n"
        "loop: imull %%ecx, %%eax; decl %%ecx; jnz loop;\n"
        "end: movl %%eax, %0;\n"
        : "=r"(res) : "r"(n) : "%eax", "%ecx"
    );

    printf("Factorielle de %u est %u", n, res);

    return 0;
}