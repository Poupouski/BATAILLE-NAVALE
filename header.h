#ifndef HEADER_H
        #define HEADER_H

/**
 * @file header.h
 * @brief Header file containing structure, enum and functions declarations for a battleship game.
 * @author Hicham Bettahar
 * @date December 24, 2023
 */

        #define BOAT_NB 7   /**< Number of boats in the game. */
        #define PLATE_SIZE 10     /**< Size of the game board. */

        #include <stdio.h>
        #include <stdlib.h>
        #include <string.h>
        #include <time.h>
        #include <unistd.h>

        /**
        * @brief Enumeration representing different types of cases on the game board.
        */
        typedef enum{
                WATER,        /**< Water on the game board. */
                WATER_SHOT,   /**< Water shot on the game board. */
                BOAT,         /**< Boat on the game board. */
                WRECK         /**< Wrecked boat on the game board. */
        }Case_type;

        /**
        * @brief Structure representing a boat with its size, position, and orientation.
        */
        typedef struct{
                int boat_size;        /**< Size of the boat. */
                int x_pos;            /**< X-coordinate of the top-left point of the boat. */
                int y_pos;            /**< Y-coordinate of the top-left point of the boat. */
                int orientation;      /**< Orientation of the boat (0 for horizontal, 1 for vertical). */
        }Boat;

        /**
        * @brief Structure representing a game board.
        */
        typedef struct{
                Case_type** matrix;   /**< 2D array representing the game board. */
                int Matrix_size;      /**< Size of the game board. */
        }Game_board;                  

        /**
        * @brief Structure representing the game with player and enemy game boards.
        */
        typedef struct{
                Game_board* tab_player;      /**< Player's game board. */
                Game_board* tab_bot;         /**< Enemy's game board. */
                Boat* boat_tab_player;       /**< Array of player's boats. */
                Boat* boat_tab_bot;          /**< Array of enemy's boats. */
        }Game;
         
        //Prototype of every function, it will be more detailled in the corresponding files
        //functions in boat.c
        Boat createBoat(int indicator);
        Boat* createBoatList();
        int check_collision(Boat* boat_list,int nb);
        int collision(Boat* boat1, Boat* boat2);
        void boatPlacement(Game_board* board, Boat* boat_list);
        int isAlive(Boat* boat, Game_board* game);
        int howManyAlive(Boat* boat_list,Game_board* board);

        //functions in char.c
        void clearInputBuffer();
        int getMissile_X();
        int getMissile_Y();

        //functions in Gameboard.c
        Game_board* createGameBoard(int size);
        void gameBoardInit(Game_board* board);
        void gameBoardDisplay(Game_board* board);
        void ennemyBoardDisplay(Game_board* board);

        //functions in Game.c
        Game* createGame();
        void mainGame();
        void menu();
        void check_const();
        void freeGameBoard(Game_board* board);
        void freeGame(Game* game);

        //functions in Turn.c
        int missileShoot(Game_board* board);
        int bot_Missile_Shoot(Game_board* board);
        void playerTurn(Game* game);
        void ennemyTurn(Game* game);
        
#endif