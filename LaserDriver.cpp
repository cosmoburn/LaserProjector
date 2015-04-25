#include "LaserDriver.h"
#include "Arduino.h"
    //Arduino stuff
/************
 *  PUBLIC  *
 ************/

void LaserDriver::lPlot(char X, char Y) {
    //Line Draw Stuff Here
}

void LaserDriver::lOn(bool ON) {
    //LASER IO HERE
}

void LaserDriver::lSet(char X, char Y) {
    //Sets the position of the laser w/o line draw algorithm
    
    setAxisXY('X');
        //Set bus to X
    
    setDataBus(X);
        //Write position to data bus
    
    writeData();
        //Write Data to Analog converter
    
    setAxisXY('Y');
        //Set bus to Y
    
    setDataBus(Y);
        //Write position to data bus
    
    writeData();
        //Write data to analog converter
}

void LaserDriver::lRect(char X, char Y, char W, char H){
    //Draws a rectangle at position X,Y and size W and H
    lSet(X-W/2, Y-H/2);
    delayMicroseconds(500);
    
    lSet(X+W/2, Y-H/2);
    delayMicroseconds(1000);

    lSet(X+W/2, Y+H/2);
    delayMicroseconds(500);
    lSet(X-W/2, Y+H/2);
    
    delayMicroseconds(500);

    lSet(X-W/2, Y-H/2);
    delayMicroseconds(500);
}

void LaserDriver::lCircle(char X, char Y, char R) {
    char temp_X, temp_Y;
    
    for ( temp_X=-R; temp_X<=R; temp_X++ ) {
        temp_Y = sqrt( (R*R) - (temp_X*temp_X) );
        lSet( temp_X + X, temp_Y + Y );
        
        if (temp_X == -R)
            delay(2);
    }
    
    for ( temp_X=R-1; temp_X>=-R; temp_X-- ) {
        temp_Y = -1 * sqrt( (R*R) - (temp_X*temp_X) );
        lSet( temp_X + X, temp_Y + Y );
        if (temp_X == -R)
            delay(2);
    }
    
}



/*************
 *  PRIVATE  *
 *************/


LaserDriver::LaserDriver() {
    //ASSIGN PINS
    D[0] = 0;  // 1
    D[1] = 1;  // 2
    D[2] = 2;  // 4
    D[3] = 3;  // 8
    D[4] = 4;  // 16
    D[5] = 5;  // 32
    D[6] = 6;  // 64
    D[7] = 7;  // 128
    WR = 8;    // WRITE
    SEL = 9;   // SELECT
    
    //Set previous variables to a NULL value
    X_prev=0;
    Y_prev=0;
    
    //Set DATA pins as outputs
    for (int i=0; i<=7; i++)
        pinMode(D[i] ,OUTPUT);
    
    //Set WRITE and SELECT pins as outputs
    pinMode(WR, OUTPUT);
    pinMode(SEL, OUTPUT);
    
    //Set WRITE to high to prevent writing DAC
    digitalWrite(WR, HIGH);
}

void LaserDriver::writeData() {
    PORTB^=B00000001;
    PORTB^=B00000001;
    /*
    digitalWrite(WR, LOW);
    //delay(1);
    digitalWrite(WR, HIGH);*/
}

void LaserDriver::setDataBus(char pos) {
    PORTD = pos;
    /*int temp;
    //temp value of shifted input
    
    //Loop through bit values (8 bit aka 0-7)
    for (int i = 7; i >= 0; i--) {
        temp  = pos >> i;
        //Shift binary position so that 128 becomes 1;
        
        //Bitwise & temp and 1
        if ( temp & 1 )
            digitalWrite( D[i], HIGH );
        else
            digitalWrite( D[i], LOW );
        
    }*/
    
}

void LaserDriver::setAxisXY(char axis){
    if ( axis == 'X' )
        PORTB&=B11111101;
        //digitalWrite(SEL, LOW);
    else
        PORTB|=B00000010;
        //digitalWrite(SEL, HIGH);
}


