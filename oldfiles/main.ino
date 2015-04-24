#include <iostream>
#include "laserdriver.h"

using namespace std;

void gameLoop();
void drawCourt(int width, int height);
bool checkCollision(Ball &ball, const Paddle &lPad, const Paddle &dPad);


/******************************************************************************
*                                Classes                                      *
******************************************************************************/

 /**
 * @brief Ball
 *
 */
class Ball
{
	private:

		/* Radius and Position of Ball */
		int radius;
		int yPos;
		int xPos;

		/* Velocity of Ball*/
		int dx;
		int dy;

	public:

	 Ball(int x, int y, int r){xPos=x; yPos =y; radius = r;}
	 ~Ball();

	 /* Getter methods */
	 int GetXpos(){return xPos;}
	 int GetYpos(){return yPos;}
	 int GetDx(){return dx;}
	 int GetDy(){return dy;}

	 void UpdateVel(int xVel, int yVel) { dx = xVel; dy = yVel; }

	 void UpdatePos() {xPos+= dx; yPos+= dy;}

	 	/**
	 	* @brief
	 	*
	 	* @param x
	 	* @param y
	 	* @param r
	 	*
	 	*/
	 void draw(int x, int y, int r){lCircle( x, y, r );}

};


/**
* @brief Paddle  
*
*/
class Paddle
{
	private:
		
		/* Dimmenssions and Position of paddle */
		int yPos;
		int xPos;
		int height;
		int width;

		int dy;
		int dx;

	public:

		Paddle(int x, int y, int){xPos= x; yPos=y;}

		/* Getter methods */
	  int GetXpos(){return xPos;}
		int GetYpos(){return yPos;}
	 	int GetDx(){return dx;}
	 	int GetDy(){return dy;}

	 	void Draw(int xPos,  int yPos, int width, int height)
	 		{lRect(xPos, yPos, width, height);}

};


/******************************************************************************
*                                  Main                                                                             *
******************************************************************************/

int main(int argc, char const *argv[])
{

	gameLoop();

	return 0;
}
	
	/* main game loop */
int gameLoop()
{		
		/* Dimenssions of Court */
	const int court_width = 255;
	const int court_height = 255;

		/* Radius of ball */
	const int ball_r = 4; 

		/* Create Ball at the center of the court */
	Ball ball( ( (court_width/2)- ball_r), ((court_height/2)- ball_r ) )

		/* Create left and right paddles */
	Paddle lPad(10, (court_height/2), 10, 20)
	paddle rPad( ( court_width-20), (court_height/2), 10, 20 ) 

		/* Game loop */
	while(true)
	{	

		drawCourt( court_width, court_height);
		lPad.Draw();
		rPad.Draw();
		ball.Draw();
		
	}

	return true;
}

void drawCourt(int width, int height)
{

	lSet( 0, 0 );
	delayMicroseconds(700);
	lSet( 0, width );
	delayMicroseconds(700);
	lSet( 0, (width/2) );
	delayMicroseconds(700);
	lSet( height, (width/2) );
	delayMicroseconds(700);
	lSet( width , height );
	delayMicroseconds(700);
	lSet( 0, height );

}

