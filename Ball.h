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
		unsigned char radius;
		unsigned char xPos;
		unsigned char yPos;

		/* Velocity of Ball*/
		unsigned char dx;
		unsigned char dy;

	public:

	 Ball(unsigned char x, unsigned char y, unsigned char r): 
	 	xPos(x), 
	 	yPos(y),
	 	radius(r),
	 	dx(3),
	 	dy(3) 
	 {
	 	//
	 }

	 /* Getter methods */
	 unsigned char getX()const{return xPos;}
	 unsigned char getY()const{return yPos;}
	 unsigned char getR()const{return radius;}
	 char getDx()const{return dx;}
	 char getDy()const{return dy;}

	 void setVel(char xVel, char yVel) { dx = xVel; dy = yVel; }

	 void update() {xPos+= dx; yPos+= dy;}

	 void reset(){xPos = 127; yPos = 127; dx =0; dy =0;}

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