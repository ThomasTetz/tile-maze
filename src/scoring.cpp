//including necessary header files
#include "shared.h"
#include <stdio.h>
#include <stdlib.h>

/* === scoring() === */
//gets the current list of high scores from a txt file
//each map has 3 high score stored within that txt file
//sorts the 3 from the level that was played with the users score
//writes the scores back excluding the worst of the 4 sorted
void scoring(int map_choice, unsigned long time){
    
    int32_t scores[21];
    char scores_str[21][10] = {0}; // set to null so can concatenate

    File score_file; // file to read
    
    // === reading old scores from the text file ===
    
    //reads current high scores from a text file and converts to
    //an integer array
    score_file = SD.open("scores.txt"); // open file for reading
    int i = 0, char_pos = 0; // tracks location in the file
    char inputChar; // character read from the file
    
    if (score_file){ // if it opened
        Serial.println("file successfuly opened: reading");
        //reads until end of file
        while (score_file.available()){
            
            inputChar = score_file.read(); // reads char by char
            
            if (inputChar == '\n'){ // if end of line goes to next
                ++i;
                char_pos = 0;
            }
            else if (inputChar == '\0'){ // catch string termination
            }
            else{ //appends to scores_str[i] and move on
                scores_str[i][char_pos] = inputChar;
                ++char_pos;
            }
        }
        score_file.close(); // closes file when done
    }
    else{ // sets default scores if file not found
        Serial.println("Error opening to read");
        scores[0]   = 1000; scores[1]   = 15000; scores[2]   = 20000;
        scores[3]   = 1000; scores[4]   = 15000; scores[5]   = 20000;
        scores[6]   = 1000; scores[7]   = 15000; scores[8]   = 20000;
        scores[9]   = 1000; scores[10]  = 15000; scores[11]  = 20000;
        scores[12]  = 1000; scores[13]  = 15000; scores[14]  = 20000;
        scores[15]  = 1000; scores[16]  = 15000; scores[17]  = 20000;
        scores[18]  = 1000; scores[19]  = 15000; scores[20]  = 20000;
    }
    
    //converts the data to an integer array
    for (i = 0; i < 21; ++i){
        scores[i] = atoi(scores_str[i]);
    }
    
    // === sorting the users score with the highscore of the map ===
    
    // sorts the 3 high scores for the map and the users time
    if(time > scores[(map_choice*3)+2]){
         // do nothing if higher than the current highest
    }
    //time was less than or equal to old 3rd highest score
    else if (time >= scores[(map_choice*3)+1] && time < scores[(map_choice*3)+2]){
        // puts time in 3rd spot
        // old 3rd is bumped out
        scores[(map_choice*3)+2] = time;
    }
    //time was between old 1st and 2nd highest scores
    else if (time >= scores[(map_choice*3)] && time < scores[(map_choice*3)+1]){
        //moves old 2nd to 3rd spot
        //puts time in 2nd spot
        //old 3rd is bumped out
        scores[(map_choice*3)+2] = scores[(map_choice*3)+1];
        scores[(map_choice*3)+1] = time;
    }
    // time was lower than old 1st
    else if (time < scores[map_choice*3]){
        //puts old 2nd in 3rd spot
        //puts old 1st in 2nd spot
        //puts time in first 1st spot
        //old 3rd is bumped out
        scores[(map_choice*3)+2] = scores[(map_choice*3)+1];
        scores[(map_choice*3)+1] = scores[(map_choice*3)];
        scores[(map_choice*3)] = time;
    }
    
    //the arduino SD FILE_WRITE function appends without removing the
    //old file data, so must manually delete the old file
    //even when lowercase is specified when creating the new file it
    //shows up as upper case so catch both
    if (SD.exists("scores.txt")) { SD.remove("scores.txt"); }
    if (SD.exists("SCORES.TXT")) { SD.remove("SCORES.TXT"); }
    
    //opens a new file to write the scores to 
    score_file = SD.open("scores.txt", FILE_WRITE);
    if (score_file){
        //writes the scores to the file, one per line
        for (i = 0; i < 21; ++i){
            score_file.println(scores[i]);
        }
        //closes the file
        score_file.close();
    }
    else{ // file failed to open
        Serial.println("failed to open for WRITE");
    }

    // === high score screen ===

    tft.setTextWrap(false); //no wrapping 
    tft.fillScreen(0x0000); // fills the screen with black
    tft.setTextColor(0xFFFF,0x0000); //set text to white font
    
    // displays the high scores for the map and the user's score
    tft.setCursor(12,24); // set cursor, indicates where
    tft.print("=================");
    tft.setCursor(12,32);
    tft.print("|| High scores ||");
    tft.setCursor(12,40);
    tft.print("=================");
    tft.setCursor(24, 60); tft.print("1. ");//can it take arguments?
    tft.setCursor(48, 60); tft.print(scores[(map_choice*3)]);
    tft.setCursor(24, 72); tft.print("2. ");//can it take arguments?
    tft.setCursor(48, 72); tft.print(scores[(map_choice*3)+1]);
    tft.setCursor(24, 84); tft.print("3. ");//can it take arguments?
    tft.setCursor(48, 84); tft.print(scores[(map_choice*3)+2]);
    tft.setCursor(12, 104); tft.print("Your score: ");//can it take arguments?
    tft.setCursor(80, 104); tft.print(time);
    tft.setCursor(9, 140);
    tft.print("Click to continue.");
    
    //wait till user clicks to return to main menu
    while(digitalRead(JOYSTICK_BUTTON) != 0){
            delay(10);
    }
    
    //now go to main menu
    return ;
}
