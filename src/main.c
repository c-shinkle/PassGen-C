#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <unistd.h>
#include <limits.h>

char *LETTERS = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

void shuffle_u32(uint32_t array[], uint32_t length) {
    for (uint32_t i = 0; i < length; i++) {
        uint32_t swap_index = random() % length;

        uint32_t temp = array[i];
        array[i] = array[swap_index];
        array[swap_index] = temp;
    }
}

int position(uint32_t val, const int *indices, int length) {
    for (int i = 0; i < length; i++) {
        if (indices[i] == val) {
            return i;
        }
    }
    return -1;
}

void insert(int *indices, int amount, int index, int element) {
    for (int i = 2; i >= index; i--) {
        indices[i+1] = indices[i];
    }
    indices[index] = element;
}

int *get_four_random_indices(int *indices, long length, int amount) {
    for (uint32_t j = length - amount, i = 0; j < length; j++, i++) {
        long random_u32 = random() % length;
        assert(random_u32 < INT32_MAX);
        int pos = position(random_u32, indices, amount);
        if (pos == -1) {
            indices[i] = random_u32;
        } else {
            insert(indices, amount, pos, j);
        }
    }
    return indices;
}

char sample(long length, uint32_t offset) {
    return LETTERS[(random() % length) + offset];
}

char *pass_gen(uint32_t length) {
    assert(length >= 4);
    char *password = malloc((length + 1) * sizeof(char));
    for (uint32_t i = 0; i < length; ++i) {
        password[i] = sample(94, 0);
    }
    password[length] = 0;
    int random_indices[4] = {-1, -1, -1, -1};
    get_four_random_indices(random_indices, length, 4);
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
    uint32_t i = 1000;
    while (i--) {
        char *password = pass_gen(1000);
        printf("%s\n", password);
        free(password);
    }
    return 0;
}
