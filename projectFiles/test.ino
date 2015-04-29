#include "LaserDriver.h"
#include "math.h"

void setup(){}


void loop()
{	



	LaserDriver LD;

	int x = 255/2;
	int y = 255/2;
	int r = 50;


	delayMicroseconds(500);
	static float temp =0;
	int leftPot=analogRead(A4)/8;
	int rightPot=(analogRead(A5)/32)+2;
	//fine = random(1, 255);
	for (int i = 0; i<=255; i++ ) {
		//temp = (random(0, 1024)/163.1);

		//delayMicroseconds(200);
		//static int temp=0;
		//if (i%=5) temp = random(50,150);
		//LD.lSet(i, temp);
		LD.lSet( (char)(tan(temp)*(leftPot)+128)*(char)(sin(temp)*(leftPot)+128), (char)(cos(temp)*(leftPot)+128)*(char)(sin(temp)*(leftPot)+128));
		//LD.lSet(i, (char)(tan(temp)*64.0f)+128);
		temp+=6.28f/(rightPot);
		//delayMicroseconds(5);
		}

	/*
	LD.lSet(x, y-r);
	delayMicroseconds(200);
	LD.lSet(x-r, y-r);
	//delayMicroseconds(100);
	LD.lSet(x-r, y);
	delayMicroseconds(200);	
	LD.lSet(x-r, y+r);
	//delayMicroseconds(100);
	LD.lSet(x, y+r);
	delayMicroseconds(200);	
	LD.lSet(x+r, y+r);
	//delayMicroseconds(100);	
	LD.lSet(x+r, y);
	delayMicroseconds(200);
	LD.lSet(x+r, y-r);
	//delayMicroseconds(100);
	*/
	

	/*float angle = 0;

	LaserDriver LD;

	for(int i=255; i>0; i--){
		
		LD.lSet( i*i*i, (pow(-1, i)));
		delayMicroseconds(500);	
	}
	for(int i=255; i>0; i--){
		
		LD.lSet( i/2, (pow(-1, i)));
		delayMicroseconds(500);	
	}
	for(int i=0; i<255; i++){
		
		LD.lSet( i*i*i, (i));
		delayMicroseconds(500);	
	}

	for(int i=0; i<255; i++){
		
		LD.lSet((i),i*i*i);
		delayMicroseconds(500);	
	}

	for(int i=255; i>0; i--){
		
		LD.lSet( i*i*i, (pow(-1, i)));
		delayMicroseconds(500);	
	}
	for(int i=0; i<255; i++){
			LD.lSet( i, pow(i,2) + pow(i,2));
			delayMicroseconds(250);
	}	
	
	for(int i=0; i<255; i++){

		LD.lSet( pow(i,2) + pow(i,2), pow(i,2) + pow(i,2));
		delayMicroseconds(250);	
	}
	
	
	for(int i=0; i<255; i++){
		
		LD.lSet( i,pow(i,2));
		delayMicroseconds(250);	
	}

	*/	
	
}
