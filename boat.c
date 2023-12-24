/**
 * @file boat.c
 * @brief .c file containing every function relative to boats
 * @author Hicham Bettahar
 * @date December 24, 2023
 */
#include "header.h"

/**
 * @brief Creates a new boat with the specified indicator (coming right from the "createBoatList" function).
 *
 * The function generates a boat with a size based on the provided indicator.
 * The boat's orientation, position, and size are determined randomly.
 *
 * @param[in] indicator An integer indicator for determining the boat size.
 * @return The newly created boat.
 *
 * @note The function exits with an error message if the indicator is negative.
 */
Boat createBoat(int indicator){
        if(indicator < 0){                                    //checking parameters to avoid errors
                fprintf(stderr,"Erreur de paramètre");
                exit(2);
        }
        Boat new_Boat;
        new_Boat.boat_size = indicator + 1;                     //setting the boat size based on the indicator 
        new_Boat.orientation = rand()%2;                        //randomly determines orientation (0 = horizontal, 1 = vertical)
        if(new_Boat.orientation == 0){                          // Randomly determine the position based on the orientation to stay in the array
                new_Boat.x_pos = rand()%(PLATE_SIZE - new_Boat.boat_size) ;
                new_Boat.y_pos = rand()%(PLATE_SIZE);
        }
        if(new_Boat.orientation == 1){
                new_Boat.x_pos = rand()%PLATE_SIZE;
                new_Boat.y_pos = rand()%(PLATE_SIZE - new_Boat.boat_size);
        }
        
        return new_Boat;
}

/**
 * @brief Creates an array of boats representing the player's boats.
 *
 * The function allocates memory for an array of boats, generates each boat,
 * and ensures there are no collisions between boats.
 *
 * @return A pointer to the array of boats.
 *
 * @note The function exits with an error message if memory allocation fails.
 */
Boat* createBoatList(){
        Boat* boatList = malloc(BOAT_NB * sizeof(Boat));             //allocate memory for the array/list of boats
        if (boatList == NULL) {                                      //checking allocation error
                fprintf(stderr, "Erreur lors de l'allocation");
                exit(1);
        }
        int collision;
        for (int i = 0; i < BOAT_NB; i++){                     //generate each boat and check for collisions
                collision = 1;
                while(collision == 1){
                        boatList[i] = createBoat(i);
                        collision = check_collision(boatList, i);         //if there are collisions, we recreate the boat
                }
        }
        return boatList;
}

/**
 * @brief Checks for collisions between a newly created boat and existing boats.
 *
 * The function checks if the newly created boat collides with any of the existing
 * boats in the array.
 *
 * @param[in] boat_list Pointer to the array of boats.
 * @param[in] nb Index of the newly created boat in the array.
 * @return 1 if a collision is detected, 0 otherwise.
 *
 * @note The function exits with an error message if the array is NULL or if the
 * index is negative.
 */
int check_collision(Boat* boat_list,int nb){
        if (boat_list == NULL || nb < 0){                       // check for parameters error
                fprintf(stderr,"Erreur de paramètre");
                exit(1);
        }
        if(nb == 0){                                           // No need to check collisions for the first boat
                return 0;
        }
        for(int i = 0; i < nb; i++){                           // Check for collisions with previously created boats
                if(collision(&boat_list[i],&boat_list[nb]) == 1){
                        return 1;                             // Collision detected
                }
        }
        return 0;                                             // No collision
}


/**
 * @brief Checks for collision between two boats.
 *
 * The function checks if two boats collide based on their positions and orientations.
 *
 * @param[in] boat1 Pointer to the first boat.
 * @param[in] boat2 Pointer to the second boat.
 * @return 1 if a collision is detected, 0 otherwise.
 *
 * @note The function exits with an error message if either boat pointer is NULL.
 */
