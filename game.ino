/** Laser Pong game for Arduino Laser projector
*   Written by: Arthur Silveira
* 	Last Edit:  04/24/15
*	Depends on: laserDriver by Darren Curry.
*/
#include "LaserDriver.h"
#include "Ball.h"
#include "Paddle.h"
#include "math.h"
	
	/* Sides of circle */
const unsigned char CIRCLE_SIDES = 8;
unsigned char FILLER;

/******************************************************************************
*								Prototyping											  *
******************************************************************************/

void gameLoop(LaserDriver &LD);

void drawFrame(
	LaserDriver &LD,
	const Ball &ball,
	const Paddle &lPad,
	const Paddle &rPad,
	unsigned char width,
	unsigned char height);

void checkCollision(
	Ball &ball,
	Paddle &lPad,
	Paddle &rPad,
	const unsigned char court_width,
	const unsigned char court_height);

/* Arduino needs this*/
void setup() {}


/******************************************************************************
*                                  Main                                                                             *
******************************************************************************/

void loop()
{

	/* create LaserDriver object */
	LaserDriver LD;
	gameLoop(LD);
}
	
	/* main game loop */
void gameLoop(LaserDriver &LD)
{		
		/* Dimenssions of Court */
	const unsigned char court_width = 255;
	const unsigned char court_height = 255;

		/* Radius of ball */
	const unsigned char ball_r = 5; 

		/* Create Ball at the center of the court */
	static Ball ball( 
		( (court_width/2)- ball_r),
		((court_height/2)- ball_r),
		ball_r );

		/* Create left and right paddles */
	static Paddle lPad(0, (court_height/2), 10, 30);
	static Paddle rPad( ( court_width), (court_height/2), 10, 30 );

		/* Game loop */
	while(true)
	{	
		lPad.UpdateY((analogRead(4)/2));
		rPad.UpdateY((analogRead(5)/2));

		ball.UpdatePos();

		checkCollision(ball,lPad,rPad,court_width,court_height);


		drawFrame(LD, ball, lPad, rPad, court_width, court_height);
		


		
		
	}
}

/* Draws an entire frame */
void drawFrame(
	LaserDriver &LD,
	const Ball &ball,
	const Paddle &lPad,
	const Paddle &rPad,
	unsigned char width,
	unsigned char height)
{

	LD.lSet( 0, 0 );
	delayMicroseconds(700);
	LD.lSet( width, 0 );
	delayMicroseconds(700);
	LD.lSet( width, height );
	delayMicroseconds(700);
	LD.lSet( 0, height );
	delayMicroseconds(700);
	LD.lSet( 0 , 0 );
	delayMicroseconds(700);
	LD.lSet( width, 0 );
	delayMicroseconds(700);

	LD.lSet( width, rPad.GetYpos() );

	delayMicroseconds(700);
	LD.lSet( (width - rPad.GetWidth()), rPad.GetYpos() );
	delayMicroseconds(700);
	LD.lSet( (width - rPad.GetWidth()), ( rPad.GetYpos() + rPad.GetHeight())  );
	delayMicroseconds(700);
	LD.lSet( width, ( rPad.GetYpos() + rPad.GetHeight()) );
	delayMicroseconds(700);
	LD.lSet(width, height);
	delayMicroseconds(700);
	LD.lSet(0, height);
	delayMicroseconds(700);

	LD.lSet(0, (lPad.GetYpos()+ lPad.GetHeight()));
	delayMicroseconds(700);
	LD.lSet(lPad.GetWidth(), (lPad.GetYpos()+ lPad.GetHeight()) );
	delayMicroseconds(700);
	LD.lSet(lPad.GetWidth(), lPad.GetYpos());
	delayMicroseconds(700);
	LD.lSet(0, lPad.GetYpos());
	delayMicroseconds(700);

	LD.lSet(0,0);
	delayMicroseconds(700);

	LD.lSet((width/2), 0 );
	delayMicroseconds(700);
	LD.lSet((width/2), (height/2));
	delayMicroseconds(700);

	drawCircle(LD, ball);

	delayMicroseconds(700);

	LD.lSet((width/2), (height/2));
	delayMicroseconds(700);
	LD.lSet((width/2), height);
	delayMicroseconds(700);
	LD.lSet(0, height);
	delayMicroseconds(700);
	LD.lSet(0,0);
	delayMicroseconds(700);

}
	
