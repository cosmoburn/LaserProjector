/********  Laser Driver for eBay Laser Gavlonometer
 * BCTC *  Written By: Darren Curry
 * TECH *
 * CLUB *  KCTCS: Bluegrass Community College
 ********  Cooper Campus
 * 2015 *
 ********/

#ifndef LASERDRIVER_h
#define LASERDRIVER_h

#include "Arduino.h"

class LaserDriver {
    
public:
    LaserDriver();
    
    void lPlot(char X, char Y);
    //Set laser position with line draw algorithm
    
    void lOn(bool ON);
    //Turns the laser on and off
    
    void lSet(char X, char Y);
    //Sets the position of the laser w/o line draw algorithm
    
    void lRect(char X, char Y, char W, char H);
    //Draws a rectangle at position X,Y and size W and H
    
    void lCircle(char X, char Y, char R);
    //Draws a circle at position X, Y with radius R
    
    
private:
    //PIN ASSIGNMENTS
    int     D[8],     //BLACK
            WR,       //ORANGE
            SEL;      //VIOLET
    
    //Previous Values for line algorithm
    char    X_prev,
            Y_prev;
    
    void setAxisXY(char axis);
    //Sets the Axis to either X or Y
    // axis == X sets Galvo to X axis
    // axis == Y sets Galvo to Y axis
    
    void setDataBus(char pos);
    //Converts a character (0x00 - 0xFF) to a binary
    //  representation on the Data Bus D[0] - D[7]
    
    void writeData();
    //Writes the output to the DAC
    
};


#endif


