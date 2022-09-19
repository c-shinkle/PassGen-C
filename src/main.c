#include <stdio.h>

char* LETTERS =
        "0123456789abcdefgh'i'"
        "jklmnopqrstuvwxyzA'B'"
        "CDEFGHIJKLMNOPQRST'U'"
        "VWXYZ!\"#$%&'()*+,-'.'"
        "/:;<=>?@[\\]^_`{|}~";

int main() {
    printf("%s\n", LETTERS);

    return 0;
}