int collision(Boat* boat1, Boat* boat2) {
        if(boat1 == NULL || boat2 == NULL){
                fprintf(stderr,"Erreur de paramètre");
                exit(2);
        }
    // Check if the boats are in the same position
        if (boat1->x_pos == boat2->x_pos && boat1->y_pos == boat2->y_pos) {
                return 1;
        }

    // Check for overlap based on boat orientations
        if (boat1->orientation == 0 && boat2->orientation == 0) {
        // Both boats are horizontal
                if( (boat1->y_pos == boat2->y_pos) && ((boat1->x_pos <= boat2->x_pos + boat2->boat_size - 1) && (boat1->x_pos + boat1->boat_size - 1 >= boat2->x_pos))){
                        return 1;
                }
        } else if (boat1->orientation == 1 && boat2->orientation == 1) {
        // Both boats are vertical
                if ((boat1->x_pos == boat2->x_pos) && ((boat1->y_pos <= boat2->y_pos + boat2->boat_size - 1) && (boat1->y_pos + boat1->boat_size - 1 >= boat2->y_pos))){
                        return 1;
                }
        } else {
        // Boats have different orientations
                if (((boat1->x_pos >= boat2->x_pos - 1 && boat1->x_pos <= boat2->x_pos + boat2->boat_size) || (boat2->x_pos >= boat1->x_pos - 1 && boat2->x_pos <= boat1->x_pos + boat1->boat_size)) && ((boat1->y_pos >= boat2->y_pos - 1 && boat1->y_pos <= boat2->y_pos + boat2->boat_size) || (boat2->y_pos >= boat1->y_pos - 1 && boat2->y_pos <= boat1->y_pos + boat1->boat_size))){
                        return 1;
                }
        }
        // No collision detected
         return 0;
}

/**
 * @brief Places boats on the game board based on their positions and orientations.
 *
 * The function updates the game board matrix with boat positions.
 *
 * @param[in] board Pointer to the game board structure.
 * @param[in] boat_list Pointer to the array of boats.
 *
 * @note The function exits with an error message if either parameter is NULL.
 */
void boatPlacement(Game_board* board, Boat* boat_list){
        if (board == NULL || boat_list == NULL){               //checking for parametors error
                fprintf(stderr,"Erreur de paramètres");
                exit(2);
        }
        for (int i = 0; i < BOAT_NB; i++){
                if(boat_list[i].orientation == 0){              //Boat is horizontal
                        for(int j = boat_list[i].x_pos; j < (boat_list[i].x_pos + boat_list[i].boat_size);j++){        //we go trough every position where the boat is on the board and update it as a 'BOAT' 
                                board->matrix[boat_list[i].y_pos][j]= BOAT;
                        }
                }
                else if(boat_list[i].orientation==1){          //Boat is vertical
                        for(int k = boat_list[i].y_pos; k < (boat_list[i].y_pos + boat_list[i].boat_size); k++){      //we go trough every position where the boat is on the board and update it as a 'BOAT'
                                board->matrix[k][boat_list[i].x_pos]= BOAT;
                        }
                }
        }
} 


/**
 * @brief Checks if a boat is still alive on the game board.
 *
 * The function determines if a boat is still present on the game board based on its
 * position, size, and orientation.
 *
 * @param[in] boat Pointer to the boat to be checked.
 * @param[in] game Pointer to the game board structure.
 * @return 1 if the boat is alive, 0 if the boat is destroyed.
 *
 * @note The function exits with an error message if either parameter is NULL.
 */
int isAlive(Boat* boat, Game_board* game){           
        if(boat == NULL || game == NULL){                           //checing for parameters error
                printf("Erreur dans la fonction isAlive !");
                exit(21);
        }
        // Check boat's presence on the game board based on its orientation
        if(boat->orientation == 0){               // if is horizontal
                for(int i = boat->x_pos; i < boat->x_pos + boat->boat_size; i++){
                        if(game->matrix[boat->y_pos][i] == BOAT){          //if only one position contains 'BOAT' then it is still alive
                                return 1;         //still alive
                        }
                }
        }
        if(boat->orientation == 1){               // if is vertical
                for(int i = boat->y_pos; i < boat->y_pos + boat->boat_size; i++){
                        if(game->matrix[i][boat->x_pos] == BOAT){
                                return 1;
                        }
                }
        }
        return 0;          //boat is destroyed
}

/**
 * @brief Counts the number of alive boats in the game board.
 *
 * The function iterates through the array of boats and checks how many boats are
 * still alive on the game board based on their positions and orientations.
 *
 * @param[in] boat_list Pointer to the array of boats.
 * @param[in] board Pointer to the game board structure.
 * @return The number of alive boats.
 *
 * @note The function exits with an error message if either parameter is NULL.
 */
int howManyAlive(Boat* boat_list,Game_board* board){
        if(boat_list == NULL || board == NULL){            //checking for parameters error
                fprintf(stderr,"Erreur de paramètre");
                exit(2);
        }
        int compt = 0;                                     
        for(int i = 0; i < BOAT_NB; i++){                 //for each boat we check if it is still alive
                if (isAlive(&boat_list[i],board) == 1){
                        compt ++;
                }
        }
        return compt;         // Return the number of alive boats
} 
