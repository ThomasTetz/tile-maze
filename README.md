# tile-maze
Arduino based maze game using a joystick and LCD

Thomas Tetz, Brett Baker  
2015

# Description:

Tile Maze is a sliding tile puzzle game. The user controls the player
cursor with a joystick, which slides in the chosen direction until it
hits a wall tile or the edge of the map, where it will stop.

The purpose of the game is to get the red player cursor to the green
finish tile. The player can quit to the main menu whenever stationary
by clicking the joystick. There are multiple maps of varying difficulty
to choose from.

Maps are stored as bitmap (.bmp) files. For each map is a corresponding
constraints file, which is a text file containing data on where the
wall tiles are. Additionally there is a single text file that contains
the high scores for all of the maps, organized from easy to hard, with
three entries each. All of these files are on the SD card. As such,
high scores are saved even if the arduino is powered off. A default
high score file is made in the event it is not found on the SD card.

# Layout of Code/Files:
* main.cpp
  * initializes the arduino, tft, and SD card
  * loops through the other functions to create the game
* shared.h
  * defines pin assignments
  * contains shared constants
  * includes necessary graphical and SD libraries
  * sets up the extern tft
* all other header files just have the functions for their .cpp listed 
* menu.cpp
  * prints out the main menu
  * allows the user to scroll through and select the level to play
  * returns the selection
* bitmap_printer.cpp
  * prints out the chosen map (.bmp on the SD card)
  * modified from spitftbitmap.cpp from examples folder of the VM
* game_mode.cpp
  * playing the game
  * calls for the map constraints to be loaded
  * allows the user to move the cursor via the joystick
  * tracks and displays the time elapsed while playing
  * calls scoring() with the player's score if they win
  * quits to main menu if they click
* constraints.cpp
  * loads the map constraints from a txt file on the SD card
* scoring.cpp
  * loads the high scores from a txt file on the SD card
  * finds the 3 for the map that was played
  * sorts those 3 along with the player's score
  * writes the scores back to the file with only the top 3 of the 4
  * displays the high scores and the player's score
  * returns to main menu

# References:
* wiring guide and image
  * ugweb.cs.ualberta.ca/~c274/web/ConcreteComputing/section/adafruit_lcd.htm
* bitmap header explanation from www.tinaja.com/glib/expbmp.pdf

# Accessories: 
* Arduino Mega Board (AMG)
* LCD screen
* joystick
* wires

# Wiring Instructions:
1 - LCD
* GND <--> BB GND bus
* VCC <--> BB positive bus
* RESET <--> Digital Pin 8
* D/C (Data/Command) <--> Digital Pin 7
* CARD_CS (Card Chip Select) <--> Digital Pin 5
* TFT_CS (TFT/screen Chip Select <--> Digital Pin 6
* MOSI (Master Out Slave In) <--> Digital Pin 51
* SCK (Clock) <--> Digital Pin 52
* MISO (Master In Slave Out) <--> Digital Pin 51
* LITE (Backlight) <--> BB positive bus
2 - Joystick
* VCC <--> BB positive bus
* VERT <--> Analog Pin A0
* HOR <--> Analog Pin A1
* SEL <--> Digital Pin 9
* GND <--> BB GND bus

# SD Card Instructions:
* copy all files located in sd/ to the SD card
* these files include the maps, their constraints, and the high scores

# How to run code:
* change directories to Project/
* connect the arduino to the computer after wiring and loading the SD
* type "make upload && serial-mon" and press enter
* scroll with the joystick to select the map to play
*    wait about a second before scrolling for the joystick to calibrate
* click the joystick to load that map
* move around the screen using the joystick
*    cursor/player is red, finish tile is green
*    the cursor slides until a wall tile or the edge of the map is hit
* clicking the joystick when stationary returns to the main menu
* winning will bring up a screen with scores
* repeatable, can play multiple levels or the same one multiple times
  
# Notes: 

Potential improvements:
* more safeguards when reading from files to ensure the data is good
* greater efficiency overall to reduce processor footprint
* do manual memory allocation to reduce footprint
* include solutions for each map
* make more easy/medium maps
