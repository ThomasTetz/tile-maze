/* 
 * CMPUT 274 Final Project
 * 
 * Thomas Tetz
 * Brett Baker
 * 
 * Tile Maze: a sliding tile puzzle game (instructions in README)
 * 
 */ 

//including necessary header files
#include "shared.h"
#include "menu.h"
#include "bitmap_printer.h"
#include "game_mode.h"
#include "scoring.h"

/*
 * 
 *    _______ _ _         __  __                 
 *   |__   __(_) |       |  \/  |                    
 *      | |   _| | ___   |      | __ _ ________          
 *      | |  | | |/ __ \ | |\/| |/ _ '|_   / __ \        
 *      | |  | | |  ___/ | |  | | (_| |/  /  ___/ 
 *      |_|  |_|_|\____| |_|  |_|\_ _,_/___\_____|                   
 *                              
 *                      
 *             
 */   

//defining external tft for use by multiple files
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
        
/* === main() === */
int main(){

    init();
    
    //setting up the external tft
    tft.initR(INITR_BLACKTAB);
    
    //initializing SD card
    Serial.print("Initializing SD card...");
    if (!SD.begin(SD_CS)) {
        Serial.println("failed!");
        return 1; //change to exit failure or whatever
    }
    Serial.println("OK!");
    
    // Attach USB for applicable processors
    #ifdef USBCON
        USBDevice.attach();
    #endif
    
    //setting up digital pin for joystick push button
    pinMode(JOYSTICK_BUTTON,INPUT);
    digitalWrite(JOYSTICK_BUTTON,HIGH);
    
    delay(500);
    
    Serial.begin(9600);
    
    //loop
    while (true){
        //main menu, gets map selection
        //starts on line 12 so adjusting to be used as an index
        int map_choice = in_menu() - 12;
        //prints the map
        print_bitmap(map_choice);
        //playing game
        game_mode(map_choice);
    }
    
    Serial.end();
    return 0;
}
