#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void convert_numbers(char* input_filename, char* output_filename);
int determine_radix(char* number);
int get_decimal_number(char* number, int radix);

int main() {
    convert_numbers("input.txt", "output.txt");
    return 0;
}

void convert_numbers(char* input_filename, char* output_filename) {
    FILE* input_file = fopen(input_filename, "r");
    FILE* output_file = fopen(output_filename, "w");

    if (input_file == NULL || output_file == NULL) {
        printf("Error opening files!\n");
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), input_file)) {
        char* number = strtok(line, " \t\n");
        while (number != NULL) {
            int radix = determine_radix(number);
            if (radix != -1) {
                int decimal_number = get_decimal_number(number, radix);
                fprintf(output_file, "%s %d %d\n", number, radix, decimal_number);
             }

        number = strtok(NULL, " \t\n");
         }
    }

    fclose(input_file);
    fclose(output_file);

}

int determine_radix(char* number) {
    int base = 2;
    int i = 0;
    while (number[i] != '\0' ) {
        int digit=0;
        if (number[i] >= '0' && number[i] <= '9') {
            digit = number[i] - '0';
        } else {
            digit = number[i] - 'A' + 10;
        }

        if (digit >= (base-1)) {
            base = digit + 1;
        }
        i++;
    }
    if (get_decimal_number(number, base) != -1) {
            return base;
    }

   /* int length = strlen(number);

    for (int radix = 2; radix <= 36; radix++) {
        if (get_decimal_number(number, radix) != -1) {
            return radix;
        }
    }
*/
    return -1;
}

int get_decimal_number(char* number, int radix) {
    int decimal_number = 0;
    int power = 1;
    int length = strlen(number);

    for (int i = length - 1; i >= 0; i--) {
        int digit;
        if (number[i] >= '0' && number[i] <= '9') {
         digit = number[i] - '0';
         } else {
            digit = number[i] - 'A' + 10;
        }

        if (digit >= radix) {
            return -1;
         }

    decimal_number += digit * power;
    power *= radix;
}

return decimal_number;
}