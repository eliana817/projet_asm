#include <stdio.h> //For printing

int main(){

    unsigned int n;           // store user input
    unsigned int fact = 1;  

    printf("Entrer un nombre (en-dessous de 12): ");
    scanf("%u", &n);

    if (n >= 12) {
        printf("Le nombre doit etre plus petit que 12.\n");
        return 1;  // stop program, although could also have done a while loop
    }

    for (unsigned int i = 1; i <= n; i++){
        fact *= i;
    }

    printf("Factorielle de %u est %u\n", n, fact);
    return 0;
}