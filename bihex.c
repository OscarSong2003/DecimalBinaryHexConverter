/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   bihex.c 
 
 * Author: Oscar Song 
 
 * Purpose: To create a program that will convert between Binary, Decimal, and 
 *          hexadecimal. The program will first ask the user to enter any of the
 *          three type of value. Then, the user will be asked to indicate the 
 *          number system that they wish to convert to. The program will then 
 *          output the correct conversion to the user in the indicated form. The 
 *          program will detect any invalid input throughout the process and 
 *          prompt the user to re-enter. The program will continue to loop until
 *          the users input evaluates to 0. 
 
 * Status: DONE

 * Created on February 18, 2020, 12:56 PM
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */

// Code to use the power function 

int power( int base, int exponent ) {
   int answer = 1;
   int index;
   for ( index = 0; index < exponent; index++ ) {
       answer *= base;  // same as answer = answer * base
   }
   return answer;
}


int main (int argc, char** argv) {
    
    // Variables
    
    const int characterConstrain = 32; 
    
    char usersValue[characterConstrain + 1];
    
    int valuePosition = 0;
    
    int binary = 0;
    
    int hex = 0;
    
    int decimal = 0;
    
    int intermediary = 0;
   
    int valueLength = 0;
   
    char convert = 'A';
   
    int subtractNum = 0;
    
    int exponent = 0;
    
    int digitNum = 0;
    
    int digit = 0;
    
    char binaryValue [100];
    
    char hexValue[100];
    
    int divisor = 0;
    
    int quit = 0;
    
    int maybeHex = 0;
    
    // Welcome
    
    printf("Welcome to the world's worst BiHex converter!"); 
   
    // Get Input 
    
    // loop through the conversion process until user's input evaluates to zero which 
    // makes quit true.
    
    while (quit != 1){
        
        // reset all variables to their initial format so the conversion will be 
        // correct no matter how many times the user chooses to convert. 
        
        quit = 0;
        valuePosition = 0;
        intermediary = 0;
        binary = 0;
        hex = 0;
        decimal = 0;
        valueLength = 0;
        convert = 'A';
        subtractNum = 0;
        exponent = 0;
        digitNum = 0;
        digit = 0;
        divisor = 0;

        // reset all arrays by filling all elements of the array with null characters.
        // this is important as the array was previously filled with the previous
        // characters so if the user chooses to convert again the arrays will contain
        // characters from the previous time the user converts. Therefore by resetting
        // the array this would ensure that every time the program loops all contents
        // will be removed. 
        
        // reset the array containing the value the user enters to convert
        
        while ((usersValue[valuePosition] != 0) && (valuePosition < characterConstrain + 1)){
            usersValue[valuePosition] = 0;
            valuePosition++;
        }
        
        // reset the value position again to 0
        
        valuePosition = 0;
        
        // reset the array containing the binary value that the program will 
        // output to the user if the user choose to convert decimal/hexadecimal 
        // to binary
       
        while ((binaryValue[digit] != 0) && (digit < 100)){
            binaryValue[digit] = 0;
            digit++;
        }
        
        // reset the digit 
        
        digit = 0;
        
        // reset the array containing the hex value that the program will output
        // to the user if the user choose to convert binary/decimal to hex. 
        
        while ((hexValue[digit] != 0) && (digit < 100)){
            hexValue[digit] = 0;
            digit++;
        }
        
        // reset digit again
        
        digit = 0;
        
        // Ask user to input a value that they wish to convert 
        
        printf("\n\nPlease enter a binary, hexadecimal, or decimal value: ");
        scanf("%s", usersValue);
        fgetc(stdin);

        // Check for validity and checking if the user entered a hex with 0x in front

        // loop through each character of the array containing the users input
        
        while ((usersValue[valuePosition] != 0) && (valuePosition < characterConstrain + 1)){
            
            // check if the character is valid.
            
            if (((usersValue[valuePosition] >= 48) && (usersValue[valuePosition] <= 57)) || ((usersValue[valuePosition] >= 65) && (usersValue[valuePosition] <= 70))
            || ((usersValue[valuePosition] >= 97) && (usersValue[valuePosition] <= 102))){
                valuePosition++;
            }
            
            // the character is not valid 
            else{
                
                // check if the position is 1 (at the second character) ---> the user might have inputted 0x
             
                if (valuePosition == 1){
                    
                    // user entered 0x at beginning
                    if ((usersValue[0] == 48) && ((usersValue[1] == 88) || (usersValue[1] == 120))){
                        // may be hex
                        hex = 1;
                        
                        // increment value position
                        valuePosition++;
                        
                        // the input is still considered valid so we continue to loop to check the remaining 
                        // characters in the array.
                        continue;
                    }
                }
                
                // if any of the below conditions are met, the users input is invalid: 
                //  - the user entered an invalid character and the value position is not 1
                //  - the user entered an invalid character; the value position is 1; but the user did not input 0x 
                //    as the first two characters.
                //  - the user entered the 0x, but also entered another invalid input somewhere after
                //    the 0x.
                
                printf("\nYour input of %s is invalid. Please enter a binary, hexadecimal,", usersValue);
                printf("\nor decimal value: ");
                scanf("%s", usersValue);
                fgetc(stdin);
                
                // reset value position to check again
                valuePosition = 0;
                
                // since input is invalid, even if the user may have inputted 0x in front 
                // the value is not hex ----> reset hex to 0
                hex = 0;
                continue;
            }      
        }
        
        // Check for which type of number is the user entering

        // Reset Value Position
        
        valuePosition = 0;
        
        // check for hex without the 0x. Loop through the array and as soon as the program
        // spot a character not between 0-9 the value MUST be hex as it is already deemed
        // valid.
        
        while ((usersValue[valuePosition] != 0) && (valuePosition < characterConstrain + 1)){
            if (usersValue[valuePosition] > 57){        
                hex = 1;
                break;    
            }
            valuePosition++;
        }
     
        // Not hexadecimal ----> check to see if the value is decimal/binary

        if (hex == 0){
            
            // reset valuePosition;
            valuePosition = 0;
            
            // check decimal ---> as long as a program spot a value greater than 1, the value MUST 
            // be decimal.

            while ((usersValue[valuePosition] != 0) && (valuePosition < characterConstrain + 1)){
                if (usersValue[valuePosition] > 49){
                    decimal = 1;
                    break;
                }
                valuePosition++;           
            }       
            // if not decimal ----> binary
            if (decimal == 0){
                binary = 1;
            }
        }
        
        // Determine Length of Users Input 

        valuePosition = 0;
        while ((usersValue[valuePosition] != 0) && (valuePosition < characterConstrain + 1)){
            valueLength++;
            valuePosition++;
        }    

        // converting to intermediary
        
        // If binary ———> Use binary conversion to decimal (intermediary)
   
        if (binary == 1){  

            // reset value position

            valuePosition = 0; 

            // going from the right to the left of the array

            while ((usersValue[valuePosition] != 0) && (valuePosition < valueLength)){

                // look for 1s 
                if (usersValue[valueLength - valuePosition - 1] == 49){

                    // convert to decimal by using base 2 to exponent
                    intermediary = intermediary + power(2, valuePosition);
                }
                
                // increment value position
                valuePosition ++;                                  
            }      
            
        }

        // not binary 
        else{
            // convert decimal to decimal  

            if (decimal == 1){

                // Reset Value Position
                valuePosition = 0;

                while ((usersValue[valuePosition] != 0) && (valuePosition < valueLength)){

                    // convert to decimal (subtract 48 to convert to decimal as we are dealing 
                    // with ASCII values.

                    intermediary += (usersValue[valueLength - valuePosition - 1] - 48) * power(10, valuePosition);

                    valuePosition ++;

                }
            }
            else{

                if (hex == 1){       

                    // Reset value position

                    valuePosition = 0;

                    while ((usersValue[valuePosition] != 0) && (valuePosition < valueLength) && (usersValue[valueLength - valuePosition - 1] != 88) && (usersValue[valueLength - valuePosition - 1] != 120)){                
                        
                        // if digit is between 0 and 9

                        if ((usersValue[valueLength - valuePosition - 1] >= 48) && (usersValue[valueLength - valuePosition - 1] <= 57)){
                            intermediary += (usersValue[valueLength - valuePosition - 1] - 48) * power(16, valuePosition);
                        }

                        // if digit is between A and F
                        else{
                            if ((usersValue[valueLength - valuePosition - 1] >= 65) && (usersValue[valueLength - valuePosition - 1] <= 70)){
                                intermediary += (usersValue[valueLength - valuePosition - 1] - 55) * power(16, valuePosition);

                            }
                            // if digit is between a and f
                            else{
                                if ((usersValue[valueLength - valuePosition - 1] >= 97) && (usersValue[valueLength - valuePosition - 1] <= 102)){
                                   intermediary += (usersValue[valueLength - valuePosition - 1] - 87) * power(16, valuePosition); 
                                }
                            }
                        }           
                        valuePosition ++; 
                    }   
                }
            }
        }
        
        // user's input evaluates to 0 ----> quit the loop
        
        if (intermediary == 0){
            quit = 1;
        }
        
        // user's input does NOT evaluate to 0 ----> ask the user to indicate the 
        // type of conversion
       
        else{
            // ask user what they want to convert to
            printf("\nPlease indicate whether you want to convert to binary [b/B], decimal [d/D],");
            printf("\nor hexadecimal [h/H]: ");
            scanf("%c", &convert);
            fgetc(stdin);
            
            // check for invalid input and if invalid prompt the user to try again
            
            while ((convert != 'b') && (convert != 'B') && (convert != 'd') && (convert != 'D') && (convert != 'h') && (convert != 'H')){
                printf("\nYour input of %c is invalid, please indicate whether you want to convert", convert);
                printf("\nto binary [b/B], decimal [d/D], or hexadecimal [h/H]: ");
                scanf("%c", &convert);
                fgetc(stdin);
                
            }

            // if the user wants to convert to decimal
            if ((convert == 'd') || (convert == 'D')) {
                printf("\n'%s' in decimal is: %d", usersValue, intermediary);
            }

            // if the user wants to convert to binary
            else{
                // user inputed binary
                if ((convert == 'b') ||(convert == 'B')){
                    if (binary == 1){
                        printf("\n'%s' in binary is: %s", usersValue, usersValue);
                    }
                    
                    
                    else{
                        // user inputed hex/decimal

                        // find the starting number to subtract by

                        while (subtractNum <= intermediary){
                            subtractNum = subtractNum + power(2,exponent-1);
                            exponent++; 
                        }
                        subtractNum = subtractNum / 2;

                        // find the total number of binary digit
                        digitNum = exponent - 1;                             

                        while (digit < digitNum){

                            if (intermediary >= subtractNum){
                                intermediary = intermediary - subtractNum;
                                binaryValue[digit] = 49;

                            }
                            else{
                                binaryValue[digit] = 48;
                            }
                            subtractNum = subtractNum / 2;        
                            digit++; 

                        }
                        // reset digit
                        digit = 0;

                        // print the binary value character by character 

                        printf("\n'%s' in binary is: ", usersValue);        
                        while ((binaryValue[digit] != 0) && (digit < digitNum)){
                            printf("%c", binaryValue[digit]);
                            digit++;
                        }
                    }    
                }
                else{
                    // hex
                    if (hex == 1){
                        printf("\n'%s' in hexadecimal is: %s", usersValue, usersValue);
                    }
                    else{

                        // determine the starting number to divide by 

                        while (divisor <= intermediary){
                            divisor = power(16, exponent);                  
                            exponent++;  

                        }

                        // finding the first (largest) divisor

                        divisor = divisor / 16;

                        // find the total number of hexadecimal digit

                        digitNum = exponent - 1;

                        // find the value of each character of the the hexadecimal. 

                        while (digit < digitNum){
                            
                            // I need to determine whether the digit will be between
                            // 0-9, which will be denoted by numbers, or between 10-15
                            // which will be denoted with letters. 
                        
                            // digit is larger than or equal to 10 ---> add 55 
                            // due to ascii values. 
                            if ((intermediary/divisor) >= 10){
                                hexValue[digit] = (intermediary/divisor) + 55;
                                intermediary = intermediary - (divisor * (hexValue[digit] - 55));
                            }
                            
                            // digit is between 0 and 9 ---> add 48 due to ascii values.
                            else{
                                hexValue[digit] = (intermediary/divisor) + 48;

                                intermediary = intermediary - (divisor * (hexValue[digit] - 48));
                            }
                            divisor = divisor / 16;
                            digit++;
                        }
                        
                        // reset digit

                        digit = 0;
                        
                        // print out each character by looping through the array 
                        // and printing them character by character.

                        printf("\n'%s' in hex is: 0x", usersValue);

                        while ((hexValue[digit] != 0) && (digit < digitNum)){
                            printf("%c", hexValue[digit]);
                            digit++;
                        }
                    }
                }
            }
        }
    }
    
    // End of program -----> the users input evaluates to 0
    
    printf("\nThank you for using the worst Bihex converter!");
   
    return (EXIT_SUCCESS);
}


