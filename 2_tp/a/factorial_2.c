#include <stdio.h>

unsigned int factorial(unsigned int n) {
    unsigned int res = 1;
    for (unsigned int i = 2; i <= n; i++) res *= i;
    return res;
}

int main(){
    unsigned int n;
    printf("Entrez un nombre (en-dessous de 12): ");
    scanf("%u", &n);

    if (n >= 12) {
        printf("Le nombre doit etre plus petit que 12.\n");
        return 1;
    }

    printf("La factorielle de %u est %u.\n", n, factorial(n));
    return 0;
}