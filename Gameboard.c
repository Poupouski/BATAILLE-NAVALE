/**
 * @file Gameboard.c
 * @brief .c file containing every function relative to game boards
 * @author Hicham Bettahar
 * @date December 24, 2023
 */
#include "header.h"

/**
 * @brief Creates a game board with the specified size (PLATE_SIZE).
 *
 * The function allocates memory for a game board matrix and initializes its size.
 *
 * @param[in] size Size of the game board.
 * @return A pointer to the created game board structure.
 *
 * @note The function exits with an error message if the size is invalid or if memory
 * allocation fails.
 */
Game_board* createGameBoard(int size){
        if((size < 1) || size > PLATE_SIZE ){
                fprintf(stderr,"taille incorrecte");
                exit(1);
        } 
        Game_board* board = malloc(sizeof(Game_board));
        if (board == NULL){
                fprintf(stderr,"Erreur lors de l'allocation");
                exit(1);
        }
        board->Matrix_size = size;
        board->matrix = malloc(size * sizeof(Case_type*));
        if(board->matrix == NULL){
                fprintf(stderr,"Erreur lors de l'allocation");
                exit(1);
        }
        for (int i = 0; i < size; i++){
                board->matrix[i] = malloc(size * sizeof(Case_type));
                if(board->matrix[i] == NULL){
                        fprintf(stderr,"Erreur lors de l'allocation");
                        exit(1);
                }
        }
        return board;
}

/**
 * @brief Initializes a game board with water in all positions.
 *
 * The function sets all positions on the game board matrix to the WATER type.
 *
 * @param[in] board Pointer to the game board structure.
 *
 * @note The function exits with an error message if the game board pointer is NULL.
 */
void gameBoardInit(Game_board* board){
        if (board == NULL){
                fprintf(stderr,"Erreur lors de l'allocation");
                exit(1);
        }
        for(int i = 0; i < board->Matrix_size; i++){
                for( int j=0; j < board->Matrix_size;j++){
                        board->matrix[i][j] = WATER;
                }
        }
}

/**
 * @brief Displays the content of the game board.
 *
 * The function prints the content of the game board matrix, representing different
 * types of cases with symbols. The display depends of the PLATE_SIZE value
 *
 * @param[in] board Pointer to the game board structure.
 *
 * @note The function exits with an error message if the game board pointer is NULL.
 */
void gameBoardDisplay(Game_board* board){
        if (board == NULL){
                fprintf(stderr,"Erreur lors de l'allocation");
                exit(1);
        }
        if(PLATE_SIZE < 11){
                printf("   ");
                for (int k = 0; k < board->Matrix_size;k++){
                        printf("%d ",k);
                }
                printf("\n");
                for(int i = 0; i < board->Matrix_size ; i++){ 
                        printf("%d  ",i);
                        for(int j = 0; j < board->Matrix_size ; j++){                 //print symbol based on the case type
                                if (board->matrix[i][j] == WATER){
                                        printf("~ ");
                                }
                                if (board->matrix[i][j] == WATER_SHOT){
                                        printf("X ");
                                }
                                if (board->matrix[i][j] == BOAT){
                                        printf("O ");
                                }
                                if (board->matrix[i][j] == WRECK){
                                        printf("D ");
                                }
                        }
                        printf("\n");
                }
                printf("\n");
        }
        else{
                printf("     ");
                for (int k = 0; k < board->Matrix_size;k++){
                        printf("%02d ",k);
                }
                printf("\n");
                for(int i = 0; i < board->Matrix_size ; i++){ 
                        printf("%02d   ",i);
                        for(int j = 0; j < board->Matrix_size ; j++){                 //print symbol based on the case type
                                if (board->matrix[i][j] == WATER){
                                        printf("~  ");
                                }
                                if (board->matrix[i][j] == WATER_SHOT){
                                        printf("X  ");
                                }
                                if (board->matrix[i][j] == BOAT){
                                        printf("O  ");
                                }
                                if (board->matrix[i][j] == WRECK){
                                        printf("D  ");
                                }
                        }
                        printf("\n");
                }
                printf("\n");
        }
}

/**
 * @brief Displays the enemy game board with symbols representing hits and misses.
 *
 * The function prints the content of the enemy game board matrix, showing wrecks,
 * water shots, and empty spaces. We can't see their boats
 *
 * @param[in] board Pointer to the enemy game board structure.
 *
 * @note The function exits with an error message if the game board pointer is NULL.
 */
void ennemyBoardDisplay(Game_board* board){
        if (board == NULL){
                fprintf(stderr,"Erreur lors de l'allocation");
                exit(1);
        }
        if(PLATE_SIZE < 11){
                printf("   ");
                for (int k = 0; k < board->Matrix_size;k++){
                       printf("%d ",k);
                }
                printf("\n");
                for(int i = 0; i < board->Matrix_size ; i++){ 
                        printf("%d  ",i);
                        for(int j = 0; j < board->Matrix_size ; j++){
                                if (board->matrix[i][j] == WRECK ){
                                        printf("D ");
                                }
                                else if (board->matrix[i][j] == WATER_SHOT){
                                        printf("X ");
                                }
                                else{
                                        printf("~ ");
                                }
                        }
                        printf("\n");
                }
                printf("\n");
        }
        else{
                printf("     ");
                for (int k = 0; k < board->Matrix_size;k++){
                       printf("%02d ",k);
                }
                printf("\n");
                for(int i = 0; i < board->Matrix_size ; i++){ 
                        printf("%02d   ",i);
                        for(int j = 0; j < board->Matrix_size ; j++){
                                if (board->matrix[i][j] == WRECK ){
                                        printf("D  ");
                                }
                                else if (board->matrix[i][j] == WATER_SHOT){
                                        printf("X  ");
                                }
                                else{
                                        printf("~  ");
                                }
                        }
                        printf("\n");
                }
                printf("\n");
        }
}