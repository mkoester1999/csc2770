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
char *decimalToBinaryHelper(int decimal);
char *decimalToHexHelper(int decimal);
int binaryToDecimalHelper(char *binary);
char *binaryToHexHelper(char *binary);

// Function to print the hexadecimal number in reverse order
void printHexInReverse(char hex[], int length) {
    printf("Hexadecimal: ");
    for (int j = length - 1; j >= 0; j--) {
        printf("%c", hex[j]);
    }
    printf("\n");
}

//helper function for decimalToBinary
//converts a decimal to binary
//arguments: decimal to be converted
//returns: binary in char array
char *decimalToBinaryHelper(int decimal)
{

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
    return binary;
}

// Function to convert decimal to binary (placeholder)
void decimalToBinary(int decimal) {
    printf("Converting decimal %d to binary...\n", decimal);
    // Conversion logic will go here
    //create 33-bit char array to represent the binary number. int is 32 bits and we will need an extra bit for terminating character

    char *binary = decimalToBinaryHelper(decimal);
    printf("Binary: %s\n", binary);
    delete[] binary;
}

char *decimalToHexHelper(int decimal)
{
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
            decimal *=-1;
            //cast to uint to get absolute value
            uint absoluteDecimal = (uint)decimal;
            //get twos complement by inverting bits and adding one. Can do with ~operator
            uint inverted = ~absoluteDecimal;
            uint twosComplement = inverted +1;
            //convert to hex
            while (twosComplement > 0)
            {
                //set hex[i] to the corresponding hex character based on the remainder of the decimal divided by 16
                hex[i] = hexChars[twosComplement % 16];
                twosComplement /= 16;
                i++;
            }
        }
        //set terminating character
        hex[i+1] = '\0';
        return hex;

}

// Function to convert decimal to hexadecimal (placeholder)
void decimalToHex(int decimal) {
    printf("Converting decimal %d to hexadecimal...\n", decimal);
    // Conversion logic will go here
    //create hex cstring to store hex digits corresponding to their value in decimal
    char *hex = decimalToHexHelper(decimal);
    int i = strlen(hex);
        // Call the function to print the hexadecimal number in reverse order
    printHexInReverse(hex, i);
    delete[] hex;
}

// Helper function to convert binary to decimal
int binaryToDecimalHelper(char *binary)
{

    int decimal = 0;
    //get length of binary string
    int length = strlen(binary);

    //handle bit to decimal conversion skipping the sign bit
    for (int i = 1; i < length; ++i)
    {
        decimal = decimal * 2 + (binary[i] - '0');
    }
   // Calculate two's complement
   //if sign bit is 1, subtract 2^length-1. Need -1 to ignore the terminating character 
    if (binary[0] == '1')
    {
        decimal -= pow(2, length-1);
    }
    return decimal;
}
// Function to convert binary to decimal (placeholder)
void binaryToDecimal(char *binary) {
    printf("Converting binary %s to decimal...\n", binary);
    // Conversion logic will go here
    int decimal = binaryToDecimalHelper(binary);
    printf("Decimal: %d\n", decimal);

}


// Helper function to convert binary to hexadecimal
char *binaryToHexHelper(char *binary) 
{
    //convert binary to decimal first
    int decimal = binaryToDecimalHelper(binary);
    //call decimalToHex to convert decimal to hex
    char *hex = decimalToHexHelper(decimal);
    return hex;
}

// Function to convert binary to hexadecimal (placeholder)
void binaryToHex(char *binary) {
    printf("Converting binary %s to hexadecimal...\n", binary);
    // Conversion logic will go here
    //create hex cstring to store 32-bit hex + terminating character
    char *hex = binaryToHexHelper(binary);
    int i = strlen(hex);
    // Call the function to print the hexadecimal number in reverse order
    printHexInReverse(hex, i);
}

int hexChartoInt(char hexChar)
{
    //handle 0-9 hex characters (just decimal)
    if (hexChar >= '0' && hexChar <= '9')
    {
        return hexChar - '0';
    }
    //handle A-F hex characters
    else if (hexChar >= 'A' && hexChar <= 'F')
    {
        return hexChar - 'A' + 10;
    }
    //handle a-f hex characters
    else if (hexChar >='a' && hexChar <= 'f')
    {
        return hexChar - 'a' + 10;
    }
    //return -1 if there is an invalid character
    else
    {
        return -1;
    }
}
// Function to convert hexadecimal to decimal (placeholder)
void hexToDecimal(char *hex) {
    printf("Converting hexadecimal %s to decimal...\n", hex);
    // Conversion logic will go here
    if (hex == nullptr || strlen(hex) == 0) {
        printf("Invalid hexadecimal input.\n");
        return;
    }
    int decimal;
    int i = 0;
    //loop through hex string until reaching the terminating character
    while (hex[i] != '\0')
    {
        //convert hex char to integer
        int hexChar = hexChartoInt(*hex);
        //multiply decimal by 16
        decimal = decimal * 16 + hexChar;
        //increment hex
        i++;
    }
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

