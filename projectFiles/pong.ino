/** Laser Pong game for Arduino Laser projector
*   Written by: Arthur Silveira

* 	Last Edit:  04/27/15
*		Depends on: laserDriver by Darren Curry.
*/

#include "Ball.h"					// Ball Class
#include "Paddle.h"					// Paddle Class
	
/******************************************************************************
*                               Global Constants                              *
******************************************************************************/	
 
 //Dimenssions of Court
const int COURT_WIDTH = 255;
const int COURT_HEIGHT = 255;

 // Delay(in microseconds) between points
const unsigned int DRAW_DELAY = 1000;

/******************************************************************************
*                                      Setup                                  *
******************************************************************************/

void setup() 
{	
		// main game loop
	void playGamel(
		LaserDriver &LD,
		Ball &ball,
		Paddle &lPad,
		Paddle &rPad);
	
	// draws each frame
	void drawFrame(
		LaserDriver &LD,
		const Ball &ball,
		const Paddle &lPad,
		const Paddle &rPad);
		// checks for every collision

	void checkCollision(
		Ball &ball,
		Paddle &lPad,
		Paddle &rPad);
}

/******************************************************************************
*                                  Main                                       *
******************************************************************************/

/* The Arduino loop */
void loop()
{
	 //LaserDriver object
	LaserDriver LD;

	 //Ball object at (x,y, with radius r)
	static Ball ball( (COURT_WIDTH/2), COURT_HEIGHT/2, 5 );

	 //Paddle objects at (x, y, width, height )
	static Paddle lPad(0, (COURT_HEIGHT/2), 10, 30);
	static Paddle rPad( ( COURT_WIDTH), (COURT_HEIGHT/2), 10, 30 );

	playGame(LD, ball, lPad, rPad);
}
	
/*
*	@brief The main game loop, where the magic happens.
*	
*	@param LD The LaserDriver object, used to draw lines with projector.
*	@param Ball The Ball object
	@param lPad The left Paddle object
	@param rPad The Right Paddle obeject
*
**/
void playGame(LaserDriver &LD, Ball &ball, Paddle &lPad, Paddle &rPad)
{ 
	 /* Game loop */
	while(true)
	{	
		 /* update positions > check for collisions > draw frame */
		lPad.update((analogRead(4)/2));
		rPad.update((analogRead(5)/2));
		ball.update();
		checkCollision(ball,lPad,rPad);
		drawFrame(LD, ball, lPad, rPad);
		
	}
}

/******************************************************************************
*                            Secondary Functions                              *
******************************************************************************/

