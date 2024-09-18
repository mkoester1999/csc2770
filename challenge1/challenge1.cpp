/*Mitchell Koester
CSC2770 Challenge 1
Last modified: 9/15/2024
*/

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
int hexToDecimalHelper(char *hex);

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

//decimalToBinary function
//takes an integer and prints it in binary
//parameters: int decimal
//returns: void
void decimalToBinary(int decimal) {
    printf("Converting decimal %d to binary...\n", decimal);
    // Conversion logic will go here
    char *binary = decimalToBinaryHelper(decimal);
    printf("Binary: %s\n", binary);
    delete[] binary;
}

//decimalToHexHelper function
//takes an integer and converts it to a 32-bit hex string
//parameters: int decimal
//returns: char*
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

//decimalToHex function
//converts a decimal to hexadecimal
//parameters: int decimal
//returns: void
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

//binaryToDecimalHelper Function
//Takes binary cstring and converts into an integer
//parameters: char* binary
//returns: int
int binaryToDecimalHelper(char *binary)
{
    int decimal = 0;
    //get length of binary string
    int length = strlen(binary);

    //handle invalid sign
    if(binary[0] != '0' && binary[0] != '1')
    {
        printf("Invalid binary number %c!\n", binary[0]);
        exit(1);
    }

    //handle bit to decimal conversion skipping the sign bit
    for (int i = 1; i < length; ++i)
    {
        if(binary[i] < '0' || binary[i] > '1')
        {
            printf("Invalid binary number %c!\n", binary[i]);
            exit(1);
        }
        decimal = decimal * 2 + (binary[i] - '0');
    }
   // Calculate two's complement
   //if sign bit is 1, subtract length -1 shifted left from decimal 
    if (binary[0] == '1')
    {
        decimal = decimal - (1 << (length-1));
    }
    return decimal;
}
//binaryToDecimal Function
//Takes binary cstring and converts into an integer
//parameters: char* binary
//returns: void
void binaryToDecimal(char *binary) {
    printf("Converting binary %s to decimal...\n", binary);
    // Conversion logic will go here
    //handle overflow
    if(strlen(binary) > 32)
    {
        printf("Overflow!\n");
        return;
    }
    int decimal = binaryToDecimalHelper(binary);
    printf("Decimal: %d\n", decimal);

}

//binaryToHexHelper function
//takes a binary cstring and returns a converted hex cstring
//parameters: char* binary
//returns: char*
char *binaryToHexHelper(char *binary) 
{
    //convert binary to decimal first
    int decimal = binaryToDecimalHelper(binary);
    //call decimalToHex to convert decimal to hex
    char *hex = decimalToHexHelper(decimal);
    return hex;
}

//binaryToHex Function
//Takes binary cstring and converts into a hex cstring
//parameters: char* binary
//returns: void
void binaryToHex(char *binary) 
{
    printf("Converting binary %s to hexadecimal...\n", binary);
    // Conversion logic will go here
    //handle overflow
    if(strlen(binary) > 32)
    {
        printf("Overflow!\n");
        return;
    }
    //create hex cstring to store 32-bit hex + terminating character
    char *hex = binaryToHexHelper(binary);
    int i = strlen(hex);
    // Call the function to print the hexadecimal number in reverse order
    printHexInReverse(hex, i);
    delete[] hex;
}

//Helper function to convert hexadecimal char to integer
//takes a hex character and returns its integer equivalent. Returns -1 if invalid
//parameters: char hexChar
//returns: int
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
//hexToDecimalHelper function
//will take a hex cstring and convert into an integer
//parameters: char* hex
//returns: int
int hexToDecimalHelper(char *hex)
{
    int decimal = 0;
    //loop through hex string until reaching the terminating character
    while (*hex != '\0')
    {
        //convert hex char to integer
        int hexChar = hexChartoInt(*hex);
        if (hexChar == -1)
        {
            printf("Invalid hexadecimal input.\n");
            return -1;
        }
        //multiply decimal by 16
        decimal = decimal * 16 + hexChar;
        //increment hex
        hex++;
    }
    return decimal;
}
//hexToDecimal function
//Will take a hex cstring and convert into an integer
//parameters: char* hex
//returns: void
void hexToDecimal(char *hex) {
    printf("Converting hexadecimal %s to decimal...\n", hex);
    // Conversion logic will go here
    //check for invalid input or buffer overflow
    if ((hex == nullptr || strlen(hex) == 0) || (strlen(hex) > 8)) {
        printf("Invalid hexadecimal input.\n");
        return;
    }
    int decimal = hexToDecimalHelper(hex);
    printf("Decimal: %d\n", decimal);

}

//hexToBinary function
//Takes a hex cstring and converts into a binary cstring
//parameters: char* hex
//returns: void
void hexToBinary(char *hex) {
    printf("Converting hexadecimal %s to binary...\n", hex);
    // Conversion logic will go here
    //convert hex to decimal
    int decimal = hexToDecimalHelper(hex);
    //convert decimal to binary
    char *binary = decimalToBinaryHelper(decimal);
    printf("Binary: %s\n", binary);
    delete[] binary;

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

    //check if value is valid
    if(value == nullptr || *value == '\0')
    {
        print: printf("Invalid value\n");
        return 1;
    }
    // Check which flag was provided and call the appropriate function
    switch(flag)
    {
        case 'd':
        {
            int decimal = atoi(value); //atoi can't handle overflows, so may need to think of a different strategy. Maybe use strtol instead.

            //check for overflow, which will happen when value isn't -1, but decimal is
            if(decimal == -1 && (strcmp(value, "-1") != 0) || decimal == 0 && (strcmp(value, "0") != 0))
            {
                printf("Invalid input\n");
                return 1;
            }
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
    //delete[] value;
    return 0;
}

