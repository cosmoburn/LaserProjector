#include "LaserDriver.h"
#include "Arduino.h"
#include "math.h"     // for cos() & sin() functions
		//Arduino stuff
/************
 *  PUBLIC  *
 ************/

const int CIRCLE_POINTS = 8;
		// Global constant: Points used to draw circle.


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
				//Wri te Data to Analog converter
		
		setAxisXY('Y');
				//Set bus to Y
		
		setDataBus(Y);
				//Write position to data bus
		
		writeData();
				//Write data to analog converter
}


void LaserDriver::lCircle(const int &X, const int &Y, const int &R)
{    
		static int cosTable[CIRCLE_POINTS];
		static int sinTable[CIRCLE_POINTS];

		 static bool firstRun = true;

		/* compute coordinate of the points of circle */
				
		if (firstRun)   // only one time
		{
				for (int i = 0; i < CIRCLE_POINTS; ++i)
				{
						static float angle = (PI/2);
						cosTable[i] = cos(angle) * R;
						sinTable[i] = sin(angle) * R;

						angle += (2*PI)/CIRCLE_POINTS;
				}

				firstRun = false;
		}

		for (int i = 0; i < CIRCLE_POINTS; ++i)
		{
				lSet( X + cosTable[i], Y + sinTable[i] );
				delayMicroseconds(200);
		}

		lSet( X + cosTable[0], Y + sinTable[0]);
				//draw first point again
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


