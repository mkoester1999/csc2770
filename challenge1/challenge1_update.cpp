#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void decimalToBinary(int decimal);
void decimalToHex(int decimal);
void binaryToDecimal(char *binary);
void binaryToHex(char *binary);
void hexToDecimal(char *hex);
void hexToBinary(char *hex);

// Function to print the hexadecimal number in reverse order
void printHexInReverse(char hex[], int length) {
    printf("Hexadecimal: ");
    for (int j = length - 1; j >= 0; j--) {
        printf("%c", hex[j]);
    }
    printf("\n");
}

// Function to convert decimal to binary (placeholder)
void decimalToBinary(int decimal) {
    printf("Converting decimal %d to binary...\n", decimal);
    // Conversion logic will go here
    //create 33-bit char array to represent the binary number. int is 32 bits and we will need an extra bit for terminating character
    char *binary = new char[33];

    if (decimal == 0) {
        binary[0] = '0';
    }
    //handle positive integers
    else if (decimal > 0) 
    {
        //for loop to do integer division and get moduli. Starting at position 31 and working backwards
        for(int i = 31; i>=0; i--) {
            //set the current position to the remainder of the decimal divided by 2. Use +'0' to convert to char
            binary[i] = decimal % 2 + '0';
            decimal = decimal / 2;
        }
        //handle overflow
        if (binary[0] == 1)
        {
            //print overflow and exit program with error code 1
            printf("Overflow!\n");
            exit(1);
        }
    }
    //handle negative integers
    else
    {
        //multiply decimal by -1 to get the absolute value
         decimal = decimal * -1;
         
        //for loop to do integer division and get 1's complement. Starting at position 31 and working backwards
        for(int i = 31; i>=0; i--) {
           //handle 2's complement by flipping all the bits 
            int tempInt = decimal % 2;
            if(tempInt == 0) {
                binary[i] = '1';
            } else {
                binary[i] = '0';
            }
            decimal = decimal / 2;
        }
        
        //now find Two's complement
        for(int i = 31; i>=0; i--)
        {
            //if first(and consecutive i-1) bit is 1, flip it
            if(binary[i] == '1') 
            {
                binary[i] = '0';
            } else {
                //if bit is 0, flip it and break
                binary[i] = '1';
                break;
            }
        }
        //handle overflow
        if (binary[0] == '0')
        {
            //print overflow and exit program with error code 1
            printf("Overflow!\n");
            exit(1);
        }
    }
    //set terminating character
    binary[32] = '\0';


    printf("Binary: %s\n", binary);
    delete[] binary;
}


// Function to convert decimal to hexadecimal (placeholder)
void decimalToHex(int decimal) {
    printf("Converting decimal %d to hexadecimal...\n", decimal);
    // Conversion logic will go here
    //create hex cstring to store hex digits corresponding to their value in decimal
    const char hexChars[] = "0123456789ABCDEF";
    //create new char array to store 32-bit hex + terminating character
    char *hex = new char[9];
    int i = 0;
    if(decimal == 0)
    {
        hex[0] = '0';
        i = 1;
    }
    //handle positive integers
    while (decimal > 0)
    {
        //set hex[i] to the corresponding hex character based on the remainder of the decimal divided by 16
        hex[i] = hexChars[decimal % 16];
        decimal /= 16;
        i++;
    }
    //handle negative integers
    if(decimal <0)
    {
        //convert decimal to binary using 2's complement
        //convert back to hexadecimal
    }
    //set terminating character
    hex[i+1] = '\0';
    // Call the function to print the hexadecimal number in reverse order
    printHexInReverse(hex, i);
    delete[] hex;
}

// Function to convert binary to decimal (placeholder)
void binaryToDecimal(char *binary) {
    printf("Converting binary %s to decimal...\n", binary);
    // Conversion logic will go here
    int decimal = 0;
    //get length of binary string
    int length = 0;
    while (binary[length] != '\0')
    {
        length++;
    }

    //handle bit to decimal conversion skipping the sign bit
    for (int i = 1; i < length; ++i)
    {
        decimal = decimal * 2 + (binary[i] - '0');
    }
    
   //if sign bit is 1, subtract 2^length-1. Need -1 to ignore the terminating character 
    if (binary[0] == '1')
    {
        decimal -= pow(2, length-1);
    }

    printf("Decimal: %d\n", decimal);

}

// Function to convert binary to hexadecimal (placeholder)
void binaryToHex(char *binary) {
    printf("Converting binary %s to hexadecimal...\n", binary);
    // Conversion logic will go here
    //create hex cstring to store 32-bit hex + terminating character
    char *hex;
    int i;
    // Call the function to print the hexadecimal number in reverse order
    printHexInReverse(hex, i);
}

// Function to convert hexadecimal to decimal (placeholder)
void hexToDecimal(char *hex) {
    printf("Converting hexadecimal %s to decimal...\n", hex);
    // Conversion logic will go here
    int decimal;
    printf("Decimal: %d\n", decimal);

}

// Function to convert hexadecimal to binary (placeholder)
void hexToBinary(char *hex) {
    printf("Converting hexadecimal %s to binary...\n", hex);
    // Conversion logic will go here
    char binary[33];
    printf("Binary: %s\n", binary);

}



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

    // Extract the flag and value from arguments
    // Check which flag was provided and call the appropriate function
    
    // Extract the flag and value from arguments
    //grab just the letter without the hyphen
    char flag = argv[1][1];
    //set value to the third argument
    char *value = argv[2];
    printf("Value: %s\n", value);
    // Check which flag was provided and call the appropriate function
    switch(flag)
    {
        case 'd':
        {
            int decimal = atoi(value); //atoi can't handle overflows, so may need to think of a different strategy. Maybe use strtol instead.
            decimalToBinary(decimal);
            decimalToHex(decimal);
        }
            break;

        case 'b':

            binaryToDecimal(value);
            binaryToHex(value);
            break;

        case 'h':
            hexToDecimal(value);
            hexToBinary(value);
            break;

        default:
            printf("Invalid flag: %c\n", flag);

    }

    return 0;
}

