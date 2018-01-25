// === shared.h ===
#ifndef _SHARED_H_
    #define _SHARED_H_
    #define SD_CS    5  // Chip select line for SD card
    #define TFT_CS   6  // Chip select line for TFT display
    #define TFT_DC   7  // Data/command line for TFT
    #define TFT_RST  8  // Reset line for TFT (or connect to +5V)
    
    #define JOYSTICK_VERT  0   // Analog input A0 - vertical
    #define JOYSTICK_HORIZ 1   // Analog input A1 - horizontal
    #define JOYSTICK_BUTTON 9  // Digital input pin 9 for the button

    const int per_screen = 20; // # of lines on the tft
    const int selection_min = 12; // minimum tft line to highlight
    const int selection_max = 17; // maximum tft line to highlight
    
    //including the necessary libraries
    #include <Arduino.h>
    #include <Adafruit_GFX.h>
    #include <Adafruit_ST7735.h>
    #include <SPI.h>	
    #include <SD.h>
    
    //initializing external tft for use by multiple files
    extern Adafruit_ST7735 tft;
#endif
