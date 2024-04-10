#include <stdio.h>
#include <stdint.h>
#include "mm_malloc.h"



#define INFO_LENGTH 483

void set_bit(uint32_t *num, int position, uint8_t value) {
    if ((value > 1) && (value < 0)) {
        printf("set_bit(%d, %d, %d): error value", *num, position, value);
        return;
    }

    // Очищаем бит на позиции position
    *num &= ~(1 << position);
    // Устанавливаем бит на позиции position в соответствии с переданным значением
    *num |= (value << position);
}

uint8_t get_bit(uint8_t num, int position) {
    return (num >> position) & 1;
}

void print_reg_8(uint8_t reg) {
    for (int i = 8; i >= 0; i--) {
        printf("%d", (reg >> i) & 1);
    }
    printf("\n");
}

void print_reg_32(uint32_t reg) {
    for (int i = 32; i >= 0; i--) {
        printf("%d", (reg >> i) & 1);
    }
    printf("\n");
}

void print_array(uint8_t* reg) {
    for (int i = 8; i >= 0; i--) {
        printf("%d", reg[i]);
    }
    printf("\n");
}

// Программа для примера с семинара
// g(x) = x^4 + x^3 + x^2 + 1
// uint8_t run_alg2(uint8_t *u) {
//     uint8_t reg = 0;
//     for (int i = 0; i < 3; i++) {
//         printf("i = %d\n", i);
//         printf("u[i] = %d\n", get_bit(*u, i));
//         uint8_t multiplier = get_bit(*u, i) ^ get_bit(reg, 0);

//         set_bit(&reg, 0, get_bit(reg, 1));

//         set_bit(&reg, 1, multiplier ^ get_bit(reg, 2));

//         set_bit(&reg, 2, multiplier ^ get_bit(reg, 3));

//         set_bit(&reg, 3, multiplier);

//         print_reg(reg);
//     }
//     return reg;
// }

// g(x) = x^{27} + x^{26} + x^{24} + x^{22} + x^{21} + x^{16} 
// + x^{13} + x^{11} + x^9 +x^8 + x^6 + x^5 + x^4 + x^3 + 1


// Деление многочленов через регистры
// n = 511, r = 28, k = 483; 
uint8_t run_alg(uint8_t *u) {
    uint32_t reg = 0;
    for (int i = 0; i < 28; i ++) {
        uint8_t multiplier = get_bit(*u, i) ^ get_bit(reg, 0);
        
        set_bit(&reg, 0, get_bit(reg, 1));
        set_bit(&reg, 1, get_bit(reg, 2));
        set_bit(&reg, 2, get_bit(reg, 3));
        set_bit(&reg, 3, multiplier ^ get_bit(reg, 4));
        set_bit(&reg, 4, multiplier ^ get_bit(reg, 5));
        set_bit(&reg, 5, multiplier ^ get_bit(reg, 6));
        set_bit(&reg, 6, multiplier ^ get_bit(reg, 7));
        set_bit(&reg, 7, get_bit(reg, 8));
        set_bit(&reg, 8, multiplier ^ get_bit(reg, 9));
        set_bit(&reg, 9, multiplier ^ get_bit(reg, 10));
        set_bit(&reg, 10, get_bit(reg, 11));
        set_bit(&reg, 11, multiplier ^ get_bit(reg, 12));
        set_bit(&reg, 12, get_bit(reg, 13));
        set_bit(&reg, 13, multiplier ^ get_bit(reg, 14));
        set_bit(&reg, 14, get_bit(reg, 15));
        set_bit(&reg, 15, get_bit(reg, 16));
        set_bit(&reg, 16, multiplier ^ get_bit(reg, 17));
        set_bit(&reg, 17, get_bit(reg, 18));
        set_bit(&reg, 18, get_bit(reg, 19));
        set_bit(&reg, 19, get_bit(reg, 20));
        set_bit(&reg, 20, get_bit(reg, 21));
        set_bit(&reg, 21, multiplier ^ get_bit(reg, 22));
        set_bit(&reg, 22, multiplier ^ get_bit(reg, 23));
        set_bit(&reg, 23, get_bit(reg, 24));
        set_bit(&reg, 24, multiplier ^ get_bit(reg, 25));
        set_bit(&reg, 25, get_bit(reg, 26));
        set_bit(&reg, 26, multiplier ^ get_bit(reg, 27));
        set_bit(&reg, 27, multiplier ^ get_bit(reg, 28));
        printf("i = %d", i);
        print_reg_32(reg);
    }
    return reg;
}

// Программа для примера с семинара
// g(x) = x^4 + x^3 + x^2 + 1
// uint8_t* run_sem_exemple(uint8_t *u) {
//     uint8_t *reg = (uint8_t*)(malloc(sizeof(uint8_t) * 4));
//     for (int i = 0; i < 3; i++) {
//         printf("i = %d\n", i);
//         printf("u[i] = %d\n", u[i]);
//         uint8_t multiplier = u[i] ^ reg[0];

//         reg[0] = reg[1];
//         printf("reg[0]: %d\n", reg[0]);

//         reg[1] = multiplier ^ reg[2];
//         printf("reg[1]: %d\n", reg[1]);

//         reg[2] = multiplier ^ reg[3];
//         printf("reg[2]: %d\n", reg[2]);

//         reg[3] = multiplier;
//         printf("reg[3]: %d\n", reg[3]);

//         print_array(reg);
//     }
//     return reg;
// }

uint32_t read_input_file(char* file_name) {
    uint32_t u;
    FILE *input_file = fopen(file_name, "r");
    if (input_file == NULL) {
        printf("Ошибка открытия входного файла.\n");
        return 1;
    }

    for (int i = 0; i < INFO_LENGTH; i++) {
        char c = fgetc(input_file);
        if (c == EOF || (c != '0' && c != '1')) {
            printf("Ошибка чтения из файла.\n");
            fclose(input_file);
        }
        uint8_t bit = c - '0';
        set_bit(&u, i, bit); // Преобразование символа в бит ('0' -> 0, '1' -> 1)
    }

    fclose(input_file);

    return u;
    
}

void print_output(uint32_t u, char* file_name) {
    FILE *output_file = fopen(file_name, "w");
    if (output_file == NULL) {
        printf("Ошибка открытия входного файла.\n");
    }

    for (int i = 0; i < INFO_LENGTH; i++) {
        fprintf(output_file, "%u ", get_bit(u, i)); // Выводим биты как беззнаковые целые числа
    }

    fclose(output_file);
}

int main() {

    // Xor where x^i not null
    //g = 0b00001101;

    //uint8_t u = 0b101;
    //print_reg(run_alg2(&u));

    uint32_t u = read_input_file("input_bits.txt");
    print_reg_32(u);
    print_output(u, "encoded_bits.txt");

    return 0;
}