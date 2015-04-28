/** Ball class for Laser Pong
*   Written by: Arthur Silveira

* 	Last Edit:  04/27/15
*		Depends on: laserDriver by Darren Curry.
*/

#ifndef PADDLE_H
#define PADDLE_H

#include <LaserDriver.h>

/**
* @brief Paddle  
*
*/
class Paddle
{
	private:
		
			/*Dimenssions of Paddle*/
		int xPos;
		int yPos;
		const int width;
		const int  height;

			/*Velocity of Paddle*/
		int dx;
		int dy;

	public:

	 	/*
		*	@brief Constructs Paddle object
		*		
		* @param x The initial x position of the paddle
		*	@param y The initial y position of the paddle
		* @param w The width of the paddle
		*	@param h The height of the paddle
		*
		**/
		Paddle(int x, int y, int w, int h): 
			xPos(x), 
			yPos(y),
			width(w),
			height(h),
			dx(0),
			dy(0) 
		{
			//
		}

		/* Getter methods */
		int getX()const{return xPos;}
		int getY()const{return yPos;}
		int getDx()const{return dx;}
		int getDy()const{return dy;}
		int getW()const{return width;}
		int getH()const{return height;}



		void update(int y){yPos=y;}

		/*
	 	*	@brief Sets the Y position of the Paddle.
	 	*
	 	*	@param y The new y position
	 	*
	 	**/
		void setY(int y) { yPos = y;}

		/**
		* @brief Draws the paddle on the screen by calling on LaserDriver class
		*
		*	@param LD The LaserDrive object used to draw rectangles.
		*																			
		*/
};

#endif