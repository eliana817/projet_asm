#include <stdio.h>
//TO REDO WITH WORKING ASSEMBLY
int main(){

    unsigned int n;
    unsigned int fact = 1; // On stock la factorielle sur 64 bits

    printf("Entrez un nombre (en-dessous de 12): ");
    scanf("%u", &n);

    if (n >= 12) {
        printf("Le nombre doit etre plus petit que 12.\n");
        return 1;
    }

    asm(
        ".intel_syntax noprefix;"    // Déclare la syntaxe intel
        "mov ecx, %1;"               // Charger n dans ecx (compteur de boucle)
        "mov eax, 1;"                // initialiser rax à 1

        "factorial_loop:"
        "cmp ecx, 1;"                // Vérifier si on arrive à la fin de la factorielle
        "jle factorial_done;"        // Imprimer le résultat si à la fin
        "mul ecx;"                   // rax = rax * rcx (multiplication)
        "dec ecx;"                   // décrémenter ecx
        "jmp factorial_loop;"        // Continuer jusqu'à la fin

        "factorial_done:"
        "mov %0, eax;"                // stocker le résultat dans fact
        ".att_syntax prefix;"         // repasser en AT&T pour gcc

        : "=r"(fact)                  // sortie = fact
        : "r"(n)                      // input = n
        : "eax", "ecx"                // rax et rcx sont modifiés au cours du programme
    );

    printf("Factorielle de %u est %u", n, fact);

    return 0;

}