/*
* @brief Draws one frame of our game.
*
* @param LD The LaserDriver object for controling the galvo scanners.
* @param lPad The left paddle object.
*	@param rPad	The right paddle object.
*
**/
void drawFrame(
	LaserDriver &LD,
	const Ball &ball,
	const Paddle &lPad,
	const Paddle &rPad)
{

	/* From  top left corner(0,0) */
	LD.lSet( 0, 0 );
	delayMicroseconds(DRAW_DELAY);

	/* to top of left paddle */
	LD.lSet( 0, lPad.getY() );
	delayMicroseconds(DRAW_DELAY);

	/* Draw left paddle */
	LD.lSet( lPad.getW(), lPad.getY() );
	delayMicroseconds(DRAW_DELAY);
	LD.lSet( lPad.getW(), lPad.getY() + lPad.getH() );
	delayMicroseconds(DRAW_DELAY);
	LD.lSet( lPad.getX(), lPad.getY() + lPad.getH() );
	delayMicroseconds(DRAW_DELAY);

	/* to bottom left corner, then bottom center */
	LD.lSet( 0, COURT_HEIGHT);;
	delayMicroseconds(DRAW_DELAY);
	LD.lSet( COURT_WIDTH/2, COURT_HEIGHT );
	delayMicroseconds(DRAW_DELAY);

	/* to  position of the ball, then draw ball and return */
		
	LD.lSet( ball.getX(), (ball.getY() + ball.getR()) );
	delayMicroseconds(DRAW_DELAY);
	
	ball.draw(LD);
	delayMicroseconds(DRAW_DELAY);

	LD.lSet( ball.getX(), (ball.getY() - ball.getR()) );
	delayMicroseconds(DRAW_DELAY);


	/* to top center then top right corner(255, 0) */
	LD.lSet( COURT_WIDTH/2, 0 );
	delayMicroseconds(DRAW_DELAY);
	LD.lSet( COURT_WIDTH, 0 );
	delayMicroseconds(DRAW_DELAY);

	// ------ repeat on right side to complete drawing of frame ------\\

	/* to top of right paddle then draw right paddle */
	LD.lSet( COURT_WIDTH, rPad.getY() );
	delayMicroseconds(DRAW_DELAY);
	LD.lSet( COURT_WIDTH - rPad.getW(), rPad.getY() );
	delayMicroseconds(DRAW_DELAY);
	LD.lSet( COURT_WIDTH - rPad.getW(), rPad.getY() + rPad.getH() );
	delayMicroseconds(DRAW_DELAY);
	LD.lSet( COURT_WIDTH, rPad.getY() + rPad.getH() );
	delayMicroseconds(DRAW_DELAY);

	/* to bottm right corner then bottom center */
	LD.lSet( COURT_WIDTH, COURT_HEIGHT);;
	delayMicroseconds(DRAW_DELAY);
	LD.lSet( COURT_WIDTH/2, COURT_HEIGHT );
	delayMicroseconds(DRAW_DELAY);

	/* draw middle line then back to beginning (0,0) */
	LD.lSet( COURT_WIDTH/2, 0 );
	delayMicroseconds(DRAW_DELAY);
	LD.lSet( 0, 0 );
	delayMicroseconds(DRAW_DELAY);

}

/*
* @brief Checks for all the collisions in the game.
*
*	@param ball The Ball object
*	@param lPad The left Paddle object
*	@param rPad The right Paddle object

**/
void checkCollision(
	Ball &ball,
	Paddle &lPad,
	Paddle &rPad)
{	

	/* if player 1 scores */
	if ( ball.getX() >= COURT_WIDTH - ball.getR() )
	{
		ball.reset(COURT_WIDTH/2, COURT_HEIGHT/2);
		ball.setVel(3,3);
	}

	/* if player 2 scores */
	if ( ball.getX() <= ball.getR() )
	{	
		ball.reset(COURT_WIDTH/2, COURT_HEIGHT/2);
		ball.setVel(-3,-3);	
	}

		/* ball collision with top and bottom walls */
	if (ball.getY() <= ball.getR()  
		|| ball.getY() >= COURT_HEIGHT - ball.getR())
	{

		ball.setVel( ball.getDx(), -ball.getDy() );
	}


			/* Paddle Collision with walls */
	if (lPad.getY() >= COURT_HEIGHT - lPad.getH() )
	{
		lPad.setY( COURT_HEIGHT - lPad.getH() );
	}

	if (rPad.getY() >= COURT_HEIGHT - rPad.getH() )
	{
		rPad.setY( COURT_HEIGHT - rPad.getH() );
	}

		/* Paddles Collision with Ball */

			/* left paddle*/
	if ( ball.getX() -ball.getR() <= lPad.getW()
		&& ball.getY() + ball.getR() >= lPad.getY()
		&& ball.getY() - ball.getR() <= lPad.getY() + lPad.getH() )
	{	
		
		ball.setVel(-ball.getDx(), ball.getDy());
		ball.setPos( lPad.getW() + ball.getR(), ball.getY());

		  
	}



			/* right paddle */
	if ( ball.getX() + ball.getR() >= COURT_WIDTH - rPad.getW() 
		&& ball.getY() + ball.getR() >= rPad.getY()
		&& ball.getY() - ball.getR() <= rPad.getY() + rPad.getH() )
	{	
		
		ball.setVel(-ball.getDx(), ball.getDy());
		ball.setPos( (COURT_WIDTH - rPad.getW() - ball.getR() ), ball.getY());
		
	}
}
