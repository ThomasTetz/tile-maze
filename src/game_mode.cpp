//including necessary header files
#include "shared.h"
#include "game_mode.h"
#include "constraints.h"
#include "scoring.h"

//size of the map printed on the screen
const int16_t map_width = 128;
const int16_t map_height = 128;

//initial map and cursor positions
int initVert,initHor;

void playing(int map_choice){
    
    //initializing variables
    int cursor_x = 0, cursor_y = 0; // coordinates of the cursor
    int old_cursor_x = 0, old_cursor_y = 0; // used when updating cursor
    int init_joystick_vert = analogRead(JOYSTICK_VERT);   // resting vertical
    int init_joystick_horiz = analogRead(JOYSTICK_HORIZ); // resting horizontal
    int delta_vert = 0, delta_horiz = 0; // change in joystick
    int vertical = 0, horizontal = 0, joystick_button = 0; // starting values
    bool sliding = false; // condition of the player, starts stationary
    int cursor_size = 4; // size of one side of the square player cursor
    int cursor_change[2]; //holds [horizontal] [vertical] change

    int mapBoundaries;
    //coordinates of the winning tile
    int finX;
    int finY;
        
        
    // ===============

    //Easy1 (map name)
    if (map_choice==0) { //pixel = 93, 1006
        mapBoundaries=17; // number of wall tiles on the map
        // starting position            finish tile position
        cursor_x = 112; cursor_y = 116; finX = 52; finY = 0;
    }

    //Easy2
    else if (map_choice==1) { //pixel = 93, 893
        mapBoundaries=36;
        cursor_x = 112;  cursor_y = 116; finX = 112; finY = 16;
    }

    //Medium1
    else if (map_choice==2) { //pixel = 107, 892
        mapBoundaries=15;
        cursor_x = 40; cursor_y = 112; finX = 108; finY = 16;
    }

    //Medium2
    else if (map_choice==3) { //pixel = 192, 907
        mapBoundaries=38;
        cursor_x = 124;  cursor_y = 104; finX = 40; finY = 12;
    }

    //Hard1
    else if (map_choice==4) { //pixel = 223, 767
        mapBoundaries=68;
        cursor_x = 120; cursor_y = 100; finX = 120; finY = 32;
    }

    //Hard2
    else { //pixel = 510, 608
        mapBoundaries=130;
        cursor_x = 116; cursor_y = 64; finX = 124; finY = 52;
    }

    int pixel[mapBoundaries];
            
    //loads the constraints file containing wall tile location
    for (int i = 0; i < mapBoundaries; ++i){
        pixel[i] = load_constraints(map_choice,i);
    }    
    Serial.println("Constraints loaded!");
            
    //holds the coordinates of the wall tiles
    int wall_X[mapBoundaries];
    int wall_Y[mapBoundaries];

    //converts the pixel data to be useful on the map
    for (int i = 0; i < mapBoundaries; ++i){
        wall_X[i] = (((pixel[i]-1)%32)*4);
        wall_Y[i] = ((31-floor((pixel[i]-1)/32))*4);
    }

    // === game begins ===
    
    //start time for calculating score
    unsigned long start_time = millis();

    //plays until user touches the win tile or quits
    while(true){
        //precedence is arbitrarily given to vertical if diagonal
        //can quit to main by clicking when stationary
        
        //draws the initial cursor (red)
        tft.fillRect(cursor_x, cursor_y, cursor_size, cursor_size, 0xF800);
        
        //if the joystick is moved the cursor slides until hitting a 
        //wall tile or the edge of the map
        while (sliding == false){
            // reads all inputs of the joystick
            vertical   = analogRead(JOYSTICK_VERT);  // 0-1023
            horizontal = analogRead(JOYSTICK_HORIZ); // 0-1023
            joystick_button   = digitalRead(JOYSTICK_BUTTON); // if joystick is pressed
            delta_vert = vertical - init_joystick_vert; // vertical change
            delta_horiz= horizontal - init_joystick_horiz; // horizontal change
                  
            //up
            if (delta_vert < -175){ // threshold for movement
                //changes to be applied to the cursor position
                cursor_change[0] = 0;
                cursor_change[1] = -1 * cursor_size;
                sliding = true;
                continue;
            }
            //down
            else if (delta_vert > 175){
                cursor_change[0] = 0;
                cursor_change[1] = cursor_size;
                sliding = true;
                continue;
            }
            //right
            else if(delta_horiz > 175){
                cursor_change[0] = cursor_size;
                cursor_change[1] = 0;
                sliding = true;
                continue;
            }
            //left
            else if (delta_horiz < -175){
                cursor_change[0] = -1* cursor_size;
                cursor_change[1] = 0;
                sliding = true;
                continue;
            }
            //joystick pressed (quit to main menu)
            else if (digitalRead(JOYSTICK_BUTTON) == 0){
                return;
            }
            
            //displays the score/time as you play
            tft.setCursor(60, 140);
            tft.print(millis() - start_time);
            delay(1); //no busy loop
        }
            
        while (sliding == true){            
            old_cursor_x = cursor_x;
            old_cursor_y = cursor_y;
            
            //changes the cursor according to joystick input
            //constrains it to the screen
            cursor_x = cursor_x + cursor_change[0];
            cursor_y = cursor_y + cursor_change[1];
            cursor_x = constrain(cursor_x,0,map_width-cursor_size);
            cursor_y = constrain(cursor_y,0,map_height-cursor_size);
            
            //checks if the cursor is hitting each wall tile
            for (int i = 0; i < mapBoundaries; ++i) {    
                //stops the cursor if hitting a wall tile
                if (cursor_x == wall_X[i] && cursor_y == wall_Y[i]) { 
                    cursor_x = old_cursor_x;
                    cursor_y = old_cursor_y;
                    sliding = false;
                    continue;
                }
                
            }
            
            //redraws the cursor in its new position if it has moved
            //also redraws the part of the map where the cursor was
            if( (cursor_x != old_cursor_x) || (cursor_y != old_cursor_y) ){
                tft.fillRect(cursor_x, cursor_y, cursor_size, cursor_size, 0xF800);
                tft.fillRect(old_cursor_x, old_cursor_y, cursor_size, cursor_size, 0xFFFF);
            }
            else{
                //catches it at the map edge
                sliding = false;
            }
            
            //check if at finish/win
            if (cursor_x == finX && cursor_y== finY) {
                //passes score for evaluation
                scoring(map_choice, millis()-start_time);
                return;
            }
            
            //updates the score/time on the screen
            tft.setCursor(60, 140);
            tft.print(millis() - start_time);
            delay(1);
        }
    }
}

/* === game_mode() ===*/
void game_mode(int map_choice){
    //prints the word time in the cleared box below the map 
    char scoreString[20];
    strcpy(scoreString,"Time: ");    
    tft.setCursor(24,140); // set cursor, indicates where
    tft.setTextWrap(false); //no wrapping
    tft.setTextColor(0xFFFF,0x0000); //set colour
    tft.print(scoreString);
    
    //begins the game
    playing(map_choice);
    
    return;
}


