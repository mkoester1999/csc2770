#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void decimalToBinary(int decimal);
void decimalToHex(int decimal);
void binaryToDecimal(char *binary);
void hexToDecimal(char *hex);

// Main function to handle inputs and trigger conversions
int main(int argc, char *argv[]) {
    // Ensure correct number of arguments are provided
    if (argc != 3) {
        printf("Usage: %s -[d|b|h] [number]\n", argv[0]);
        printf("Options:\n");
        printf("-d [decimal]     Convert decimal to binary and hexadecimal\n");
        printf("-b [binary]      Convert binary to decimal and hexadecimal\n");
        printf("-h [hexadecimal] Convert hexadecimal to decimal and binary\n");
        return 1;
    }

    char *flag = argv[1];
    //print out flag
    printf("Flag: %s", flag);

}