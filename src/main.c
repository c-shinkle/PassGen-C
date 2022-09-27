#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <unistd.h>

char *LETTERS = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

int position(int val, const int *indices, int length) {
    for (int i = 0; i < length; i++) {
        if (indices[i] == val) {
            return i;
        }
    }
    return -1;
}

void insert(int *indices, int index, int element) {
    for (int i = 2; i >= index; i--) {
        indices[i+1] = indices[i];
    }
    indices[index] = element;
}

int *get_four_random_indices(int indices[4], int length) {
    for (int i = 0, j = length - 4; i < 4; i++, j++) {
        int val = ((int) random()) % (j + 1);
        int pos = position(val, indices, i + 1);
        if (pos == -1) {
            indices[i] = val;
        } else {
            insert(indices, pos, j);
        }
    }
    return indices;
}

char sample(int length, uint32_t offset) {
    return LETTERS[(random() % length) + offset];
}

char *pass_gen(char *password, int length) {
    assert(length >= 4);
    for (int i = 0; i < length; ++i) {
        password[i] = sample(94, 0);
    }
    password[length] = 0;
    int random_indices[4] = {-1, -1, -1, -1};
    get_four_random_indices(random_indices, length);
    password[random_indices[0]] = sample(10, 00);// NUMBERS
    password[random_indices[1]] = sample(26, 10);// LOWERS
    password[random_indices[2]] = sample(26, 36);// UPPERS
    password[random_indices[3]] = sample(32, 62);// SPECIALS
    return password;
}

uint32_t mix(uint32_t a, uint32_t b, uint32_t c) {
    a=a-b;  a=a-c;  a=a^(c >> 13);
    b=b-c;  b=b-a;  b=b^(a << 8);
    c=c-a;  c=c-b;  c=c^(b >> 13);
    a=a-b;  a=a-c;  a=a^(c >> 12);
    b=b-c;  b=b-a;  b=b^(a << 16);
    c=c-a;  c=c-b;  c=c^(b >> 5);
    a=a-b;  a=a-c;  a=a^(c >> 3);
    b=b-c;  b=b-a;  b=b^(a << 10);
    c=c-a;  c=c-b;  c=c^(b >> 15);
    return c;
}

int main() {
    uint32_t seed = mix(clock(), time(NULL), getpid());
//    printf("Seed: %ud\n", seed);
    srandom(seed);
    int i = 1000;
    int length = 1000;
    char password[length + 1];
    while (i--) {
        pass_gen(password, length);
        printf("%s\n", password);
    }
    return 0;
}
