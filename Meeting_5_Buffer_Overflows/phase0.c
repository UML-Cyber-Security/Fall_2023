//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[], char* envp[]) {
    int x = 0;
    char strbuff2[5];
    char strbuff[10];

    printf("Enter a 10 char string: ");
    scanf("%s", strbuff);
    printf("You entered: %s\n", strbuff);
    printf("Copying over\n");
    strcpy(strbuff2, strbuff);

    if (x) {
        printf("X is non-zero");
    }
}