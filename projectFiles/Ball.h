/** Ball class for Laser Pong
*   Written by: Arthur Silveira
* 	Last Edit:  04/27/15
*	Depends on: laserDriver by Darren Curry.
*/
#ifndef BALL_H
#define BALL_H

#include "LaserDriver.h"  // For drawing with laser projector

class Ball
{
	private:

		/* Radius and Position of Ball */
		const int radius;
		int xPos;
		int yPos;

		/* Velocity of Ball*/
		int dx;
		int dy;

	public:
		/*
		*	@brief Constructs Ball object
		*		
		*	@param x The initial x position of the ball
		*	@param y The initial y position of the ball
		* 	@param r The radius of the ball
		*
		**/
	 	Ball(int x, int y, int r): 
			xPos(x), 
			yPos(y),
			radius(r),
			dx(2),
			dy(2) 
	 	{
			//
	 	}

	 	/* Getter methods */
	 	int getX()const{return xPos;}
	 	int getY()const{return yPos;}
	 	int getR()const{return radius;}
	 	int getDx()const{return dx;}
	 	int getDy()const{return dy;}


	 	/*
	 	*	@brief Sets The velocity of ball.
	 	*	
	 	*	@param xVel The velocity of ball in X direction.
	 	*	@param yVel The velocity of the ball in Y direction.
	 	**/
	 	void setVel(int xVel, int yVel) { dx = xVel; dy = yVel; }

	 	/**
	 	*	@brief Updates the position of the ball based on the current dx and dy 
	 	*
	 	**/
	 	void update() {if(dx < radius){xPos+= dx;} if(dy< radius){yPos+= dy;} }  


	 	/*
	 	*	@brief Resets the ball to position (x,y) and 0 velocity(dx, dy)
	 	*
	 	*	@param x The new x position
	 	*	@param y The new y position
	 	**/
	 	void reset(int x, int y){xPos = x; yPos = y; dx =0; dy =0;}


		/**
		* @brief Draws the ball on the screen by calling on LaserDriver class
		*
		*	@param LD The LaserDrive object used to draw circles @ (x,y)
		*											with a radius of r
		*/
		void draw( LaserDriver &LD )const { LD.lCircle(xPos, yPos, radius); }

};

#endif