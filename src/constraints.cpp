//including necessary header files
#include "shared.h"
#include "constraints.h"

/* === load_constraints() === */
//associates txt file lines with pixels on the tft
//calculates coordinates from the data
int load_constraints(int map_choice, int counter) {

    //initialization before reading
    int mapBoundaries;
    File dataFile;
    
    //chooses the file to open based on the user selection
    //sets number of wall tiles that exist on the chosen map
    if (map_choice==0) {
        mapBoundaries=17; dataFile = SD.open("easyone.txt");
    }
    else if (map_choice==1) {
        mapBoundaries=36; dataFile = SD.open("easytwo.txt");
    }
    else if (map_choice==2) {
        mapBoundaries=15; dataFile = SD.open("medone.txt");
    }
    else if (map_choice==3) {
        mapBoundaries=38; dataFile = SD.open("medtwo.txt");
    }
    else if (map_choice==4) {
        mapBoundaries=68; dataFile = SD.open("hardone.txt");
    }
    else { //map_choice==5
        mapBoundaries=130; dataFile = SD.open("hardtwo.txt");
    }

    int prohibited[mapBoundaries];
    char linespro[5] = {0};

      if (dataFile) {
        //reads until the end of the chosen file
        //converts the data into coordinates
        while (dataFile.available()) {

        int i=0;

        for (int j = 0; j <= 4; ++j) {

            char dataByte = dataFile.read(); // the byte being read

            // if new line move on to get next constraint
            if(dataByte == 13) {
                linespro[j]=0;
                int prohibitedLine=atoi(linespro);
                prohibited[i]=prohibitedLine;
                ++i;
                j=-1;
            }
            else if(dataByte== 10) {
                --j;
            }
            // if end
            else if(dataByte== NULL || dataByte== -1) {
                break;
            }
            //get the byte if it's valid
             else{
                linespro[j] = dataByte;
            }
        }
    }
    //done with the file
    dataFile.close();
    }
    //if the file fails to open
    else {
        Serial.println("error opening datalog");
    }
    return prohibited[counter];
}


