#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/syscall.h> // only for Linux

int main(){

    const char message[] = "Hello World!\n";

    // Method 1
    printf("%s", message);

    // Method 2
    write(1, message, strlen(message));

    // Method 3
    syscall(1, 1, message, strlen(message));

    return 0;
}

// To compile: gcc -o output_file file.c
// In our case: gcc -o Hello_World Hello_World.c