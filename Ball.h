#ifndef BALL_H
#define BALL_H

#include <LaserDriver.h>

/**
 * @brief Ball
 *
 */
class Ball
{
	private:

		/* Radius and Position of Ball */
		int radius;
		int xPos;
		int yPos;

		/* Velocity of Ball*/
		int dx;
		int dy;

	public:

	 Ball(int x, int y, int r): 
	 	xPos(x), 
	 	yPos(y),
	 	radius(r),
	 	dx(3),
	 	dy(3) 
	 {
	 	//
	 }

	 /* Getter methods */
	 int getX()const{return xPos;}
	 int getY()const{return yPos;}
	 int getR()const{return radius;}
	 int getDx()const{return dx;}
	 int getDy()const{return dy;}

	 void setVel(int xVel, int yVel) { dx = xVel; dy = yVel; }

	 void update() {xPos+= dx; yPos+= dy;}

	 void reset(int x, int y){xPos = x; yPos = y; dx =0; dy =0;}

	 	/**
	 	* @brief
	 	*
	 	* @param x
	 	* @param y
	 	* @param r
	 	*
	 	*/
	 void draw( LaserDriver &LD ) { LD.lCircle( xPos, yPos, radius ); }

};

#endif