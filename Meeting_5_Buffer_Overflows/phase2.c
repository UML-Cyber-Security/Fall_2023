#include <stdio.h>

void vulnerable_function() {
    char buffer[128];
    printf("Enter some text: ");
    scanf("%s", buffer);
    printf("You entered: %s\n", buffer);
}

int main() {
    vulnerable_function();
    return 0;
}
