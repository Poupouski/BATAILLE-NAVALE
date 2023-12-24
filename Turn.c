/**
 * @file Turn.c
 * @brief .c file containing every function relative to players and bot turn
 * @author Hicham Bettahar
 * @date December 24, 2023
 */

#include "header.h"

/**
 * @brief Processes a missile shoot at the specified coordinates on the game board.
 *
 * The function prompts the user for missile coordinates, checks the result of the shoot,
 * and updates the game board accordingly.
 *
 * @param[in,out] board Pointer to the game board structure.
 * @return 0 if the shoot was unsuccessful, 1 if a boat was hit, and updates the board.
 *
 * @note The function exits with an error message if the game board pointer is NULL.
 */
int missileShoot(Game_board* board){
        if (board == NULL){
                fprintf(stderr,"Erreur de paramètre");
                exit(2);
        } 
        int x = getMissile_X();
        int y = getMissile_Y();
        if (board->matrix[y][x] == WATER){
                printf("Raté, le tir est partit droit dans l'eau !\n");
                board->matrix[y][x] = WATER_SHOT;
                return 0;
        }
        else if(board->matrix[y][x] == WATER_SHOT || board->matrix[y][x] == WRECK){
                printf("Vous avez deja tiré ici chef !\n");
                return 0;
        }
        else if (board->matrix[y][x] == BOAT){
                printf("Touché chef, félicitations !\n");
                printf("Vous pouvez rejouer votre tour\n");
                board->matrix[y][x] = WRECK;
                return 1;
        }
}

/**
 * @brief Simulates a missile shoot by the enemy bot at a random position on the game board.
 *
 * The function generates random coordinates for the enemy bot's missile shoot,
 * checks the result, and updates the game board accordingly. The bot cans only
 * shoot where he hasn't shooted yet.
 *
 * @param[in,out] board Pointer to the game board structure.
 * @return 0 if the enemy bot missed, 1 if the enemy bot hit a boat and updates the board.
 *
 * @note The function exits with an error message if the game board pointer is NULL.
 */
int bot_Missile_Shoot(Game_board* board){
        if (board == NULL){
                fprintf(stderr,"Erreur de paramètre");
                exit(2);
        }
        int condition = 0;
        int x,y;
        while(condition == 0){
                x = rand()%PLATE_SIZE;
                y = rand()%PLATE_SIZE;
                if(board->matrix[y][x] == BOAT || board->matrix[y][x] == WATER){
                        condition = 1;
                }
        }
        if (board->matrix[y][x] == WATER){
                printf("L'ennemi a raté son tir on a eu chaud !\n");
                board->matrix[y][x] = WATER_SHOT;
                return 0;
        }
        else if (board->matrix[y][x] == BOAT){
                printf("Alerte l'ennemi a touché notre bateau !\n");
                printf("Il va pouvoir retirer !\n");
                board->matrix[y][x] = WRECK;
                return 1;
        }
}

/**
 * @brief Executes the player's turn, allowing them to take shots at the enemy game board.
 *
 * The function displays the enemy game board, prompts the player to take a shot,
 * processes the result, and updates the display accordingly. If the shot is 
 * successful, the player can play his turn again
 *
 * @param[in,out] game Pointer to the game structure.
 *
 * @note The function exits with an error message if the game pointer is NULL.
 */
void playerTurn(Game* game){
        int do_replay = 1;
        int nbBoatAlive = BOAT_NB;
        if(game == NULL){
                fprintf(stderr,"Erreur de paramètre");
                exit(2);
        }
        printf(" --- TABLEAU ENNEMI ---\n\n");
        ennemyBoardDisplay(game->tab_bot);
        while(do_replay == 1 && nbBoatAlive != 0){            //The player can shoot again while he touch an ennemy boat and the game is not finished
                do_replay = missileShoot(game->tab_bot);
                nbBoatAlive = howManyAlive(game->boat_tab_bot,game->tab_bot);
                sleep(2);
                printf(" --- TABLEAU ENNEMI ---\n\n");
                ennemyBoardDisplay(game->tab_bot);
                sleep(2);
        }
}


/**
 * @brief Executes the enemy's turn, allowing them to take shots at the player's game board.
 *
 * The function simulates the enemy's actions, generates a missile shot, processes the result,
 * and updates the display of the player's game board. If the shot is successful, the bot can
 * play again
 *
 * @param[in,out] game Pointer to the game structure.
 *
 * @note The function exits with an error message if the game pointer is NULL.
 */

void ennemyTurn(Game* game){
        int do_replay = 1;
        int nbBoatAlive = BOAT_NB;
        if(game == NULL){
                fprintf(stderr,"Erreur de paramètre");
                exit(2);
        }
        while(do_replay == 1 && nbBoatAlive != 0){               //The bot can shoot again while he touch an ennemy boat and the game is not finished
                printf("L'ennemi se prépare à tirer !\n");
                sleep(2);
                do_replay = bot_Missile_Shoot(game->tab_player);
                nbBoatAlive = howManyAlive(game->boat_tab_player,game->tab_player);
                sleep(2);
                printf(" --- VOTRE TABLEAU ---\n\n");
                gameBoardDisplay(game->tab_player);
                sleep(2);
        }
}


