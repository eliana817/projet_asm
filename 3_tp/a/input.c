#include <stdio.h>

int main(){

    char user_input[50];   // Read 50 characters max

    printf("Please enter whatever: \n");
    scanf("%s", &user_input);

    printf("Here is the value you entered: %s \n", user_input);

    return 0;

}