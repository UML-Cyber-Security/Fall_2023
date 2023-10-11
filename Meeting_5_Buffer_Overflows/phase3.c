#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char global_flag = 0;

// Vulnerable function
void greeting(char *name) {
    char buffer[128];
    strncpy(buffer, name, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    printf(buffer); // Format string vulnerability
    printf("\n");
}

void set_flag() {
    global_flag = 1;
}

void win() {
    if(global_flag) {
        printf("You win! Nice ROP chain!\n");
        exit(0);
    } else {
        printf("Nice try! But the flag isn't set.\n");
        exit(1);
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <name>\n", argv[0]);
        return 1;
    }

    printf("Welcome ");
    greeting(argv[1]);
    printf("Hope you enjoyed the challenge!\n");

    return 0;
}
