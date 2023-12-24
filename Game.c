/**
 * @file Game.c
 * @brief .c file containing every function relative to the progress of the game
 * @author Hicham Bettahar
 * @date December 24, 2023
 */
#include "header.h"

/**
 * @brief Creates a new game with player and enemy game boards, as well as boat arrays.
 *
 * The function allocates memory for the game structure, initializes player and enemy
 * boat arrays, and creates player and enemy game boards.
 *
 * @return A pointer to the created game structure.
 *
 * @note The function exits with an error message if memory allocation fails.
 */
Game* createGame(){
        Game* game = malloc(sizeof(Game));
        if(game == NULL){
                fprintf(stderr,"Erreur lors de l'allocation");
                exit(1);
        }
        game->boat_tab_player = createBoatList();
        game->boat_tab_bot = createBoatList();
        game->tab_player = createGameBoard(PLATE_SIZE);
        game->tab_bot = createGameBoard(PLATE_SIZE);
        return game;
}


/**
 * @brief Executes the main game loop, allowing the player to take turns and play against the enemy bot.
 *
 * The function creates the game, initializes player and enemy game boards, places boats, and executes
 * the main game loop until one of the players wins or loses. It displays the game status at each turn.
 * At the end, the function free all allocated memory.
 *
 * @note The function exits with an error message if memory allocation fails during game creation.
 */
void mainGame(){
        check_const();                  //check if PLATE_SIZE and BOAT_NB are correct
        int nbBoatLeftPlayer = 5;
        int nbBoatLeftBot = 5;
        Game* game = createGame();
        gameBoardInit(game->tab_bot);
        gameBoardInit(game->tab_player);
        printf("Création des tableaux ...\n");
        sleep(1); 
        boatPlacement(game->tab_bot,game->boat_tab_bot);
        boatPlacement(game->tab_player,game->boat_tab_player);
        printf("Placement des bateaux ...\n\n");
        sleep(2);
        printf(" --- VOTRE TABLEAU --- \n\n");
        gameBoardDisplay(game->tab_player);
        while( nbBoatLeftPlayer != 0 && nbBoatLeftBot !=0){
                playerTurn(game);
                nbBoatLeftBot = howManyAlive(game->boat_tab_bot,game->tab_bot);
                printf("Bateaux restants ennemis: %d \n",nbBoatLeftBot);
                ennemyTurn(game);       
                nbBoatLeftPlayer = howManyAlive(game->boat_tab_player,game->tab_player);
                printf("Il vous reste %d bateaux\n",nbBoatLeftPlayer);
        }
        if(nbBoatLeftBot == 0){
                printf("Félicitations vous avez gagné la partie !\n");
        }
        else{
                printf("Dommage vous avez perdu, mais ce n'est que partie remise !\n");
        }
        printf("Libération de l'espace mémoire ...\n");
        freeGame(game);
        sleep(1);
}

/**
 * @brief Displays the game menu and allows the player to choose between starting a game, 
 *        reading game instructions, or quitting the game.
 *
 * The function displays the menu options and prompts the player to make a selection.
 * It then executes the corresponding action based on the player's choice.
 */
void menu(){
        int res = 0;
        int check = 0;
        while(res != 3){
                printf("---BATAILLE NAVALE---\n");
                printf("Que souhaitez vous faire: -1: Lancer une partie -2: Explications -3: Quitter le jeu\n");
                while((check = scanf("%d",&res)) != 1 || res < 1 || res > 3 ){
                        printf("Valeur sasie incorrecte, veuillez réessayer:\n");
                        clearInputBuffer();
                }
                if(res == 1){
                        mainGame();
                }
                else if(res == 2){
                        printf("Explications du jeu:\n");
                        printf(" Le but du jeu est de détruire tous les bateaux adverses\n");
                        printf(" ~ représente l'eau\n");
                        printf(" X représente les endroits où vous avez tiré dans l'eau\n");
                        printf(" O représente vos bateaux\n");
                        printf(" D représentes les bateaux qui on été touchés\n");
                        printf("Vous devez rentrer l'abcisse et l'ordonné de la case sur laquelle vous souhaitez tirer\n");
                        printf("Si vous touchez un bateau, vous pourrez rejouer votre tour !\n");
                }
        }

        printf("Ce fût un plaisir de jouer avec vous, à bientot !\n");
}

/**
 * @brief Checks the validity of constants (PLATE_SIZE and BOAT_NB) to ensure a valid game configuration.
 *
 * The function performs checks to ensure that the number of boats and the size of the game board are within
 * reasonable limits. It exits with an error message if the conditions are not met.
 *
 * @note The function exits with an error message if the conditions for a valid game configuration are not met.
 */
void check_const(){
        if(PLATE_SIZE - BOAT_NB < PLATE_SIZE/5 || BOAT_NB < 1  || PLATE_SIZE < 2){                   //hasardous maths to determine if there are too many boats for the size of the board
                fprintf(stderr,"Il y a trop de bateaux pour la taille du plateaux");
                exit(3);
        }
        if(BOAT_NB < 1  || PLATE_SIZE < 2){
                fprintf(stderr,"La taille du plateau ou le nombre de bateaux est invalide");
                exit(4);
        }
}

/**
 * @brief Frees the memory allocated for a Game structure.
 *
 * This function deallocates memory for the Game structure, including the boat arrays
 * (boat_tab_player and boat_tab_bot) and the game boards (tab_player and tab_bot).
 * It also calls the corresponding function to free the memory of each game board.
 *
 * @param game A pointer to the Game structure to be freed.
 *
 * @note If the game pointer is NULL, nothing is freed.
 */
void freeGame(Game* game){
    if (game == NULL) {
        return;  // Nothing to free if the game pointer is NULL
    }

    // Free boat arrays
    free(game->boat_tab_player);
    free(game->boat_tab_bot);

    // Free game boards
    freeGameBoard(game->tab_player);
    freeGameBoard(game->tab_bot);

    // Free the Game structure itself
    free(game);
}

/**
 * @brief Frees the memory allocated for a Game_board structure.
 *
 * This function deallocates memory for the Game_board structure, including freeing
 * individual rows of the matrix and the matrix itself. If the board pointer is NULL,
 * nothing is freed.
 *
 * @param board A pointer to the Game_board structure to be freed.
 *
 * @note If the board pointer is NULL, nothing is freed.
 */
void freeGameBoard(Game_board* board){
    if (board == NULL) {
        return;  // Nothing to free if the board pointer is NULL
    }

    // Free matrix rows
    for (int i = 0; i < board->Matrix_size; i++) {
        free(board->matrix[i]);
    }

    // Free matrix
    free(board->matrix);

    // Free the Game_board structure itself
    free(board);
}