/**
 * @file char.c
 * @brief .c file containing every function relative to characters/string/scanf
 * @author Hicham Bettahar
 * @date December 24, 2023
 */
#include "header.h"

/**
 * @brief Clears the input buffer by consuming and discarding any remaining characters.
 *
 * The function reads characters from the standard input until a newline character or
 * the end of the file is encountered, effectively clearing the input buffer.
 */
void clearInputBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
} 

/**
 * @brief Gets the x-coordinate for firing a missile from the user.
 *
 * The function prompts the user to enter the x-coordinate for firing a missile,
 * validates the input, and returns the valid x-coordinate.
 *
 * @return The valid x-coordinate entered by the user.
 */
int getMissile_X(){
        int res,check;
        printf("A quelle abcisse souhaitez vous envoyé le missile ?\n");
        while( (check = scanf("%d",&res)) != 1 || res < 0 || res >= PLATE_SIZE){          //checking if the input is correct
                clearInputBuffer();
                printf("Valeur sasie incorrecte\n");
        }
        return res;
}

/**
 * @brief Gets the y-coordinate for firing a missile from the user.
 *
 * The function prompts the user to enter the y-coordinate for firing a missile,
 * validates the input, and returns the valid y-coordinate.
 *
 * @return The valid y-coordinate entered by the user.
 */
int getMissile_Y(){
        int res,check;
        printf("A quelle ordonnée souhaitez vous envoyez le missile ?\n");
        while( (check = scanf("%d",&res)) != 1 || res < 0 || res >= PLATE_SIZE){           //checking if the input is correct
                clearInputBuffer();
                printf("Valeur sasie incorrecte\n");
        }
        return res;
}