//including necessary header files
#include "shared.h"
#include "menu.h"

/*
 * Note: scrolling before it finishes loading will cause an infinite
 *       scroll. Wait about a second after the menu appears.
 */ 

char names[20][60];
//stores the colours for the text and its background
//different difficulties have different colour schemes
int highlights[6] = {0xFFFF00,0xFFFF00,0xFF8000,0xFF8000,0xFF8888,0xFF8888};
int letters[6]    = {0x000000,0x000000,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF};
int selection=12, old_selection=12; // choices start on 12th line
int line_length = 8; // length of line on tft

//prints out the main menu
void print_names(int start, int end){
    tft.fillScreen(0x000000); // fill with black bg
    tft.setCursor(0,0); // set cursor, indicates where
    tft.setTextWrap(false); //no wrapping
    //prints all as white text on black background unless selected
    for(int i = start; i <=end; i++){
        if(i == selection){
            tft.setTextColor(letters[selection-12],highlights[selection-12]);
        }
        else{tft.setTextColor(0xFFFFFF,0x000000);}//white on black
        tft.print(names[i]);
        tft.print('\n');
    }
    tft.setCursor(0,selection*line_length);
}

//updates names to highlight the selected map
void update_names(){
    tft.setCursor(0,old_selection*line_length);
    tft.setTextColor(0xFFFFFF,0x000000);
    tft.print(names[old_selection]);
    tft.setCursor(0,selection*line_length);
    tft.setTextColor(letters[selection-12],highlights[selection-12]);
    tft.print(names[selection]);
}

/* === in_menu() === */
int in_menu(){
    //contents of main menu to be printed
    strcpy(names[0],"");
    strcpy(names[1],"    _____ _ _          ");
    strcpy(names[2],"   |_   _(_) |___      ");
    strcpy(names[3],"     | | | | / -_)     ");
    strcpy(names[4],"     |_| |_|_\\___|    ");
    strcpy(names[5],"");
    strcpy(names[6]," __  __                ");
    strcpy(names[7],"|  \\/  |____ _______  ");
    strcpy(names[8],"| |\\/| / _' |_  / -_) ");
    strcpy(names[9],"|_|  |_\\__,_/___\\___|");
    strcpy(names[10],"");
    strcpy(names[11],"");
    strcpy(names[12],"        Easy 1        ");
    strcpy(names[13],"        Easy 2        ");
    strcpy(names[14],"       Medium 1       ");
    strcpy(names[15],"       Medium 2       ");
    strcpy(names[16],"        Hard 1        ");
    strcpy(names[17],"        Hard 2        ");
    strcpy(names[18],"");
    strcpy(names[19],"");
    
    //prints the main menu
    print_names(0,per_screen-1);
    
    //reading intitial joystick values, only vertical relevant here
    int init_joystick_vert = analogRead(JOYSTICK_VERT);
    int delta_vert=0; //change in joystick, only vertical relevant here
    int vertical=0;
    
    //while in the menu user can scroll through the selections
    while(true){
        //reads the joystick vertical and calculates the difference
        vertical   = analogRead(JOYSTICK_VERT);
        delta_vert = vertical - init_joystick_vert;

        old_selection = selection;

        //up
        if(delta_vert > 175){ // threshold for change
            selection = selection + 1;
            //if at the top it wraps to the bottom
            if(selection>selection_max){ selection = selection_min; }
            update_names(); // updates highlighted choice
            delay(200);
        }
        //down
        else if(delta_vert < -175){
            selection = selection - 1;
            //if at the bottom it wraps to the top
            if(selection<selection_min){ selection = selection_max; }
            update_names(); // updates highlighted choice
            delay(200);
        }
        // returns selection when joystick button is pressed
        if(digitalRead(JOYSTICK_BUTTON) == 0){
            delay(100);
            return selection;
        }
        delay(1); // no busy loop
    }
}
