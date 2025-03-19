#include <unistd.h>
#include <cstdio>

#include "lib/helpers/keyboard.h"

[[noreturn]] int main() {

    int ch;

    while (true) {
        ch = getchar();
        printf("The entered character is : %c\n", ch);
    }
}

