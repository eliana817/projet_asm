#include <stdio.h>
#include <string.h>

void reverse(char *str){
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

void rot13(char *str){
    for (int i = 0; str[i] != '\0'; i++){
        if ((str[i] >= 'A' && str[i] <= 'M') || (str[i] >= 'a' && str[i] <= 'm')){
            str[i] += 13;
        } else if ((str[i] >= 'N' && str[i] <= 'Z') || (str[i] >= 'n' && str[i] <= 'z')) {
            str[i] -= 13;
        }
    }
}

void read_and_process(){
    char input[100];
    fgets(input, sizeof(input), stdin);
    reverse(input);
    printf("Reversed: %s \n", input);
    rot13(input);
    printf("ROT13: %s", input);
}

int main() {
    read_and_process();
    return 0;
}