/* draws a circle */
void drawCircle(LaserDriver &LD, const Ball &ball)
{
	static char cosTable[CIRCLE_SIDES];
	static char sinTable[CIRCLE_SIDES];

	static bool firstRun = true;

	if (firstRun)
	{

		for(unsigned char i = 0; i< CIRCLE_SIDES; i++){

			static float angle = 0.0f;
			cosTable[i] = (cos(angle) * ball.GetRadius()) + ball.GetRadius();
			sinTable[i] = sin(angle) * ball.GetRadius() + ball.GetRadius();

			angle += ((2*PI)/CIRCLE_SIDES);

		}

		firstRun = false;
	}

	for(unsigned char i=0; i<CIRCLE_SIDES; i++){
	    
	    LD.lSet(( ball.GetXpos() +  cosTable[i] ),( ball.GetYpos() +  sinTable[i] ));
	    delayMicroseconds(600);
	}

	LD.lSet( (ball.GetXpos() + cosTable[0]), ( ball.GetYpos() +  sinTable[0] )  );
	delayMicroseconds(100);

}

void checkCollision(
	Ball &ball,
	Paddle &lPad,
	Paddle &rPad,
	const unsigned char court_width,
	const unsigned char court_height)
{	
	/* if player 2 scores */
	if ( ball.GetXpos() - ball.GetRadius() <= ball.GetRadius())
	{	
		//ball.Reset();
		//ball.UpdateVel(3,3);
		
	}
	/* if player 1 scores */
	else if ( ball.GetXpos() >= (court_width - ball.GetRadius()) )
	{
		//ball.Reset();
		//ball.UpdateVel(-3,0);
	}

	if (ball.GetYpos() <= ball.GetRadius()  ||
		ball.GetYpos() >= court_height - ball.GetRadius())		
	{

		ball.UpdateVel( ball.GetDx(), -ball.GetDy() );
	}


	/* Paddle Collision */
	if (lPad.GetYpos() >= court_height - lPad.GetHeight() )
	{

		lPad.SetPosY( court_height - lPad.GetHeight() );
	}

	if (rPad.GetYpos() >= court_height - rPad.GetHeight() )
	{

		rPad.SetPosY( court_height - rPad.GetHeight() );
	}


	//* Paddle Collision with Ball *//

			/* left paddle*/
	if( ((ball.GetXpos() + ball.GetRadius()) <= lPad.GetWidth())
		&& (ball.GetYpos() + ball.GetRadius()) >= lPad.GetYpos()
		&& (ball.GetYpos() - ball.GetRadius()) <= lPad.GetYpos() + lPad.GetHeight() )
	{
	 	ball.UpdateVel( -ball.GetDx(), (ball.GetYpos() - (lPad.GetYpos()/2)) /15 );  
	}

			/* right paddle */
	if ( ((ball.GetXpos() - ball.GetRadius()) >= court_width -rPad.GetWidth())
		&& (ball.GetYpos() + ball.GetRadius()) >= rPad.GetYpos()
		&& (ball.GetYpos() - ball.GetRadius()) <= rPad.GetYpos() + rPad.GetHeight() )

	{
		ball.UpdateVel( -ball.GetDx(), (ball.GetYpos() - (rPad.GetYpos()/2)) /15 );
	}
}




















	 //SAVING DARREN'S VALUES   float  SX_ball = 1.5,
	 //SAVING DARREN'S VALUES          SY_ball = 2.5,
	 //SAVING DARREN'S VALUES          X_ball = 128.0,
	 //SAVING DARREN'S VALUES          Y_ball = 128.0;