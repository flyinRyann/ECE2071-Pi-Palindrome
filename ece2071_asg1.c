#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
Written By: Khanh Gia Nguyen
Student ID: 32498349, Monash University
Last Modified: Thursday, 24th March 2022
Description:
This program takes a given text file of pi digits and explores the patterns of palindrome 
within the file, and then prints out a summary of what was found in the terminal.
*/ 

// Compile with:
// gcc -std=c17 -pedantic -Werror ece2071_asg1.c -o ece2071_asg1 -lm

// Function Prototype:
bool isPalindrome(int array[], size_t size);
int median(int input[], int count3);
int cmpfunc (const void * a, const void * b);

int main(void)
{
    // Array Definition:
    int arrayLength = 50000002;
    int *array = (int*) malloc(arrayLength * sizeof(int));
    unsigned int count = 0;
    int c;
    int palindromeLength = 2;

    // Print Headings:
    printf("%s%13s%18s\n", "Palindrome", "Number of", "Median Digit");
    printf("%s%19s%12s\n", "Length", "Palindromes", "Distance");
    printf("%s%15s%16s\n","----------", "-----------", "------------");
   

    // Opening the file.
    FILE *file = fopen("pi_50m.txt", "r");
    if (file == 0)
    {
        printf("I can't open the file for reading.\n");
        return -1;
    }

    // Iterating through the variables in the file and storing it into array usign malloc.
    while ((c = fgetc(file)) != EOF)
    {
        array[count] = c;
        count++;
    }

    // Main Function:

    // Variables:
    int palinCount2 = 1; // Counter for amount of palindromes in each iteration.
    int distanceActive = 0; // Checker to activate for when to start counting palindrome distance.
    int start = 0; // Variable to determine digit distance.
    int *arrayMedian = (int*) malloc(arrayLength * sizeof(int)); // Array using malloc to store digit distance.
    int count2 = 0; // Counter to count the length of the digit distance array.
    bool conState = false; // Another variable to determine digit distance.

    // Iterate while the specified palindrome length still returns a palindrome.
    while(palinCount2 > 0)
    {
        palinCount2 = 0;
        // Iterates through the store element in the pi text file.
        for (size_t i = 2; i < arrayLength; i++)
        {
            int arrayChecker[palindromeLength];
            
            // Create a small array to check palindrome of certain length.
            for (size_t j = 0; j < palindromeLength; j++)
            {
                arrayChecker[j] = array[i+j];
            }

            // Check if the array made is a palindrome.
            if (isPalindrome(arrayChecker,palindromeLength) == true)
            {
                // Finding distance between one palindrome and next.
                distanceActive++;
                if (distanceActive == 1 && conState == false)
                {
                    start = i;
                }
                else if (distanceActive == 2)
                {
                    arrayMedian[count2] = i - start - 1;
                    count2++;
                    distanceActive = 1;
                    conState = true;
                    start = i;
                }
                palinCount2++;
            }
        }
        distanceActive = 0;
        conState = false;

        // Prints the last palindrome length that doesn't have a palidrome.
        if (palinCount2 == 0)
        {
            printf("%10d", palindromeLength);
            printf("%15d", palinCount2);
            printf("%16d\n", 0);
            break;
        }

        // Sorting the array of digit distance and determining the median value.
        qsort(arrayMedian, count2, sizeof(int), cmpfunc);
        int midVal = median(arrayMedian, count2);
        
        // Prints the final specify details of each palindrome length.
        printf("%10d", palindromeLength);
        printf("%15d", palinCount2);
        printf("%16d\n", midVal);
        count2 = 0;
        midVal = 0;
        palindromeLength++;
    }

    // Closing the file.
    printf("The file is %d characters long.\n", count);
    fclose(file);


    return 0;
}

// Compare function for the inbuilt qsort() method.
int cmpfunc (const void * a, const void * b) {
        return ( *(const int*)a - *(const int*)b );
    }

// Function that returns the median value of an array given the array and its size.
int median(int input[], int count3)
{
    if (count3 % 2 != 0)
    {
        return input[(count3/2)];
    }
    else
    {
        return input[count3/2-1];
    }
}

// Function that takes in an array and its size, and then returns true if it is palindrome and false otherwise.
bool isPalindrome(int array[], size_t size)
{
    unsigned int c = 0;
    unsigned int i;
    for(i = 0; i < size/2; i++)
    {
        if (array[i] == array[size-i-1])
        {
            c++;
        }
    }
    if(c == i)
    {
        return true;
    }
    else
    {
        return false;
    }
}

